// Caro_Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Caro_Server.h"
#include "Server.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// The one and only application object

using namespace std;

int main()
{
	int port = 9998;
	Server test_server(port);
	test_server.listenToClients();
	return 0;
}
