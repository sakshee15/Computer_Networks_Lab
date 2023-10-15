#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#define MAX_BUFFER_SIZE 1024
void error(char *msg)
{
    perror(msg);
    exit(1);
}
int main(int argc, char *argv[])
{
    WSADATA wsaData;
    SOCKET sockfd;
    struct sockaddr_in serv_addr;
    char buffer[MAX_BUFFER_SIZE];
    int n;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        error("WSAStartup failed");
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET)
    {
        error("ERROR opening socket");
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    serv_addr.sin_addr.s_addr = inet_addr("192.168.128.234");
    if (serv_addr.sin_addr.s_addr == INADDR_NONE)
    {
        error("Invalid address");
    }
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) ==
        SOCKET_ERROR)
    {
        error("ERROR connecting");
    }
    printf("Connected to server\n");
    FILE *file = fopen("file_to_send.txt", "rb");
    if (file == NULL)
    {
        error("ERROR opening file");
    }
    while ((n = fread(buffer, sizeof(char), MAX_BUFFER_SIZE, file)) > 0)
    {
        if (send(sockfd, buffer, n, 0) == SOCKET_ERROR)
        {
            error("ERROR writing to socket");
        }
    }
    printf("File sent successfully\n");
    fclose(file);
    closesocket(sockfd);
    WSACleanup();
    printf("Connection closed\n");
    return 0;
}