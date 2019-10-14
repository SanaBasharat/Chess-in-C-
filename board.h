#pragma once
#include "tile.h"
#include "player.h"
#include <Windows.h>
extern HANDLE out;


class Board {
    private:
        tile ** board;
		Player * p1;
		Player * p2;
		int turn;
    public:
		Board ();
        Board (const Board & x);
        ~Board();
		void setBoard ();
		bool playGame();
		bool MakeMove();
		bool checkMove (int &x1, int &x2, int &y1, int &y2);
		bool moveRook(int x1, int y1, int x2, int y2, bool usingforcheck);
		bool moveKnight(int x1, int y1, int x2, int y2, bool usingforcheck);
		bool moveBishop(int x1, int y1, int x2, int y2, bool usingforcheck);
		bool moveQueen(int x1, int y1, int x2, int y2, bool usingforcheck);
		bool moveKing(int x1, int y1, int x2, int y2, bool usingforcheck);
		bool movePawns(int x1, int y1, int x2, int y2, bool usingforcheck);

        void printBoard ();
		void SaveGame();
		void LoadGame();
		void NewGame();

		bool check(int x, int y);
		bool checkmate(int x, int y);
};