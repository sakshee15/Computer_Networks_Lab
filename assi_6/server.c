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
    SOCKET sockfd, newsockfd;
    struct sockaddr_in serv_addr, cli_addr;
    int clilen;
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
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(8080);
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) ==
        SOCKET_ERROR)
    {
        error("ERROR on binding");
    }
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    printf("Server is listening...\n");
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd == INVALID_SOCKET)
    {
        error("ERROR on accept");
    }
    printf("Connected to client\n");
    FILE *file = fopen("received_file.txt", "wb");
    if (file == NULL)
    {
        error("ERROR opening file");
    }
    while (1)
    {
        n = recv(newsockfd, buffer, MAX_BUFFER_SIZE, 0);
        if (n <= 0)
            break;
        fwrite(buffer, sizeof(char), n, file);
    }
    printf("File received successfully\n");
    fclose(file);
    closesocket(newsockfd);
    closesocket(sockfd);
    WSACleanup();
    printf("File saved as received_file.txt\n");
    return 0;
}