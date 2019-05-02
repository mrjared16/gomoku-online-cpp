// Caro_Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Caro_Client.h"
#include "MyClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


int main()
{
	char ip[IP_LENGTH];
	int port = -1;
	
	MyClient my_client;

	do
	{
		int socket_data_mode = MyClient::inputServer();
		MyClient::getSocketData(socket_data_mode, ip, port);

		my_client.set(ip, port);
	} while (!my_client.connectToServer());

	return 0;
}
