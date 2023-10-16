#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment( lib, "ws2_32.lib" )

///// 定数宣言 /////
const unsigned short SERVER_PORT = 8888;	//ポート番号
const unsigned int MESSAGE_LENGTH = 1024;	//送受信の最大文字数

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() {
	//結果格納用変数
	int result = 0;

	//WinSock本体
	WSADATA wsaData;

	//初期化
	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		cout << "Error : WSAStartUp" << endl;
		return -1;
	}

	//ソケットディスクリプタ
	SOCKET sock;

	//UDPソケット作成
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET) {
		cout << "Error : Socket" << endl;
		return -1;
	}


	//通信先を入力
	string serverIP = "";
	cout << "Input Server IPv4 Address : ";
	cin >> serverIP;

	//通信先情報の格納
	SOCKADDR_IN toAddr;
	const int tolen = sizeof(toAddr);
	memset(&toAddr, 0, sizeof(toAddr));
	toAddr.sin_family = AF_INET;
	toAddr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, serverIP.c_str(), &toAddr.sin_addr.s_addr);

	//メインループ
	while (true) {
		string message;
		message.resize(MESSAGE_LENGTH);//上限値をサーバと合わせる
		std::cout << "Input Message : ";
		std::getline(cin, message);

		result = sendto(sock, message.c_str(), MESSAGE_LENGTH, 0, (SOCKADDR*)&toAddr, tolen);
		if (result == SOCKET_ERROR) {
			cout << "Error : sendto" << endl;
			return -1;
		}
	}

	//ソケットの後処理
	result = closesocket(sock);
	if (result == SOCKET_ERROR) {
		cout << "Error : closesocket" << endl;
		return -1;
	}

	//WinSockの後処理
	result = WSACleanup();
	if (result != 0) {
		cout << "Error : WSACleanup" << endl;
		return -1;
	}

	return 0;
}