#include <iostream>
#include "ChatClient.h"

///// 定数宣言 /////
const unsigned short SERVER_PORT = 8888;	//ポート番号
const unsigned int MESSAGE_LENGTH = 1024;	//送受信の最大文字数

using std::cin;
using std::cout;
using std::endl;

int main() {
	ChatClient* pClient = new ChatClient();

	//結果を格納する変数
	int result = 0;

	//WinSockの初期化
	result = pClient->InitWinSock();
	if (pClient->InitWinSock()) {
		cout << "Error : WSAStartUp" << endl;
		delete pClient;
		return -1;
	}
	cout << "Success : WinSock StartUp" << endl;

	//ソケット作成
	if (pClient->InitSocket()) {
		cout << "Error : Create Socket" << endl;
		delete pClient;
		return -1;
	}
	cout << "Success : Create Socket" << endl;

	//通信先を入力
	if (pClient->SetServerIP()) {
		cout << "Error : Set Server IP Address" << endl;
		delete pClient;
		return -1;
	}
	cout << "Success : Set Server IP Address" << endl;

	cout << "Now Connecting..." << endl;
	cout << "Connection opens now! Let's Communicate with Others!" << endl;
	//メインループ
	

	//ソケットの後処理
	if (pClient->ReleaseSocket()) {
		cout << "Error : closesocket" << endl;
		delete pClient;
		return -1;
	}

	//WinSockの後処理
	if (pClient->ReleaseWinSock()) {
		cout << "Error : WSACleanup" << endl;
		delete pClient;
		return -1;
	}

	delete pClient;
	return 0;
}