#include <iostream>
#include <cstdlib>
#include <Winsock2.h>
#include <windows.h> // Add this header for Sleep function

#pragma comment(lib, "ws2_32.lib")

using namespace std;

struct Packet {
    int sequenceNumber;
};

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed" << endl;
        return -1;
    }

    SOCKET receiverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (receiverSocket == INVALID_SOCKET) {
        cerr << "Error creating socket" << endl;
        WSACleanup();
        return -1;
    }

    sockaddr_in receiverAddr;
    receiverAddr.sin_family = AF_INET;
    receiverAddr.sin_port = htons(8080); // Set to the desired port.
    receiverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(receiverSocket, (const sockaddr*)&receiverAddr, sizeof(receiverAddr)) == SOCKET_ERROR) {
        cerr << "Error binding socket" << endl;
        closesocket(receiverSocket);
        WSACleanup();
        return -1;
    }

    int expectedSeqNum = 0;

    while (true) {
        Packet packet;
        int addrLen = sizeof(receiverAddr);
        recvfrom(receiverSocket, (char*)&packet, sizeof(packet), 0, (sockaddr*)&receiverAddr, &addrLen);

        // Process the received packet (frame number).
        cout << "Received Frame " << packet.sequenceNumber << endl;
        Sleep(2000); // Add a 1-second delay between receiving frames

        // Send acknowledgment.
        sendto(receiverSocket, (const char*)&packet, sizeof(packet), 0, (const sockaddr*)&receiverAddr, sizeof(receiverAddr));
        cout << "Sent Acknowledgment for Frame " << packet.sequenceNumber << endl;

        expectedSeqNum++;
    }

    closesocket(receiverSocket);
    WSACleanup();
    return 0;
}

//#include <iostream>
//#include <Winsock2.h>
//#include <windows.h> // Add this header for Sleep function
//#include <vector>
//
//#pragma comment(lib, "ws2_32.lib")
//
//using namespace std;
//
//const int MAX_FRAMES = 100; // Maximum number of frames to receive
//
//struct Packet {
//    int sequenceNumber; // Data field with the sequence number.
//};
//
//int main() {
//    WSADATA wsaData;
//    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
//        cerr << "WSAStartup failed" << endl;
//        return -1;
//    }
//
//    SOCKET receiverSocket = socket(AF_INET, SOCK_DGRAM, 0);
//    if (receiverSocket == INVALID_SOCKET) {
//        cerr << "Error creating socket" << endl;
//        WSACleanup();
//        return -1;
//    }
//
//    sockaddr_in receiverAddr;
//    receiverAddr.sin_family = AF_INET;
//    receiverAddr.sin_port = htons(8080); // Set to the desired port.
//    receiverAddr.sin_addr.s_addr = INADDR_ANY;
//
//    if (bind(receiverSocket, (const sockaddr*)&receiverAddr, sizeof(receiverAddr)) == SOCKET_ERROR) {
//        cerr << "Error binding socket" << endl;
//        closesocket(receiverSocket);
//        WSACleanup();
//        return -1;
//    }
//
//    int expectedSeqNum = 0;
//
//    while (expectedSeqNum < MAX_FRAMES) {
//        Packet packet;
//        int addrLen = sizeof(receiverAddr);
//        recvfrom(receiverSocket, (char*)&packet, sizeof(packet), 0, (sockaddr*)&receiverAddr, &addrLen);
//
//        if (packet.sequenceNumber == expectedSeqNum) {
//            // Process the received packet (frame number).
//            cout << "Received Frame with Sequence Number " << packet.sequenceNumber << endl;
//            Sleep(2000); // Add a delay between receiving frames
//
//            // Send acknowledgment.
//            sendto(receiverSocket, (const char*)&packet, sizeof(packet), 0, (const sockaddr*)&receiverAddr, sizeof(receiverAddr));
//            cout << "Sent Acknowledgment for Frame with Sequence Number " << packet.sequenceNumber << endl;
//
//            expectedSeqNum++;
//        } else {
//            // Out-of-sequence frame, request retransmission.
//            cout << "Out-of-Sequence Frame received, requesting retransmission..." << endl;
//            Packet ack;
//            ack.sequenceNumber = expectedSeqNum - 1; // Acknowledge the last correctly received frame.
//            sendto(receiverSocket, (const char*)&ack, sizeof(ack), 0, (const sockaddr*)&receiverAddr, sizeof(receiverAddr));
//        }
//    }
//
//    closesocket(receiverSocket);
//    WSACleanup();
//    return 0;
//}
//
//
