#pragma once

#include "MyClient.h"
#include "PlayerClient.h"

//#include "Data.h"


// server
#define START_SIGNAL 0
#define TURN_SIGNAL 1
#define RESULT_SIGNAL 2
#define CMD_SIGNAL 3
#define YOUR_SCORE_SIGNAL 4
#define OPPONENT_SCORE_SIGNAL 5

// client & server

// client
#define REQUEST_SIGNAL 7

// turn signal (server)
#define IN_TURN_SIGNAL 0
#define NOT_IN_TURN_SIGNAL 1
#define DATA_SIGNAL 2

// result signal (server)
#define WIN_SIGNAL 0
#define LOSE_SIGNAL 1

// cmd signal (server)
#define PLAY_SIGNAL 0
#define DONT_PLAY_SIGNAL 1
#define SENT_SIGNAL 2

// request signal (client)
#define ACCEPT_SIGNAL 0
#define DECLINE_SIGNAL 1

#define NUL_VALUE -1
#define PLAYER_1_ID 0
#define PLAYER_2_ID 1

#define SIZE 100
class GameClient
{
public:
	GameClient(CSocket *player1);
	virtual ~GameClient();

	void run();
	void tiso();
private:
	void play();
	void init();

	PlayerClient *you, *opponent;
	CSocket *client;
	int x, y;
	int playground[SIZE][SIZE];
};

