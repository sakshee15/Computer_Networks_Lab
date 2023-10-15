//#include <stdio.h>
//#include <winsock2.h>
//
//#pragma comment(lib, "ws2_32.lib")
//
//#define WINDOW_SIZE 4
//
//struct Packet {
//    int seq_num;
//    char data;
//    bool ack;
//};
//
//int main() {
//    WSADATA wsaData;
//    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
//        perror("WSAStartup failed");
//        return 1;
//    }
//
//    SOCKET server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
//    if (server_socket_fd == INVALID_SOCKET) {
//        perror("Socket creation failed");
//        WSACleanup();
//        return 1;
//    }
//
//    struct sockaddr_in server_addr;
//    server_addr.sin_family = AF_INET;
//    server_addr.sin_port = htons(1245);
//    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//
//    if (bind(server_socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
//        perror("Binding failed");
//        closesocket(server_socket_fd);
//        WSACleanup();
//        return 1;
//    }
//
//    if (listen(server_socket_fd, 1) == SOCKET_ERROR) {
//        perror("Listening failed");
//        closesocket(server_socket_fd);
//        WSACleanup();
//        return 1;
//    }
//
//    struct sockaddr_in client_addr;
//    int client_len = sizeof(client_addr);
//    SOCKET socket_fd = accept(server_socket_fd, (struct sockaddr *)&client_addr, &client_len);
//    if (socket_fd == INVALID_SOCKET) {
//        perror("Accepting connection failed");
//        closesocket(server_socket_fd);
//        WSACleanup();
//        return 1;
//    }
//
//    int max_packets;
//    printf("Enter the number of packets: ");
//    scanf("%d", &max_packets);
//    struct Packet received_packets[max_packets];
//    
//    while (1) {
//        struct Packet packet;
//        if (recv(socket_fd, (char *)&packet, sizeof(packet), 0) != SOCKET_ERROR) {
//            if (packet.seq_num >= 0 && packet.seq_num < max_packets) {
//                if (!received_packets[packet.seq_num].ack) {
//                    printf("\nReceived packet %d with data %c", packet.seq_num + 1, packet.data);
//                    received_packets[packet.seq_num] = packet;
//                    
//                    // Simulate packet loss (acknowledgment not sent)
//                    // if (packet.seq_num != 2) {
//                    packet.ack = true;
//                    send(socket_fd, (char *)&packet, sizeof(packet), 0);
//                    printf("\nSent acknowledgment for packet %d", packet.seq_num + 1);
//                    // }
//                }
//            }
//        }
//    }
//
//    closesocket(socket_fd);
//    closesocket(server_socket_fd);
//    WSACleanup();
//    return 0;
//}

