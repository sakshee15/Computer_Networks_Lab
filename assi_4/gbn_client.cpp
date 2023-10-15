//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//#include <Winsock2.h>
//#include <windows.h> // Add this header for Sleep function
//
//#pragma comment(lib, "ws2_32.lib")
//
//using namespace std;
//
//struct Packet {
//    int sequenceNumber;
//};
//
//int main() {
//    WSADATA wsaData;
//    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
//        cerr << "WSAStartup failed" << endl;
//        return -1;
//    }
//
//    SOCKET senderSocket = socket(AF_INET, SOCK_DGRAM, 0);
//    if (senderSocket == INVALID_SOCKET) {
//        cerr << "Error creating socket" << endl;
//        WSACleanup();
//        return -1;
//    }
//
//    sockaddr_in receiverAddr;
//    receiverAddr.sin_family = AF_INET;
//    receiverAddr.sin_port = htons(8080); // Change to the receiver's port.
//    receiverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Change to receiver's IP.
//
//    int totalFrames;
//    int windowSize;
//    cout << "Enter the Total number of frames: ";
//    cin >> totalFrames;
//    cout << "Enter the Window Size: ";
//    cin >> windowSize;
//
//    int base = 0;
//    int nextSeqNum = 0;
//
//    while (base < totalFrames) {
//        while (nextSeqNum < base + windowSize && nextSeqNum < totalFrames) {
//            Packet packet;
//            packet.sequenceNumber = nextSeqNum;
//            sendto(senderSocket, (const char*)&packet, sizeof(packet), 0, (const sockaddr*)&receiverAddr, sizeof(receiverAddr));
//            cout << "Sent Frame " << nextSeqNum << endl;
//            nextSeqNum++;
//            Sleep(2000); // Add a 1-second delay between sending frames
//        }
//
//        fd_set readSet;
//        FD_ZERO(&readSet);
//        FD_SET(senderSocket, &readSet);
//
//        timeval timeout;
//        timeout.tv_sec = 5; // Set your timeout value here.
//        timeout.tv_usec = 0;
//
//        int ready = select(0, &readSet, NULL, NULL, &timeout);
//
//        if (ready == SOCKET_ERROR) {
//            cerr << "Error in select" << endl;
//            closesocket(senderSocket);
//            WSACleanup();
//            return -1;
//        } else if (ready == 0) {
//            // Timeout occurred, retransmit frames in the window.
//            cout << "Timeout! Retransmitting window..." << endl;
//            nextSeqNum = base;
//        } else {
//            // Acknowledgment received.
//            Packet ack;
//            recvfrom(senderSocket, (char*)&ack, sizeof(ack), 0, NULL, NULL);
//            cout << "Received Acknowledgment for Frame " << ack.sequenceNumber << endl;
//            base = ack.sequenceNumber + 1;
//        }
//    }
//
//    closesocket(senderSocket);
//    WSACleanup();
//    return 0;
//}

#include <iostream>
#include <Winsock2.h>
#include <windows.h> // Add this header for Sleep function

#pragma comment(lib, "ws2_32.lib")

using namespace std;

const int MAX_FRAMES = 100; // Maximum number of frames to send

struct Packet {
    int sequenceNumber; // Data field with the sequence number.
};

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed" << endl;
        return -1;
    }

    SOCKET senderSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (senderSocket == INVALID_SOCKET) {
        cerr << "Error creating socket" << endl;
        WSACleanup();
        return -1;
    }

    sockaddr_in receiverAddr;
    receiverAddr.sin_family = AF_INET;
    receiverAddr.sin_port = htons(8080); // Change to the receiver's port.
    receiverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Change to receiver's IP.

    int totalFrames; // Number of frames to send.
    int windowSize; // Sender window size.
    int errorFrame; // Sequence number of a frame to introduce an error.

    cout << "Enter the total number of frames: ";
    cin >> totalFrames;
    cout << "Enter the sender window size: ";
    cin >> windowSize;
    cout << "Enter the frame number to introduce an error (or -1 for no error): ";
    cin >> errorFrame;

    int base = 0; // Base of the sender window.
    int nextSeqNum = 0; // Next sequence number to be sent.
    int timeout = 5000; // Timeout duration in milliseconds.

    while (base < totalFrames) {
        while (nextSeqNum < base + windowSize && nextSeqNum < totalFrames) {
Packet packet;
    packet.sequenceNumber = nextSeqNum;

    // Introduce an error in the specified frame.
    if (packet.sequenceNumber == errorFrame) {
        packet.sequenceNumber = -1;
        errorFrame=100;
    }

    sendto(senderSocket, (const char*)&packet, sizeof(packet), 0, (const sockaddr*)&receiverAddr, sizeof(receiverAddr));
    cout << "Sent Frame with Sequence Number " << packet.sequenceNumber << endl;
    
    // Update the sequence number here:
    if (packet.sequenceNumber == -1) {
        	packet.sequenceNumber=nextSeqNum;
    }
    nextSeqNum++;
    
    Sleep(2000);
        }

        fd_set readSet;
        FD_ZERO(&readSet);
        FD_SET(senderSocket, &readSet);

        timeval timeoutVal;
        timeoutVal.tv_sec = timeout / 1000;
        timeoutVal.tv_usec = (timeout % 1000) * 1000;

        int ready = select(0, &readSet, NULL, NULL, &timeoutVal);

        if (ready == SOCKET_ERROR) {
            cerr << "Error in select" << endl;
            closesocket(senderSocket);
            WSACleanup();
            return -1;
        } else if (ready == 0) {
            // Timeout occurred, retransmit frames in the window.
            cout << "Timeout! Retransmitting window..." << endl;
            nextSeqNum = base;

            // Retransmit frames from the base to the last sent frame.
            while (base < nextSeqNum) {
                Packet packet;
                packet.sequenceNumber = base;

                // Introduce an error in the specified frame.
                if (packet.sequenceNumber == errorFrame) {
                    packet.sequenceNumber = -1;
                    errorFrame =1000;
                }

                sendto(senderSocket, (const char*)&packet, sizeof(packet), 0, (const sockaddr*)&receiverAddr, sizeof(receiverAddr));
                cout << "Retransmitted Frame with Sequence Number " << packet.sequenceNumber << endl;
                base++;
            }
        } else {
            // Acknowledgment received.
            Packet ack;
            recvfrom(senderSocket, (char*)&ack, sizeof(ack), 0, NULL, NULL);
            cout << "Received Acknowledgment for Frame with Sequence Number " << ack.sequenceNumber << endl;
            base = ack.sequenceNumber + 1;
        }
    }

    closesocket(senderSocket);
    WSACleanup();
    return 0;
}

