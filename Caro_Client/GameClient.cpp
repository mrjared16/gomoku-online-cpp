#include "pch.h"
#include "GameClient.h"
#include "WindowsFunctions.h"

#include <iostream>
#include <conio.h>

using namespace std;

#define UP   119  // w
#define DOW  115  // s
#define LE   97   // a
#define RI   100  // d
#define OK   13   // enter

GameClient::GameClient(CSocket * player1)
{
	this->you = new PlayerClient();
	this->opponent = new PlayerClient();
	this->client = player1;
}

GameClient::~GameClient()
{
	if (you != NULL)
	{
		delete you;
	}

	if (opponent != NULL)
	{
		delete opponent;
	}

}

void GameClient::tiso() {
	int p1 = you->getScore();
	int p2 = opponent->getScore();
	for (int i = 0; i < p1; i++) {
		WindowsFunctions::goToXY(52 + 2, 6 + i);
		WindowsFunctions::WindowsFunctions::txtColor(12);
		cout << "o";
	}
	for (int i = 0; i < p2; i++) {
		WindowsFunctions::goToXY(52 + 13, 6 + i);
		WindowsFunctions::WindowsFunctions::txtColor(11);
		cout << "x";
	}
}

void huongdan() {
	WindowsFunctions::WindowsFunctions::txtColor(10);
	WindowsFunctions::goToXY(1, 0);
	WindowsFunctions::WindowsFunctions::txtColor(9);
	cout << "Esc - Thoat";
	WindowsFunctions::WindowsFunctions::txtColor(10);
	WindowsFunctions::goToXY(1, 3);
	cout << "a : " << char(283);
	WindowsFunctions::goToXY(1, 4);
	cout << "d : " << char(282);
	WindowsFunctions::goToXY(1, 5);
	cout << "w : " << char(280);
	WindowsFunctions::goToXY(1, 6);
	cout << "s : " << char(281);
	WindowsFunctions::goToXY(1, 8);
	WindowsFunctions::WindowsFunctions::txtColor(13);
	cout << "t : xin ";
	WindowsFunctions::goToXY(1, 9);
	WindowsFunctions::WindowsFunctions::txtColor(13);
	cout << "    thua";
	WindowsFunctions::goToXY(1, 10);
	WindowsFunctions::WindowsFunctions::txtColor(10);
	WindowsFunctions::WindowsFunctions::txtColor(13);
	cout << "h : cau ";
	WindowsFunctions::goToXY(1, 11);

	cout << "    hoa";

}

void khungtiso() {
	WindowsFunctions::goToXY(52, 3);
	WindowsFunctions::WindowsFunctions::txtColor(10);
	cout << char(220) << char(220) << char(220) << char(220) << char(220) << char(220) << char(220) << char(220);
	WindowsFunctions::WindowsFunctions::txtColor(13);
	cout << " Ti so ";
	WindowsFunctions::WindowsFunctions::txtColor(10);
	cout << char(220) << char(220) << char(220) << char(220) << char(220) << char(220) << char(220);
	WindowsFunctions::goToXY(54, 4);
	WindowsFunctions::WindowsFunctions::txtColor(14);
	cout << "Ban        Doi thu";

	for (int i = 0; i <= 21; i++) {
		WindowsFunctions::goToXY(52 + i, 4 + 18);
		WindowsFunctions::WindowsFunctions::txtColor(10);
		cout << char(223);
	}
	for (int i = 4; i <= 21; i++) {
		WindowsFunctions::goToXY(52, i);
		cout << char(219);
		WindowsFunctions::goToXY(52 + 16 + 5, i);
		cout << char(219);
		WindowsFunctions::goToXY(52 + 8 + 2, i);
		cout << char(219);
	}
}

