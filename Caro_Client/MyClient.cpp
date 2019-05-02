#include "pch.h"
#include "MyClient.h"
#include "GameClient.h"
#include <iostream>

using namespace std;

MyClient::MyClient()
{

	CWinApp theApp;

	HMODULE hModule = ::GetModuleHandle(nullptr);

	if (hModule == nullptr)
	{
		// TODO: change error code to suit your needs
		wprintf(L"Fatal Error: GetModuleHandle failed\n");
		exit(1);
	}
	// initialize MFC and print and error on failure
	if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
	{
		// TODO: code your application's behavior here.
		wprintf(L"Fatal Error: MFC initialization failed\n");
		exit(2);
	}
	AfxSocketInit(NULL);

}

MyClient::~MyClient()
{
	client.Close();
}

void MyClient::set(const char ip[], int port)
{
	// get ip
	for (int i = 0; i < IP_LENGTH; i++)
	{
		this->ip[i] = ip[i];
	}

	// Get port
	this->port = port;

	client.Create();
}

bool MyClient::connectToServer()
{
	cout << "Dang ket noi...\n";

	if (!client.Connect(CA2W(this->ip), this->port))
	{
		cout << "Ket noi that bai!\n";
		cout << "Moi ban kiem tra lai mang hoac chon server khac.\n\n";
		return false;
	}

	cout << "Ket noi den server thanh cong! Cho doi thu...\n";
	GameClient new_game(&this->client);
	new_game.run();
	return true;
	// Play
}


int MyClient::inputServer()
{
	MyClient::showInputMsg();
	return MyClient::getInputMsg();
}

void MyClient::getSocketData(int mode, char ip[IP_LENGTH], int &port)
{
	const char loop_ip[IP_LENGTH] = "127.0.0.1";
	const char private_server_ip[IP_LENGTH] = "13.250.11.150"; // www.caroserver.tk
	int default_port = 9998;

	switch (mode)
	{
	case 0:
		strcpy_s(ip, IP_LENGTH, loop_ip);
		port = default_port;
		return;
	case 1:
		strcpy_s(ip, IP_LENGTH, private_server_ip);
		port = default_port;
		return;
	case 2:
		cout << "Server ip: ";
		cin >> ip;

		cout << "port: ";
		cin >> port;

		return;
	}
}


void MyClient::sendInt(CSocket *socket, int signal)
{
	socket->Send(&signal, sizeof(signal), 0);
}

void MyClient::receiveInt(CSocket *socket, int &signal)
{
	socket->Receive(&signal, sizeof(signal), 0);
}



void MyClient::showInputMsg()
{
	cout << "Nhap vao server(";
	cout << LAN_MODE << ": LAN, ";
	cout << ONLINE_MODE << "1: Online, ";
	cout << CUSTOM_MODE << ": Custom";
	cout << "): ";
}

int MyClient::getInputMsg()
{
	int type;
	do
	{
		cin >> type;
		switch (type)
		{
		case LAN_MODE:
		case ONLINE_MODE:
		case CUSTOM_MODE:
			return type;
		}
		cout << "Nhap vao loi! Moi ban nhap lai: ";
	} while (true);
	return -1;
}
