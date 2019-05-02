#include "pch.h"
#include "GameServer.h"
#include "PlayerServer.h"


using namespace std;

void GameServer::run()
{
	this->init();

	this->play();
}

void GameServer::operator()()
{
	this->run();
}

GameServer::GameServer(CSocket *player1, CSocket *player2)
{
	player[0] = new PlayerServer(player1, PLAYER_1_ID);	// PlayerServer 1 danh truoc
	player[1] = new PlayerServer(player2, PLAYER_2_ID);
}

void GameServer::init()
{
	// set playground
	memset(playground, NUL_VALUE, sizeof(playground));
}

void GameServer::play()
{
	for (int i = 0; i < 2; i++)
	{
		player[i]->sendSignal(START_SIGNAL);
		player[i]->sendSignal(i);	// ID
		//player[i]->sendSignal((i + 1) % 2);	// ID opponent
	}

	PlayerServer *winner = NULL,
		*loser = NULL;
	do
	{
		PlayerServer *in_turn = this->getInTurnPlayer();
		PlayerServer *not_in_turn = this->getNotInTurnPlayer();

		in_turn->sendSignal(TURN_SIGNAL, IN_TURN_SIGNAL);
		not_in_turn->sendSignal(TURN_SIGNAL, NOT_IN_TURN_SIGNAL);

		int type, signal;
		in_turn->receiveSignal(type);
		in_turn->receiveSignal(signal);

		if (!this->isReceivePlacedData(type, signal)) {
			// cau hoa hoac xin thua
			break;
		}

		Data data;
		in_turn->receiveData(data);
		this->setPlace(data); // valid 
		// if valid
		not_in_turn->sendSignal(TURN_SIGNAL);
		not_in_turn->sendSignal(DATA_SIGNAL);
		not_in_turn->sendData(data);

		if (this->isWin())
		{
			// winner is always player in turn
			winner = in_turn;
			loser = not_in_turn;
			break;
		}
		// Chua win: tiep tuc, doi luot
		this->alternateTurn();

	} while (true);

	this->sendResult(winner, loser);
}

void GameServer::sendResult(PlayerServer *winner, PlayerServer *loser)
{
	winner->increaseScore();
	winner->sendSignal(YOUR_SCORE_SIGNAL, winner->getScore());
	winner->sendSignal(OPPONENT_SCORE_SIGNAL, loser->getScore());
	//winner->sendScore();
	winner->sendSignal(RESULT_SIGNAL, WIN_SIGNAL);

	//valid not null
	// NECESSARY?
	//loser->sendScore();
	loser->sendSignal(YOUR_SCORE_SIGNAL, loser->getScore());
	loser->sendSignal(OPPONENT_SCORE_SIGNAL, winner->getScore());
	loser->sendSignal(RESULT_SIGNAL, LOSE_SIGNAL);


	// receive play again request
	if (this->isReceiveBothPlayAgainRequest(winner, loser))
	{
		// Play again
		winner->sendSignal(CMD_SIGNAL, PLAY_SIGNAL);
		loser->sendSignal(CMD_SIGNAL, PLAY_SIGNAL);
		cout << "Dang bat dau lai...\n";
		this->run();
	}
	else {
		winner->sendSignal(CMD_SIGNAL, DONT_PLAY_SIGNAL);
		loser->sendSignal(CMD_SIGNAL, DONT_PLAY_SIGNAL);
		cout << "Khong choi lai!\n";
	}
}

