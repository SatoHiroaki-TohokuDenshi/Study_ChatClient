/*
WSAStartup()	// WinSock初期化
socket()		// ソケット作成
サーバのソケットアドレス情報をセット
while(true)
{
	送信メッセージ入力
	sendto();	// 送信
	recvfrom();	// 受信
	出力
}
closesocket()		// ソケット破棄
WSACleanup()		// WinSock終了処理
*/

#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment( lib, "ws2_32.lib" )

using std::cout;
using std::endl;

// ポート番号
const unsigned short SERVERPORT = 8888;

// 送受信するメッセージの最大値
const unsigned int MESSAGELENGTH = 1024;

// プロトタイプ宣言
int InitWinSock();
//void SetServerIP(SOCKADDR_IN& sIP);

int main() {
	cout << "You are Chat Client" << endl;

	//初期化の結果を格納する変数
	int ret;

	// WinSockの初期化
	ret = InitWinSock();
	if (ret != 0) {
		cout << "WinSock Initializing Error";
		return -1;
	}
	cout << "Initialize WinSock is Success";

	// ソケットディスクリプタ
	SOCKET sock;

	// UDPソケット作成
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock < 0) {
		cout << "Socket Creation Error" << endl;
		return -1;
	}
	cout << "Create Socket is Success";

	// 接続先サーバのIPアドレスを入力させる
	std::string serverIpAddress;
	std::cout << "Input Server IPv4 address :";
	std::cin >> serverIpAddress;

	// 接続先サーバのソケットアドレス情報格納
	SOCKADDR_IN toAddr;
	const int tolen = sizeof(toAddr);
	memset(&toAddr, 0, sizeof(toAddr));
	toAddr.sin_family = AF_INET;
	toAddr.sin_port = htons(SERVERPORT);
	ret = inet_pton(AF_INET, serverIpAddress.c_str(), &toAddr.sin_addr.s_addr);
	if (ret < 0) {
		cout << "Set Server IP Error" << endl;
		return -1;
	}

	while (true) {
		char message[MESSAGELENGTH];	// サーバ側とサイズを合わせること
		std::cout << "Input message:";
		std::cin >> message;

		ret = sendto(sock, message, MESSAGELENGTH, 0, (SOCKADDR*)&toAddr, tolen);
		if (ret == SOCKET_ERROR) {
			/*
				エラー処理
			*/
		}

	}

	ret = closesocket(sock);
	if (ret == SOCKET_ERROR)
	{
		/*
			エラー処理
		*/
	}

	// WinSockの終了処理
	ret = WSACleanup();
	//if (ret == SOCKET_ERROR)
	if (ret != 0)
	{
		/*
			エラー処理
		*/
	}

	return 0;
}

int InitWinSock() {
	//WinSockを表す構造体
	WSADATA wsaData;
	// WinSockの初期化  WinSock2.2
	return(WSAStartup(MAKEWORD(2, 2), &wsaData));
}

//void SetServerIP(SOCKADDR_IN& sIP) {
//	// 接続先サーバのIPアドレスを入力させる
//	std::string serverIpAddress;
//	std::cout << "Input Server IPv4 address :";
//	std::cin >> serverIpAddress;
//
//	const int tolen = sizeof(sIP);
//	memset(&sIP, 0, sizeof(sIP));
//	sIP.sin_family = AF_INET;
//	sIP.sin_port = htons(SERVERPORT);
//	inet_pton(AF_INET, serverIpAddress.c_str(), &sIP.sin_addr.s_addr);
//}