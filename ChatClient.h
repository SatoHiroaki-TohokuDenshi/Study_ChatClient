#pragma once

#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment( lib, "ws2_32.lib" )

using std::string;

class ChatClient {
private:
	unsigned short serverPort_;		//ポート番号
	unsigned int messageLength_;	//最大文字数

	SOCKET sock_;

	string serverIP_;
	SOCKADDR_IN toAddr_;
	int tolen_;
public:
	ChatClient();
	ChatClient(unsigned short port);
	ChatClient(unsigned short port, unsigned int length);
	~ChatClient();

	///// 初期化 /////
	bool InitWinSock();
	bool InitSocket();
	bool SetServerIP();

	///// メインループ /////
	bool Loop();

	///// 解放 /////
	bool ReleaseSocket();
	bool ReleaseWinSock();
};