#include <iostream>
#include <WinSock2.h>

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

    SOCKET server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_fd == INVALID_SOCKET) {
        cerr << "Socket creation failed" << endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        cerr << "Binding failed" << endl;
        closesocket(server_socket_fd);
        WSACleanup();
        return 1;
    }

    if (listen(server_socket_fd, 1) == SOCKET_ERROR) {
        cerr << "Listening failed" << endl;
        closesocket(server_socket_fd);
        WSACleanup();
        return 1;
    }

    sockaddr_in client_addr;
    int client_len = sizeof(client_addr);
    SOCKET socket_fd = accept(server_socket_fd, (struct sockaddr*)&client_addr, &client_len);
    if (socket_fd == INVALID_SOCKET) {
        cerr << "Accepting connection failed" << endl;
        closesocket(server_socket_fd);
        WSACleanup();
        return 1;
    }

    int receivedMsg[7];
    recv(socket_fd, (char*)receivedMsg, sizeof(receivedMsg), 0);

    int d3 = receivedMsg[0];
    int d2 = receivedMsg[1];
    int d1 = receivedMsg[2];
    int p2 = receivedMsg[3];
    int d0 = receivedMsg[4];
    int p1 = receivedMsg[5];
    int p0 = receivedMsg[6];

    cout << "\nReceived Message: ";
    for (int i = 0; i < 7; i++) {
        cout << receivedMsg[i] << " ";
    }

    int receivedData[4] = { d3, d2, d1, d0 };
    int receivedParity[3] = { p0, p1, p2 };

    int calculatedParity[3];
    calculateParity(receivedData, calculatedParity);

    int errorBit = 0;
    for (int i = 0; i < 3; i++) {
        if (receivedParity[i] != calculatedParity[i]) {
            errorBit += (1 << i);
        }
    }

    if (errorBit > 0) {
        cout << "Error detected at bit position: " << errorBit << endl;
        receivedData[errorBit - 1] ^= 1;
    }
    else {
        cout << "\nNo Error Detected." << endl;
        cout << "Decoded message: " << receivedData[0] << " " << receivedData[1] << " " << receivedData[2] << " " << receivedData[3] << endl;
    }

    closesocket(socket_fd);
    closesocket(server_socket_fd);
    WSACleanup();

    return 0;
}