//#include <iostream>
//#include <Winsock2.h>
//#include <windows.h> // Add this header for Sleep function
//
//#pragma comment(lib, "ws2_32.lib")
//
//using namespace std;
//
//const int MAX_FRAMES = 100; // Maximum number of frames to send
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
//    SOCKET senderSocket = socket(AF_INET, SOCK_DGRAM, 0);
//    if (senderSocket == INVALID_SOCKET) {
//        cerr << "Error creating socket" << endl;
//        WSACleanup();
//        return -1;
//    }
//
//    sockaddr_in receiverAddr;
//    receiverAddr.sin_family = AF_INET;
//    receiverAddr.sin_port = htons(8080); // Change to the receiver's port.
//    receiverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Change to receiver's IP.
//
//    int totalFrames; // Number of frames to send.
//    int windowSize; // Sender window size.
//    int errorFrame; // Sequence number of a frame to introduce an error.
//
//    cout << "Enter the total number of frames: ";
//    cin >> totalFrames;
//    cout << "Enter the sender window size: ";
//    cin >> windowSize;
//    cout << "Enter the frame number to introduce an error (or -1 for no error): ";
//    cin >> errorFrame;
//
//    int base = 0; // Base of the sender window.
//    int nextSeqNum = 0; // Next sequence number to be sent.
//    int timeout = 5000; // Timeout duration in milliseconds.
//
//    while (base < totalFrames) {
//        while (nextSeqNum < base + windowSize && nextSeqNum < totalFrames) {
//            Packet packet;
//            packet.sequenceNumber = nextSeqNum;
//
//            // Introduce an error in the specified frame.
//            if (packet.sequenceNumber == errorFrame) {
//                packet.sequenceNumber = -1;
//                errorFrame = 100; // Advance errorFrame
//            }
//
//            // Send the packet
//            sendto(senderSocket, (const char*)&packet, sizeof(packet), 0, (const sockaddr*)&receiverAddr, sizeof(receiverAddr));
//            cout << "Sent Frame with Sequence Number " << packet.sequenceNumber << endl;
//            
//            // Update the sequence number here:
//            if (packet.sequenceNumber == -1) {
//                packet.sequenceNumber = nextSeqNum;
//            }
//            nextSeqNum++;
//            
//            Sleep(2000); // Add a delay between sending frames
//        }
//
//        fd_set readSet;
//        FD_ZERO(&readSet);
//        FD_SET(senderSocket, &readSet);
//
//        timeval timeoutVal;
//        timeoutVal.tv_sec = timeout / 1000;
//        timeoutVal.tv_usec = (timeout % 1000) * 1000;
//
//        int ready = select(0, &readSet, NULL, NULL, &timeoutVal);
//
//        if (ready == SOCKET_ERROR) {
//            cerr << "Error in select" << endl;
//            closesocket(senderSocket);
//            WSACleanup();
//            return -1;
//        } else if (ready == 0) {
//            // Timeout occurred, retransmit frames in the window.
//            cout << "Timeout! Retransmitting window..." << endl;
//            nextSeqNum = base;
//
//            // Retransmit frames from the base to the last sent frame.
//            while (base < nextSeqNum) {
//                Packet packet;
//                packet.sequenceNumber = base;
//
//                // Retransmit the packet
//                sendto(senderSocket, (const char*)&packet, sizeof(packet), 0, (const sockaddr*)&receiverAddr, sizeof(receiverAddr));
//                cout << "Retransmitted Frame with Sequence Number " << packet.sequenceNumber << endl;
//                base++;
//            }
//        } else {
//            // Acknowledgment received.
//            Packet ack;
//            recvfrom(senderSocket, (char*)&ack, sizeof(ack), 0, NULL, NULL);
//            cout << "Received Acknowledgment for Frame with Sequence Number " << ack.sequenceNumber << endl;
//            base = ack.sequenceNumber + 1;
//        }
//    }
//
//    closesocket(senderSocket);
//    WSACleanup();
//    return 0;
//}
