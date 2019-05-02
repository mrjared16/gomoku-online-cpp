#pragma once
struct Data
{
public:
	Data(int x, int y, int value)
	{
		this->x = x;
		this->y = y;
		this->value = value;
	}
	Data()
	{
	}
	
	int x, y;
	int value;
};