#include "pch.h"
#include "PlayerServer.h"
#include "GameServer.h"

PlayerServer::PlayerServer(CSocket * socket, int player_id)
{
	this->socket = socket;
	this->player_id = player_id;
	//this->g = g;
}

PlayerServer::PlayerServer()
{
	socket = NULL;
	player_id = -1;
	score = 0;
}


PlayerServer::~PlayerServer()
{
}

void PlayerServer::sendData(Data d)
{
	int data[2] = { d.x, d.y };
	this->socket->Send(data, sizeof(data), 0);
}

void PlayerServer::receiveData(Data &d)
{
	// receive data from in turn player
	int buffer[2];
	this->socket->Receive(buffer, sizeof(buffer), 0);

	d.x = buffer[0];
	d.y = buffer[1];
	d.value = this->player_id;
}

void PlayerServer::sendSignal(int type, int signal)
{
	/*if (!GameServer::isValidSignal(type, signal))
		return;*/
	Server::sendInt(this->socket, type);
	Server::sendInt(this->socket, signal);
}

void PlayerServer::sendSignal(int type)
{
	Server::sendInt(this->socket, type);
}

void PlayerServer::receiveSignal(int & type, int & signal)
{
	Server::receiveInt(this->socket, type);
	Server::receiveInt(this->socket, signal);

}void PlayerServer::receiveSignal(int & type)
{
	Server::receiveInt(this->socket, type);
}

void PlayerServer::increaseScore()
{
	score++;
}

int PlayerServer::getScore()
{
	return this->score;
}

//void PlayerServer::sendScore()
//{
//	this->sendSignal(SCORE_SIGNAL, this->score);
//}
