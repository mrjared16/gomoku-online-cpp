#pragma once
#define IP_LENGTH 16 // 15 + \0
#define LAN_MODE 0
#define ONLINE_MODE 1
#define CUSTOM_MODE 2

#include "resource.h"
#include <afxsock.h>


class MyClient
{
public:
	MyClient();
	void set(const char ip[], int port);
	virtual ~MyClient();

	bool connectToServer();

	static int inputServer();
	static void getSocketData(int mode, char ip[IP_LENGTH], int &port);
	
	static void sendInt(CSocket *socket, int signal);
	static void receiveInt(CSocket *socket, int &signal);

private:
	char ip[IP_LENGTH];
	int port;
	CSocket client;

	static void showInputMsg();
	static int getInputMsg();

};

