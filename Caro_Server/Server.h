#pragma once

#include "resource.h"
#include <iostream>
#include <string>
#include <vector>
#include <afxsock.h>
#include <thread>

class Server
{
public:
	Server(int port);
	virtual ~Server();

	void listenToClients();

	static void sendInt(CSocket *socket, int data);
	static void receiveInt(CSocket *socket, int &data);

	static void getEscKeyPress(bool &key);
private:
	int num_clients;
	int port;
	CSocket server;

	std::vector<CSocket *> clients_queue;
//	std::vector<thread *> game_queue;
};