bool GameServer::isWin()
{
	//	//return (check == WIN || check == LOSE);
	bool win = true;
	for (int i = 1; i <= 50; i++) {
		for (int j = 1; j <= 50; j++) {

			if ((this->playground[i][j] == this->playground[i + 1][j]) && (this->playground[i][j] == this->playground[i + 2][j]) && (this->playground[i][j] == this->playground[i + 3][j])/*&&(this->playground[i+4][j]==this->playground[i][j])*/ && (this->playground[i][j] != NUL_VALUE)) {
				win = true;
				for (int h = 0; h <= 50; h++) {
					if (i - h <= 1) {
						break;
					}
					else {
						if ((this->playground[i - h][j] != this->playground[i][j]) && (this->playground[i - h][j] != NUL_VALUE)) {
							win = false;;
							break;
						}
					}
				}
				for (int h = 0; h <= 50; h++) {
					if (i + h >= 50) {
						break;
					}
					else {
						if ((this->playground[i + h + 3][j] != this->playground[i][j]) && (this->playground[i + h + 3][j] != NUL_VALUE)) {
							win = false;;
							break;
						}
					}
				}
				if (win) {
					/*for (int k = 0; k < 4; k++) {
						mang[k].y = j;
						mang[k].x = i + k;
					}
					return this->playground[i][j];*/
					return true;
				}
			}
			if ((this->playground[i][j] == this->playground[i][j + 1]) && (this->playground[i][j] == this->playground[i][j + 2]) && (this->playground[i][j] == this->playground[i][j + 3])/*&&(this->playground[i][j]==this->playground[i][j+4])*/ && (this->playground[i][j] != NUL_VALUE)) {
				win = true;
				for (int h = 0; h <= 50; h++) {
					if (j + h >= 50) {
						break;
					}
					else {
						if ((this->playground[i][j + 3 + h] != NUL_VALUE) && (this->playground[i][j + 3 + h] != this->playground[i][j])) win = false;;
					}
				}
				for (int h = 0; h <= 50; h++) {
					if (j - h <= 1) {
						break;
					}
					else {
						if ((this->playground[i][j - h] != NUL_VALUE) && (this->playground[i][j - h] != this->playground[i][j])) win = false;;
					}
				}
				if (win) {
					/*for (int k = 0; k < 4; k++) {
						mang[k].x = i;
						mang[k].y = j + k;
					}
					return this->playground[i][j];*/
					return true;
				}
			}
			if ((this->playground[i][j] == this->playground[i + 1][j + 1]) && (this->playground[i][j] == this->playground[i + 2][j + 2]) && (this->playground[i][j] == this->playground[i + 3][j + 3])/*&&(this->playground[i][j]==this->playground[i+4][j+4])*/ && (this->playground[i][j] != NUL_VALUE)) {
				win = true;
				for (int h = 0; h <= 50; h++) {
					if ((i + h >= 50) || (j + h) >= 30) break;
					else {
						if ((this->playground[i + h + 3][j + h + 3] != this->playground[i][j]) && (this->playground[i + h + 3][j + h + 3] != NUL_VALUE)) win = false;;
					}
				}
				for (int h = 0; h <= 50; h++) {
					if ((i - h <= 1) || (j - h) <= 1) break;
					else {
						if ((this->playground[i - h][j - h] != this->playground[i][j]) && (this->playground[i - h][j - h] != NUL_VALUE)) win = false;;
					}
				}
				if (win) {
					/*for (int k = 0; k < 4; k++) {
						mang[k].x = i + k;
						mang[k].y = j + k;
					}
					return this->playground[i][j];*/
					return true;
				}
			}
			if ((this->playground[i][j] == this->playground[i - 1][j + 1]) && (this->playground[i][j] == this->playground[i - 2][j + 2]) && (this->playground[i][j] == this->playground[i - 3][j + 3])/*&&(this->playground[i][j]==this->playground[i-4][j-4])*/ && (this->playground[i][j] != NUL_VALUE)) {
				win = true;
				for (int h = 1; h <= 50; h++) {
					if ((i + h >= 50) || (j - h) <= 1) break;
					else {
						if ((this->playground[i + h][j - h] != this->playground[i][j]) && (this->playground[i + h][j - h] != NUL_VALUE)) win = false;;
					}
				}
				for (int h = 0; h <= 50; h++) {
					if ((i - h <= 1) || (j + h) >= 50) break;
					else {
						if ((this->playground[i - 4 - h][j + h + 4] != this->playground[i][j]) && (this->playground[i - h - 4][j + h + 4] != NUL_VALUE)) win = false;;
					}
				}
				if (win) {
					/*for (int k = 0; k < 4; k++) {
						mang[k].x = i - k;
						mang[k].y = j + k;
					}
					return this->playground[i][j];*/
					return true;
				}
			};
		}
	}

	return false;
}

bool GameServer::isReceiveBothPlayAgainRequest(PlayerServer * p1, PlayerServer * p2)
{
	int type[2], signal[2];
	p1->receiveSignal(type[0], signal[0]);
	p1->sendSignal(CMD_SIGNAL, SENT_SIGNAL);

	p2->receiveSignal(type[1], signal[1]);
	p2->sendSignal(CMD_SIGNAL, SENT_SIGNAL);

	return (type[0] == type[1] && type[0] == REQUEST_SIGNAL &&
		signal[0] == signal[1] && signal[0] == ACCEPT_SIGNAL);
}



void GameServer::setPlace(Data data)
{
	//valid

	this->playground[data.x][data.y] = data.value;
}


PlayerServer * GameServer::getInTurnPlayer()
{
	return player[0];
}

PlayerServer * GameServer::getNotInTurnPlayer()
{
	return player[1];
}

void GameServer::alternateTurn()
{
	PlayerServer *tmp = player[0];
	player[0] = player[1];
	player[1] = tmp;
}

bool GameServer::isReceivePlacedData(int type, int signal)
{
	return (signal == DATA_SIGNAL && type == TURN_SIGNAL); 
}

GameServer::~GameServer()
{
	for (int i = 0; i < 2; i++)
	{
		if (player[i] != NULL)
			delete player[i];
	}
}