//#include <stdio.h>
//#include<string.h>
//#include<sys/types.h>
//#include<sys/socket.h>
//#include<netinet/in.h
//#include<netdb.h>
//#include<time.h>
//#include<math.h>
//
//#define SERV_TCfl_flORT 5035
//
//void delay(int number_of_seconds)
//{
//int milli_seconds = 1000 * number_of_seconds;
//clock_t start_time = clock();
//while (clock() < start_time + milli_seconds)
//;
//
//}
//int main( int argc, char **argv)
//{
//int sockfd,newsockfd,clength;
//struct sockaddr_in serv_addr,cli_addr;
//sockfd=socket(AF_INET,SOCK_STREAM,0);
//serv_addr.s n_fam ly=AF_INET;
//serv_addr.s n_addr.s_addr=INADDR_ANY;
//serv_addr.s n_port=htons(SERV_TCfl_flORT);
//pr ntf("\nSocket ng Successful !!!\n");
//bind(sockfd,(struct sockaddr*)&serv_addr,s zeof(serv_addr));
//listen(sockfd,5);
//clength=sizeof(cli_addr);
//newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&clength);
//char data[80],data2[9]="",final[100]="",final2[100]="",f[3],temp[2];
//
//int index_server=0, index_client=0,m,Tp,Tt,tmax,wait_time,total_time,data_len,max_packets_sent,
//wind_size,index=0,k=0,j=0,frame_number=0,pos=0,ack=0,i,wind_size2[2], index_data_lost,flag=0; 
//printf("Enter Data Frame:");
//scanf("%s",data);
//printf("\nData Frame to be sent:%s",data);
//
//printf("\nEnter the Window S ze:");
//scanf("%d",&wind_size);
//printf("\nEnter the index for Error:");
//scanf("%d",& index_data_lost);
//wind_size2[0]=wind_size;
//wind_size2[1]=index_data_lost;
//write(newsockfd,wind_size2,2);
//write(newsockfd,data,80);
//for (int i= 0; i<wind_size;i++)
//{
//temp[0]=data[i];
//write(newsockfd,temp,2);
//printf("\ frame:%d", i+1);
//delay(10);
//index++;
//}
//wait_time=10;
//delay(wait_time);
//index=wind_size;
//
//while( index<strlen(data))
//{
//if(ack== index_data_lost && flag==0)
//{
//printf("\nTimeout!No Acknowledgement Received from the Client");
//temp[0]=data[ack];
//write(newsockfd,temp,2);
//printf("Sending frame:%d",ack+1);
//delay(10);
//flag=1;
//}
//if(ack!= index_data_lost || flag==1){
//printf("Postive Acknowledgement of frame %d Received from the Client",ack+1);
//printf("\nSednig frame:%d",index+1);
//ack++;
//temp[0]=data[index];
//i++;
//write(newsockfd,temp,2);
//delay(wait_time);
//index++;
//}
//}
//while (ack<strlen(data))
//{
//printf("\n Postive Acknowledgement of frame %d Received from the Client",ack+1);
//ack++;
//}
//close(sockfd);
//return 0;
//}

#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <time.h>

#define SERV_TCP_PORT 5035

void delay(int number_of_seconds) {
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

int main(int argc, char** argv) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed!\n");
        return 1;
    }

    int sockfd, newsockfd, clength;
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(SERV_TCP_PORT);

    printf("\nSocket created successfully!\n");

    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        fprintf(stderr, "Binding failed!\n");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    listen(sockfd, 5);
    clength = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clength);

    char data[80], data2[9] = "", final[100] = "", final2[100] = "", f[3], temp[2];

    int index_server = 0, index_client = 0, m, Tp, Tt, tmax, wait_time, total_time, data_len,
        max_packets_sent, wind_size, index = 0, k = 0, j = 0, frame_number = 0, pos = 0,
        ack = 0, i, wind_size2[2], index_data_lost, flag = 0;

    printf("Enter Data Frame:");
    scanf("%s", data);
    printf("\nData Frame to be sent:%s", data);

    printf("\nEnter the Window Size:");
    scanf("%d", &wind_size);
    printf("\nEnter the Index for Error:");
    scanf("%d", &index_data_lost);
    wind_size2[0] = wind_size;
    wind_size2[1] = index_data_lost;
    write(newsockfd, wind_size2, 2);
    write(newsockfd, data, 80);
    
    for (i = 0; i < wind_size; i++) {
        temp[0] = data[i];
        write(newsockfd, temp, 2);
        printf("\nFrame:%d", i + 1);
        delay(10);
        index++;
    }

    wait_time = 10;
    delay(wait_time);
    index = wind_size;

    while (index < strlen(data)) {
        if (ack == index_data_lost && flag == 0) {
            printf("\nTimeout! No Acknowledgment Received from the Client");
            temp[0] = data[ack];
            write(newsockfd, temp, 2);
            printf("Sending frame:%d", ack + 1);
            delay(10);
            flag = 1;
        }
        if (ack != index_data_lost || flag == 1) {
            printf("Positive Acknowledgment of frame %d Received from the Client", ack + 1);
            printf("\nSending frame:%d", index + 1);
            ack++;
            temp[0] = data[index];
            i++;
            write(newsockfd, temp, 2);
            delay(wait_time);
            index++;
        }
    }

    while (ack < strlen(data)) {
        printf("\nPositive Acknowledgment of frame %d Received from the Client", ack + 1);
        ack++;
    }

    closesocket(sockfd);
    closesocket(newsockfd);
    WSACleanup();
    return 0;
}
