#include <iostream>
#include <bits/stdc++.h>
#include <WinSock2.h>

using namespace std;

string XOR(string a, string b){
     string result = "";
     int n= b.length();
     for(int i=1;i<n;i++){
     	if(a[i]==b[i]) result+='0';
	else result+='1';
     }
     return result;
}

string binDiv(string divD,string divS){  //divD = dividend & divS= divisor
     int n = divS.length();
     string tmp = divD.substr(0,n);
     int len = divD.length();
     while(n<len){
     	if(tmp[0]=='1'){
     		tmp = XOR(divS,tmp) + divD[n];
	}else{
	    tmp = XOR(std::string(n,'0'),tmp) + divD[n]; 
       tmp += divD[n]; 	
	}
	
	n++;
     }
     
     if(tmp[0]=='1'){
     		tmp = XOR(divS,tmp);
	}else{
	    tmp = XOR(std::string(n,'0'),tmp); 	
	}
	return tmp;
     
	
	
}

bool decode(string data,string key){
       int k_length = key.length();
	string rem = binDiv(data,key);
	if(!rem.find('1')){
		return  true;
	}else{
		return false;
	}
	
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

    string receivedData(1024, '\0'); // Buffer to receive data
    string key;
int bytesReceived = recv(socket_fd, &receivedData[0], receivedData.size(), 0);

if (bytesReceived > 0) {
    string receivedMessage = receivedData.substr(0, bytesReceived);
    cout << "\nReceived Message: " << receivedMessage << endl;

    cout << "\nEnter key: ";
    cin >> key;
    bool error = decode(receivedMessage, key);

    if (error) {
        cout << "\nError detected in the received message." << endl;
    } else {
        cout << "\nNo Error Detected." << endl;
    }
} else {
    cout << "\nError receiving data" << endl;
}

    closesocket(socket_fd);
    closesocket(server_socket_fd);
    WSACleanup();

    return 0;
}
