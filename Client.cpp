#include <iostream>
#include "ChatClient.h"

///// �萔�錾 /////
const unsigned short SERVER_PORT = 8888;	//�|�[�g�ԍ�
const unsigned int MESSAGE_LENGTH = 1024;	//����M�̍ő啶����

using std::cin;
using std::cout;
using std::endl;

int main() {
	ChatClient* pClient = new ChatClient();

	//���ʂ��i�[����ϐ�
	int result = 0;

	//WinSock�̏�����
	result = pClient->InitWinSock();
	if (pClient->InitWinSock()) {
		cout << "Error : WSAStartUp" << endl;
		delete pClient;
		return -1;
	}
	cout << "Success : WinSock StartUp" << endl;

	//�\�P�b�g�쐬
	if (pClient->InitSocket()) {
		cout << "Error : Create Socket" << endl;
		delete pClient;
		return -1;
	}
	cout << "Success : Create Socket" << endl;

	//�ʐM������
	if (pClient->SetServerIP()) {
		cout << "Error : Set Server IP Address" << endl;
		delete pClient;
		return -1;
	}
	cout << "Success : Set Server IP Address" << endl;

	cout << "Now Connecting..." << endl;
	cout << "Connection opens now! Let's Communicate with Others!" << endl;
	//���C�����[�v
	if (pClient->Loop()) {
		cout << "Error : Connection Failer" << endl;
	}
	else {
		cout << "Success : Connection is Closed" << endl;
	}

	//�\�P�b�g�̌㏈��
	if (pClient->ReleaseSocket()) {
		cout << "Error : closesocket" << endl;
		delete pClient;
		return -1;
	}

	//WinSock�̌㏈��
	if (pClient->ReleaseWinSock()) {
		cout << "Error : WSACleanup" << endl;
		delete pClient;
		return -1;
	}

	delete pClient;
	return 0;
}