#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment( lib, "ws2_32.lib" )

///// �萔�錾 /////
const unsigned short SERVER_PORT = 8888;	//�|�[�g�ԍ�
const unsigned int MESSAGE_LENGTH = 1024;	//����M�̍ő啶����

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() {
	//���ʊi�[�p�ϐ�
	int result = 0;

	//WinSock�{��
	WSADATA wsaData;

	//������
	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		cout << "Error : WSAStartUp" << endl;
		return -1;
	}

	//�\�P�b�g�f�B�X�N���v�^
	SOCKET sock;

	//UDP�\�P�b�g�쐬
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET) {
		cout << "Error : Socket" << endl;
		return -1;
	}


	//�ʐM������
	string serverIP = "";
	cout << "Input Server IPv4 Address : ";
	cin >> serverIP;

	//�ʐM����̊i�[
	SOCKADDR_IN toAddr;
	const int tolen = sizeof(toAddr);
	memset(&toAddr, 0, sizeof(toAddr));
	toAddr.sin_family = AF_INET;
	toAddr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, serverIP.c_str(), &toAddr.sin_addr.s_addr);

	//���C�����[�v
	while (true) {
		string message;
		message.resize(MESSAGE_LENGTH);//����l���T�[�o�ƍ��킹��
		std::cout << "Input Message : ";
		std::getline(cin, message);

		result = sendto(sock, message.c_str(), MESSAGE_LENGTH, 0, (SOCKADDR*)&toAddr, tolen);
		if (result == SOCKET_ERROR) {
			cout << "Error : sendto" << endl;
			return -1;
		}
	}

	//�\�P�b�g�̌㏈��
	result = closesocket(sock);
	if (result == SOCKET_ERROR) {
		cout << "Error : closesocket" << endl;
		return -1;
	}

	//WinSock�̌㏈��
	result = WSACleanup();
	if (result != 0) {
		cout << "Error : WSACleanup" << endl;
		return -1;
	}

	return 0;
}