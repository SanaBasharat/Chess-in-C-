#pragma once

class Player {
private:
	char * pieces;
	int playerNum;

	int kingX;
	int kingY;

public:
	Player();
	Player (int pN);
	Player (const Player & obj);
	void capture (char x);
	char getpieces(int n);
	void setpieces(int n, char a);
	void promotePawn(char c);
	~Player();

	void setkingX(int x);
	void setkingY(int x);
	int getkingX();
	int getkingY();

};
