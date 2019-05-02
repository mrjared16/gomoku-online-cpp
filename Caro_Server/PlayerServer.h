#pragma once
#include "Server.h"
#include "Data.h"
//class Game;


class PlayerServer
{
public:
	PlayerServer(CSocket *socket, int player_id);
	PlayerServer();
	virtual ~PlayerServer();

	void sendData(Data d);
	void receiveData(Data &d);

	void sendSignal(int type, int signal);
	void sendSignal(int type);

	void receiveSignal(int &type, int &signal);
	void receiveSignal(int &type);

	void increaseScore();
	int getScore();
	//void sendScore();
private:
	CSocket *socket;
	//Game *g;
	int player_id;
	int score;
};