void khung() {
	int d = 1;
	WindowsFunctions::WindowsFunctions::txtColor(6);
	for (int i = 0; i < 40; i++) {
		WindowsFunctions::goToXY(10 + i, 3);
		cout << char(220);
		WindowsFunctions::goToXY(10 + i, 20);
		cout << char(223);
	}
	for (int i = 4; i <= 19; i++) {
		WindowsFunctions::goToXY(10, i);
		cout << char(219);
		WindowsFunctions::goToXY(49, i);
		cout << char(219);
	}
	int k = 1;
	for (int i = 11; i <= 48; i++) {
		for (int j = 4; j <= 19; j++) {
			if (i % 2 == 0) {
				if (j % 2 == 0) {
					WindowsFunctions::goToXY(i, j);
					WindowsFunctions::WindowsFunctions::txtColor(0);
					cout << char(219);
				}
				else {
					WindowsFunctions::goToXY(i, j);
					WindowsFunctions::WindowsFunctions::txtColor(7);
					cout << char(219);
				}
			}
			else {
				if (j % 2 == 0) {
					WindowsFunctions::goToXY(i, j);
					WindowsFunctions::WindowsFunctions::txtColor(7);
					cout << char(219);
				}
				else {
					WindowsFunctions::goToXY(i, j);
					WindowsFunctions::WindowsFunctions::txtColor(0);
					cout << char(219);
				}
			}
		}
	}
	WindowsFunctions::WindowsFunctions::txtColor(14);
	WindowsFunctions::goToXY(10, 21);
	cout << "Developer : Nguyen Dinh Tuan . ";
	WindowsFunctions::goToXY(10, 22);
	cout << "Mail      : theiron1997@gmail.com";
	huongdan();
}

void GameClient::run()
{
	this->play();
}

