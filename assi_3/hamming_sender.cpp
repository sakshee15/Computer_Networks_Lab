#include <iostream>
#include <winsock2.h>

using namespace std;

void calculateParity(int data[4], int parity[3]) {
    parity[0] = data[0] ^ data[1] ^ data[3];
    parity[1] = data[0] ^ data[2] ^ data[3];
    parity[2] = data[1] ^ data[2] ^ data[3];
}

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed" << endl;
        return 1;
    }

    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET) {
        cerr << "Socket creation failed" << endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        cerr << "Connection failed" << endl;
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    cout << "Enter a 4-bit message: ";
    char m[5];
    cin >> m;

    int d0 = m[3] - '0';
    int d1 = m[2] - '0';
    int d2 = m[1] - '0';
    int d3 = m[0] - '0';

    int data[4] = { d3, d2, d1, d0 };
    int parity[3];
    calculateParity(data, parity);

    int hammingMsg[7];
    hammingMsg[0] = d3;
    hammingMsg[1] = d2;
    hammingMsg[2] = d1;
    hammingMsg[3] = parity[2];
    hammingMsg[4] = d0;
    hammingMsg[5] = parity[1];
    hammingMsg[6] = parity[0];

    cout << "\nMessage with Hamming code: ";
    for (int i = 0; i < 7; i++) {
        cout << hammingMsg[i] << " ";
    }
    cout << endl;

    send(sockfd, (char*)hammingMsg, sizeof(hammingMsg), 0);

    closesocket(sockfd);
    WSACleanup();

    return 0;
}
