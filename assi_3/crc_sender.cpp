#include <iostream>
#include <bits/stdc++.h>
#include <winsock2.h>

using namespace std;
string XOR(string a, string b) {
    string result = "";
    int n = b.length();
    for (int i = 1; i < n; i++) {
        if (a[i] == b[i])
            result += "0";
        else
            result += "1";
    }
    return result;
}

string binDiv(string dividend, string divisor) {
    int pick = divisor.length();
    string tmp = dividend.substr(0, pick);
    int n = dividend.length();

    while (pick < n) {
        if (tmp[0] == '1') {
            tmp = XOR(divisor, tmp) + dividend[pick];
        } else {
            tmp = XOR(string(pick, '0'), tmp) + dividend[pick];
        }
        pick += 1;
    }

    if (tmp[0] == '1') {
        tmp = XOR(divisor, tmp);
    } else {
        tmp = XOR(string(pick, '0'), tmp);
    }
    return tmp;
}

string encode(string data, string key) {
    int k_length = key.length();
    string appended_data = (data + string(k_length - 1, '0'));
    string rem = binDiv(appended_data, key);
    string ans = data + rem;
    cout << "\nRemainder: " << rem;
    cout << "\nEncoded data : " << ans;
    return ans;
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
       string data,key,res;
	cout<<"Enter data to be encoded: ";
	cin>>data;
	cout<<"\nEnter key: ";
	cin>>key;  
    string ans = encode(data,key);
    cout << endl;

    send(sockfd, ans.c_str(), ans.size(), 0);

    closesocket(sockfd);
    WSACleanup();

    return 0;
}