void GameClient::play()
{
	int type, signal;
	//MyClient::receiveInt(client, type);

	//if (type != START_SIGNAL)
	//{
	//	return;
	//}

	int request;


	// tmp
	bool check = true;
	do
	{
		type = signal = NUL_VALUE;

		MyClient::receiveInt(client, type);
		MyClient::receiveInt(client, signal);

		if (type == NUL_VALUE || signal == NUL_VALUE)
		{
			check = false;
			system("cls");
			cout << "Xay ra loi!";
			continue;
		}

		if (type == START_SIGNAL)
		{
			//cout << "Game bat dau!\n";
			you->setID(signal);
			opponent->setID((signal + 1) % 2);
			// tmp
			this->init();
			SetConsoleTitleA("Game : Ca-ro . Developer : Nguyen Dinh Tuan");
			system("cls");
			khung();
			khungtiso();
			tiso();
			WindowsFunctions::goToXY(x, y);
			request = NUL_VALUE;
			continue;
		}


		switch (type)
		{
		case TURN_SIGNAL:
			int mess[2];
			switch (signal)
			{
			case IN_TURN_SIGNAL:
				WindowsFunctions::goToXY(10, 1);
				WindowsFunctions::WindowsFunctions::txtColor(11);
				cout << "Den luot ban danh! - ";
				WindowsFunctions::txtColor(12);
				cout << "o";
				WindowsFunctions::goToXY(x, y);
				char ch;
				while (true)
				{
					ch = _getch();
					if (ch == UP)
					{
						if (y <= 4)
						{
							y = 19;
							WindowsFunctions::goToXY(x, y);
						}
						else
						{
							y--;
							WindowsFunctions::goToXY(x, y);
						}
					}

					if (ch == DOW)
					{
						if (y >= 19)
						{
							y = 4;
							WindowsFunctions::goToXY(x, y);
						}
						else
						{
							y++;
							WindowsFunctions::goToXY(x, y);
						}
					}
					if (ch == RI)
					{
						if (x >= 48)
						{
							x = 11;
							WindowsFunctions::goToXY(x, y);
						}
						else
						{
							x++;
							WindowsFunctions::goToXY(x, y);
						}
					}
					if (ch == LE)
					{
						if (x <= 11)
						{
							x = 48;
							WindowsFunctions::goToXY(x, y);
						}
						else
						{
							x--;
							WindowsFunctions::goToXY(x, y);
						}
					}
					if (ch == OK)
					{
						// Neu ma da co gia tri
						if (this->playground[x][y] != NUL_VALUE)
						{
							WindowsFunctions::goToXY(10, 1);
							WindowsFunctions::WindowsFunctions::txtColor(10);
							cout << "O nay khong trong. Ban hay chon o khac ...";
							_getch();
							WindowsFunctions::goToXY(10, 1);
							cout << "                                            ";
							WindowsFunctions::goToXY(x, y);
						}
						else {
							// luc nay da chon o khong co gia tri
							this->playground[x][y] = you->getID();
							WindowsFunctions::goToXY(x, y);
							WindowsFunctions::WindowsFunctions::txtColor(12);
							cout << "o";
							break;
						}
					}
				}

				mess[0] = x;
				mess[1] = y;
				MyClient::sendInt(client, TURN_SIGNAL);
				MyClient::sendInt(client, DATA_SIGNAL);
				client->Send(&mess, sizeof(mess), 0);
				break;
			case NOT_IN_TURN_SIGNAL:
				WindowsFunctions::goToXY(10, 1);
				WindowsFunctions::WindowsFunctions::txtColor(11);
				cout << "Den luot doi thu! -  ";
				WindowsFunctions::WindowsFunctions::txtColor(10);
				cout << "x";
				WindowsFunctions::goToXY(x, y);
				break;
			// cau hoa
			// xin thua
			// nhan tin hieu
			case DATA_SIGNAL:
				client->Receive(&mess, sizeof(mess), 0);
				this->playground[mess[0]][mess[1]] = opponent->getID();
				WindowsFunctions::goToXY(mess[0], mess[1]);
				WindowsFunctions::WindowsFunctions::txtColor(10);
				cout << "x";
				//cout << "Doi thu da danh (" << mess[0] << "; " << mess[1] << ") ... \n";
				break;
			}
			break;
		case RESULT_SIGNAL:
			// tmp
			tiso();
			WindowsFunctions::goToXY(10, 1);
			cout << "                                                              ";
			WindowsFunctions::goToXY(10, 1);
			// tmp
			switch (signal)
			{
			case WIN_SIGNAL:
				cout << "Chuc mung! Ban da gianh chien thang!\n";
				break;
			case LOSE_SIGNAL:
				cout << "Sorry! Ban da thua cuoc!\n";
				break;
			}
			WindowsFunctions::goToXY(10, 2);
			cout << "Ban co muon choi lai? (Co: " << ACCEPT_SIGNAL << ", Khong: " << DECLINE_SIGNAL << "): ";
			//cout << "So diem cua ban la: " << score << "\n";
			cin >> request;

			WindowsFunctions::goToXY(10, 2);
			cout << "Dang gui cau tra loi cua ban...                         \n";
			MyClient::sendInt(client, REQUEST_SIGNAL);
			MyClient::sendInt(client, request);
			break;
		case CMD_SIGNAL:
			switch (signal)
			{
			case SENT_SIGNAL:
				WindowsFunctions::goToXY(10, 1);
				cout << "                                                              ";
				WindowsFunctions::goToXY(10, 1);
				if (request == ACCEPT_SIGNAL)
				{
					cout << "Da gui loi moi choi lai! Doi loi tra loi cua doi thu...\n";
				}
				else
				{
					cout << "Da gui loi tu choi!\n";
					check = false;
					_getch();
				}
				break;
			case PLAY_SIGNAL:
				WindowsFunctions::goToXY(10, 2);
				cout << "                                                              ";
				WindowsFunctions::goToXY(10, 2);
				cout << "Ca 2 deu chap nhan choi lai! Nhan phim bat ky de bat dau game moi!\n";
				_getch();
				break;
			case DONT_PLAY_SIGNAL:
				check = false;
				if (request == ACCEPT_SIGNAL)
				{
					WindowsFunctions::goToXY(10, 2);
					cout << "                                                              ";
					WindowsFunctions::goToXY(10, 2);
					cout << "Rat tiec, doi thu khong dong y choi lai!\n";
					_getch();
				}
				break;
			}
			break;
		case YOUR_SCORE_SIGNAL:
			you->setScore(signal);
			break;
		case OPPONENT_SCORE_SIGNAL:
			opponent->setScore(signal);
			break;
		}
	} while (check);
	system("cls");
	cout << "Game ket thuc!\n";
}


void GameClient::init()
{
	memset(this->playground, NUL_VALUE, sizeof(this->playground));
	x = 12;
	y = 6;
}

