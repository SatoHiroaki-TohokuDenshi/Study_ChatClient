/*
WSAStartup()	// WinSock������
socket()		// �\�P�b�g�쐬
�T�[�o�̃\�P�b�g�A�h���X�����Z�b�g
while(true)
{
	���M���b�Z�[�W����
	sendto();	// ���M
	recvfrom();	// ��M
	�o��
}
closesocket()		// �\�P�b�g�j��
WSACleanup()		// WinSock�I������
*/

#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment( lib, "ws2_32.lib" )

using std::cout;
using std::endl;

// �|�[�g�ԍ�
const unsigned short SERVERPORT = 8888;

// ����M���郁�b�Z�[�W�̍ő�l
const unsigned int MESSAGELENGTH = 1024;

// �v���g�^�C�v�錾
int InitWinSock();
//void SetServerIP(SOCKADDR_IN& sIP);

int main() {
	cout << "You are Chat Client" << endl;

	//�������̌��ʂ��i�[����ϐ�
	int ret;

	// WinSock�̏�����
	ret = InitWinSock();
	if (ret != 0) {
		cout << "WinSock Initializing Error";
		return -1;
	}
	cout << "Initialize WinSock is Success";

	// �\�P�b�g�f�B�X�N���v�^
	SOCKET sock;

	// UDP�\�P�b�g�쐬
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock < 0) {
		cout << "Socket Creation Error" << endl;
		return -1;
	}
	cout << "Create Socket is Success";

	// �ڑ���T�[�o��IP�A�h���X����͂�����
	std::string serverIpAddress;
	std::cout << "Input Server IPv4 address :";
	std::cin >> serverIpAddress;

	// �ڑ���T�[�o�̃\�P�b�g�A�h���X���i�[
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
		char message[MESSAGELENGTH];	// �T�[�o���ƃT�C�Y�����킹�邱��
		std::cout << "Input message:";
		std::cin >> message;

		ret = sendto(sock, message, MESSAGELENGTH, 0, (SOCKADDR*)&toAddr, tolen);
		if (ret == SOCKET_ERROR) {
			/*
				�G���[����
			*/
		}

	}

	ret = closesocket(sock);
	if (ret == SOCKET_ERROR)
	{
		/*
			�G���[����
		*/
	}

	// WinSock�̏I������
	ret = WSACleanup();
	//if (ret == SOCKET_ERROR)
	if (ret != 0)
	{
		/*
			�G���[����
		*/
	}

	return 0;
}

int InitWinSock() {
	//WinSock��\���\����
	WSADATA wsaData;
	// WinSock�̏�����  WinSock2.2
	return(WSAStartup(MAKEWORD(2, 2), &wsaData));
}

//void SetServerIP(SOCKADDR_IN& sIP) {
//	// �ڑ���T�[�o��IP�A�h���X����͂�����
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