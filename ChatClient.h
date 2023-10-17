#pragma once

#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment( lib, "ws2_32.lib" )

using std::string;

class ChatClient {
private:
	unsigned short serverPort_;		//ƒ|[ƒg”Ô†
	unsigned int messageLength_;	//Å‘å•¶š”

	SOCKET sock_;

	string serverIP_;
	SOCKADDR_IN toAddr_;
	int tolen_;
public:
	ChatClient();
	ChatClient(unsigned short port);
	ChatClient(unsigned short port, unsigned int length);
	~ChatClient();

	bool InitWinSock();
	bool InitSocket();
	bool SetServerIP();

	bool Loop();

public:
	bool ReleaseSocket();
	bool ReleaseWinSock();
};