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
//    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
//    if (sockfd == INVALID_SOCKET) {
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
//    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
//        perror("Connection failed");
//        closesocket(sockfd);
//        WSACleanup();
//        return 1;
//    }
//
//    int max_packets, i = 0;
//    printf("Enter the number of packets: ");
//    scanf("%d", &max_packets);
//    char data[max_packets];
//    
//    // Initialize data array, for example:
//    for (i = 0; i < max_packets; i++) {
//        printf("Enter the %d packet's Data: ", i + 1);
//        scanf(" %c", &data[i]);
//    }
//
//    int base = 0;
//    int next_seq_num = 0;
//    struct Packet packets[WINDOW_SIZE];
//    
//    while (base < max_packets) {
//        // Send packets within the window
//        while (next_seq_num < base + WINDOW_SIZE && next_seq_num < max_packets) {
//            struct Packet packet;
//            packet.seq_num = next_seq_num;
//            packet.data = data[next_seq_num];
//            packet.ack = false;
//            
//            send(sockfd, (char *)&packet, sizeof(packet), 0);
//            printf("\nPacket %d sent with data %c", packet.seq_num + 1, packet.data);
//            
//            packets[next_seq_num % WINDOW_SIZE] = packet;
//            next_seq_num++;
//        }
//        
//        // Receive acknowledgments
//        struct Packet ack_packet;
//        if (recv(sockfd, (char *)&ack_packet, sizeof(ack_packet), 0) != SOCKET_ERROR) {
//            if (ack_packet.ack) {
//                printf("\nReceived acknowledgment for packet %d", ack_packet.seq_num + 1);
//                base = ack_packet.seq_num + 1;
//            }
//        }
//    }
//
//    closesocket(sockfd);
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
//connect(sockfd,(struct sockaddr*)&serv_addr,size_of(serv_addr));
//read(sockfd,wind_size2,2);
//read(sockfd,data,80);
//strcpy(final,data);
//wind_size=wind_size2[0];
//index_data_lost=wind_size2[1];
//for (i= 0; i<wind_size;i++)
//{
//read(sockfd,temp,2);
//data[i]=temp[0];
//printf("\n Received frame:%d"i+1);
//delay(10);
//index++;
//}
//wait_time=10;
//delay(wait_time);
//index=wind_size;
//
//while( index<strlen(data))
//{
//if(ack== index_data_lost || flag==0)
//{
//read(sockfd,temp,2);
//data[ack]=temp[0];
//delay(10);
//flag=1;
//}
//if(ack!= ndex_data_lost || flag==1)
//{
//ack++;
//i++;
//read(sockfd,temp,2);
//data[index]=temp[0];
//printf("\n Received frame:%d",index+1);
//delay(wait_time);
//index++;
//}
//}
//printf("\nFinal data:%s\n",final);
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

    read(newsockfd, wind_size2, 2);
    read(newsockfd, data, 80);
    strcpy(final, data);
    wind_size = wind_size2[0];
    index_data_lost = wind_size2[1];

    for (i = 0; i < wind_size; i++) {
        read(newsockfd, temp, 2);
        data[i] = temp[0];
        printf("\n Received frame:%d", i + 1);
        delay(10);
        index++;
    }

    wait_time = 10;
    delay(wait_time);
    index = wind_size;

    while (index < strlen(data)) {
        if (ack == index_data_lost || flag == 0) {
            read(newsockfd, temp, 2);
            data[ack] = temp[0];
            delay(10);
            flag = 1;
        }
        if (ack != index_data_lost || flag == 1) {
            ack++;
            i++;
            read(newsockfd, temp, 2);
            data[index] = temp[0];
            printf("\n Received frame:%d", index + 1);
            delay(wait_time);
            index++;
        }
    }

    printf("\nFinal data:%s\n", final);
    closesocket(sockfd);
    closesocket(newsockfd);
    WSACleanup();
    return 0;
}
