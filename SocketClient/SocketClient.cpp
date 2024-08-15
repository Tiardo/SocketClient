
#define	WIN32_LEAN_AND_MEAN

#include <iostream>
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;


int main()
{
	WSADATA wsaData;
	ADDRINFO hints;
	ADDRINFO* addrResult = NULL;
	SOCKET ConnectSocket = INVALID_SOCKET;


	const char* sendBuffer = "Piska";
	char recvBuffer[512];


	int result;
	result = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (result != 0)
	{
		cout << "Warning Nax , result = " << result << endl;
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	result = getaddrinfo("localhost", "8803", &hints, &addrResult);
	if (result != 0) {

		cout << "Problemka s soketom ili locallhostom" << result << endl;
		WSACleanup();
		return 1;
	}


	ConnectSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
	if (ConnectSocket == NULL) {

		cout << "ConnectSocket NICHT ichWIll" << endl;
		freeaddrinfo(addrResult);
		WSACleanup();
		return 1;
	}


	result = connect(ConnectSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
	if (result == SOCKET_ERROR)
	{
		cout << "Beda s connectom" << endl;
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
		freeaddrinfo(addrResult);
		WSACleanup();
		return 1;
	}


	result = send(ConnectSocket, sendBuffer, (int)strlen(sendBuffer), 0);
	if (result == SOCKET_ERROR) {

		cout << "Nea" << result << endl;
		closesocket(ConnectSocket);
		freeaddrinfo(addrResult);
		WSACleanup();
		return 1;
	}


	cout << "PAM PAM PAAAM" << result << endl;


	result = shutdown(ConnectSocket, SD_SEND);
	if (result == SOCKET_ERROR) {

		cout << "NeaNeaa" << result << endl;
		closesocket(ConnectSocket);
		freeaddrinfo(addrResult);
		WSACleanup();
		return 1;

	}

	ZeroMemory(recvBuffer, 512);
	do {


		result = recv(ConnectSocket, recvBuffer, 512, 0);
		if (result > 0)
		{



		}


	} while ();



}
