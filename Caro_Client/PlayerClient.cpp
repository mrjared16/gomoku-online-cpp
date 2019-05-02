#include "pch.h"
#include "PlayerClient.h"


PlayerClient::PlayerClient()
{
	id = -1;
	score = 0;
}

int PlayerClient::getID()
{
	return this->id;
}

int PlayerClient::getScore()
{
	return this->score;
	return 0;
}

void PlayerClient::setScore(int x)
{
	this->score = x;
}

void PlayerClient::setID(int id)
{
	this->id = id;
}


PlayerClient::~PlayerClient()
{
}
