#include "ChatClient.h"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

ChatClient::ChatClient()
	:serverPort_(8888), messageLength_(1024),
	sock_(), toAddr_(), tolen_(sizeof(toAddr_))
{
}

ChatClient::ChatClient(unsigned short port)
	:serverPort_(port), messageLength_(1024),
	sock_(), toAddr_(), tolen_(sizeof(toAddr_))
{
}

ChatClient::ChatClient(unsigned short port, unsigned int length)
	:serverPort_(port), messageLength_(length),
	sock_(), toAddr_(), tolen_(sizeof(toAddr_))
{
}

ChatClient::~ChatClient() {
}

bool ChatClient::InitWinSock() {
	//WinSock本体
	WSADATA wsaData;

	//初期化
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);

	return (ret != 0);
}

bool ChatClient::InitSocket() {
	sock_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	return (sock_ == INVALID_SOCKET);
}

bool ChatClient::SetServerIP() {
	serverIP_ = "";
	cout << "Input Server IPv4 Address : ";
	cin >> serverIP_;

	//通信先情報の格納
	tolen_ = sizeof(toAddr_);
	memset(&toAddr_, 0, sizeof(toAddr_));
	toAddr_.sin_family = AF_INET;
	toAddr_.sin_port = htons(serverPort_);
	return (inet_pton(AF_INET, serverIP_.c_str(), &toAddr_.sin_addr.s_addr) != 1);
}

bool ChatClient::Loop() {
	while (true) {
		///// メッセージ送信 /////
		//char message[];	//メッセージ
		//std::cout << "Input Message : ";
		//cin >> message;
		string message;
		message.resize(messageLength_);//上限値をサーバと合わせる
		std::cout << "Input Message : ";
		cin >> message;
		//std::getline(cin, message);

		if (sendto(sock_, message.c_str(), messageLength_, 0, (SOCKADDR*)&toAddr_, tolen_) == SOCKET_ERROR) {
			cout << "Error : sendto" << endl;
			return false;
		}

		///// メッセージ受信 /////
		//上限値をサーバと合わせる
		char* buff = new char[messageLength_];	//受取用バッファ

		SOCKADDR_IN fromAddr;
		int fromlen = sizeof(fromAddr);
		if (recvfrom(sock_, buff, messageLength_, 0, (SOCKADDR*)&fromAddr, &fromlen) == SOCKET_ERROR) {
			cout << "Error : Recieve Message" << endl;
			delete[] buff;
			return false;
		}
		else {
			//表示
			cout << "Receive Message : " << buff << endl;
			delete[] buff;
		}

		string tmp = "";
		cout << "Want to Close Connection? (Y / N) : ";
		cin >> tmp;
		if (tmp == "Y") {
			cout << "Now Closing Connection..." << endl;
			break;
		}
	}
	return true;
}

bool ChatClient::ReleaseSocket() {
	return (closesocket(sock_) == SOCKET_ERROR);
}

bool ChatClient::ReleaseWinSock()
{
	return (WSACleanup() != 0);
}
