#pragma once

class PlayerClient
{
public:
	PlayerClient();
	~PlayerClient();
	int getID();
	int getScore();
	
	void setScore(int x);
	void setID(int x);
private:
	int id;
	int score;
};

