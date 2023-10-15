#include <stdio.h>
#include <winsock2.h>
#define PORT 8080
int main()
{
    WSADATA wsa;
    SOCKET client_socket;
    struct sockaddr_in server_addr;
    char message[1024];
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }
    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d", WSAGetLastError());
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("192.168.128.234");
    while (1)
    {
        printf("Enter message : ");
        gets(message);
        // Send to server
        sendto(client_socket, message, strlen(message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
        memset(message, '\0', sizeof(message));
        // Receive from server
        int addr_len = sizeof(server_addr);
        if (recvfrom(client_socket, message, sizeof(message), 0, (struct sockaddr *)&server_addr, &addr_len) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code : %d",
                   WSAGetLastError());
            return 1;
        }
        printf("Server: %s\n", message);
    }
    closesocket(client_socket);
    WSACleanup();
    return 0;
}
