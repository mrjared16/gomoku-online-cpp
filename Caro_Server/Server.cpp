#include "pch.h"
#include "Server.h"
#include "GameServer.h"
//#include <thread>
#include <vector>
#include <conio.h>

#define ESC 27

using namespace std;

Server::Server(int port)
{
	CWinApp theApp;
	HMODULE hModule = ::GetModuleHandle(nullptr);

	if (hModule == nullptr)
	{
		// TODO: change error code to suit your needs
		wprintf(L"Fatal Error: GetModuleHandle failed\n");
		return;
	}
	// initialize MFC and print and error on failure
	if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
	{
		// TODO: code your application's behavior here.
		wprintf(L"Fatal Error: MFC initialization failed\n");
		return;
	}

	AfxSocketInit(NULL);

	server.Create(port);

	// tmp
	num_clients = 2;
}

Server::~Server()
{
	// close socket
	for (CSocket *p : clients_queue)
	{
		if (p != NULL)
		{
			p->Close();
			delete p;
		}
	}
	server.Close();
}

void Server::listenToClients()
{
	server.Listen();
	cout << "Cho client ket noi server...\n";
	cout << "Nhan ESC de ngung\n";

	// TODO: code your application's behavior here.

	// wait client connect to server

	bool exit = false;
	std::thread get_key_press(Server::getEscKeyPress, std::ref(exit));

	int i = 1;
	std::vector<std::thread> game_queue;
	while (!exit)
	{
		CSocket *client1, *client2;
		client2 = new CSocket;
		if (server.Accept(*client2))
		{
			cout << "Client " << (i) << " ket noi den server!\n";
		}

		if (!clients_queue.empty())
		{
			client1 = clients_queue.back();
			clients_queue.pop_back();

			GameServer game(client1, client2);
			cout << "Client " << (i - 1) << " & " << i << " vao tro choi...\n";
			game_queue.push_back(thread(game));
		}
		else
		{
			clients_queue.insert(clients_queue.begin(), client2);
		}
		i++;
	}

	int size = game_queue.size();
	if (size > 0)
	{
		cout << "Cho tat ca cac game ket thuc...";
	}
	for (auto &g: game_queue)
	{
		cout << "end\n";
		g.join();
	}
}

void Server::sendInt(CSocket * socket, int data)
{
	socket->Send(&data, sizeof(data), 0);
}

void Server::receiveInt(CSocket * socket, int & data)
{
	socket->Receive(&data, sizeof(data), 0);
}

void Server::getEscKeyPress(bool &key)
{
	while (!key)
	{
		key = (_getch() == ESC);
		this_thread::sleep_for(std::chrono::milliseconds(300));
	}
}
