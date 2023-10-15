#include <stdio.h>
#include <winsock2.h>
#define PORT 8080
#define MAX_BUFFER_SIZE 1024
int main()
{
    WSADATA wsa;
    SOCKET server_socket;
    struct sockaddr_in server_addr, client_addr;
    int addr_len = sizeof(client_addr);
    char buffer[MAX_BUFFER_SIZE];
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }
    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d", WSAGetLastError());
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    // Bind
    if (bind(server_socket, (struct sockaddr *)&server_addr,
             sizeof(server_addr)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d", WSAGetLastError());
        return 1;
    }
    while (1)
    {
        memset(buffer, '\0', sizeof(buffer));
        // Receive from client
        if (recvfrom(server_socket, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &addr_len) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code : %d",
                   WSAGetLastError());
            return 1;
        }
        printf("Received from %s:%d - %s\n", inet_ntoa(client_addr.sin_addr),
               ntohs(client_addr.sin_port), buffer);
        // Take response from server
        char response[MAX_BUFFER_SIZE];
        printf("Enter response message: ");
        gets(response);
        // Send response to client
        sendto(server_socket, response, strlen(response), 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
    }
    closesocket(server_socket);
    WSACleanup();
    return 0;
}