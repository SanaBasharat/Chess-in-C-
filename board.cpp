#include "board.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <Windows.h>
HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
using namespace std;
 int n=8;
 Board::Board (){
	 turn = 1;
	 p1=new Player (1);
	 p2=new Player (2);
            char * w = "white";
            char * b = "black";
            board = new tile * [8];
            for (int i=0; i<8; i++){
                board[i]= new tile [8];
        }
        
        for (int i=0; i<8; i++){
			for ( int j=0; j<8; j++){
				if (i%2==1){
					if (j%2==1){
						board[i][j].setColor(w);
					}
					else{
						board[i][j].setColor(b);
					}
				 }
				else {
                    if (j%2==1){
                        board[i][j].setColor(b);
                    }
                    else
						board[i][j].setColor(w);
                }
			}
        }
	}

        Board::~Board (){
            for (int i=0; i<8; i++){
                delete [] board[i];
            }

            delete board;
			delete p1;
			delete p2;
}
        
		Board::Board (const Board & x){
            for (int i=0; i<8; i++){
                for (int j=0; j<8; j++){
                    board[i][j]=x.board[i][j];

                }
            }
			p1=x.p1;
			p2=x.p2;
			turn=x.turn;
        }

		void Board:: setBoard (){
			board[0][0].setPiece('r');
			board[0][1].setPiece('n');
			board[0][2].setPiece('b');
			board[0][3].setPiece('q');
			board[0][4].setPiece('k');
			board[0][5].setPiece('b');
			board[0][6].setPiece('n');
			board[0][7].setPiece('r');

			for (int i=0; i<8; i++){
				board[1][i].setPiece('p');
			}

			board[7][0].setPiece('R');
			board[7][1].setPiece('N');
			board[7][2].setPiece('B');
			board[7][3].setPiece('Q');
			board[7][4].setPiece('K');
			board[7][5].setPiece('B');
			board[7][6].setPiece('N');
			board[7][7].setPiece('R');

			for (int i=0; i<8; i++){
				board[6][i].setPiece('P');
			}

			for (int i=2; i<6; i++){
				for (int j=0; j<8; j++){
					board[i][j].setPiece('E');
				}
			}
			p1->setkingX(7);
			p1->setkingY(4);
			p2->setkingX(0);
			p2->setkingY(4);
		}
        
        void Board::printBoard (){
	int temp = n;
	SetConsoleTextAttribute(out, 7);
	cout << "         .:: CHESS ::." << endl;
	cout << "Enter -1 0 to Save your game"<<endl<<"-2 0 to Load a previous game" << endl<<"-3 0 to start a new game"<<endl<<"and -4 0 to quit the game"<<endl;
	cout << "   --------------------------" << endl;
	for (int i = 0; i<8; i++) {
		cout << temp-- << " | ";
		for (int j = 0; j<8; j++) {
			if (board[i][j].getPiece() == 'E') {
				if (strcmp("white", board[i][j].getColor()) == 0) {
					SetConsoleTextAttribute(out, 117);			//117 - Purple		116 - Red		115 - Aqua
					cout << "   ";								//125 - Light Purple	124 - Light Red		123 - Light Aqua
				}
				else {
					SetConsoleTextAttribute(out, 5);			//5 - Purple		4 - Red			3 - Aqua
					cout << "   ";								//13 - Light Purple		12 - Light Red		11 - Light Aqua
				}
			}
			else {
				if (strcmp("white", board[i][j].getColor()) == 0) {
					SetConsoleTextAttribute(out, 117);
					cout<<" ";
					cout << board[i][j].getPiece();
					cout<<" ";
				}
				else {
					SetConsoleTextAttribute(out, 5);
					cout<<" ";
					cout << board[i][j].getPiece();
					cout<<" ";
				}
			}
		}
		SetConsoleTextAttribute(out, 7);
		cout << " |" << endl;
	}
	SetConsoleTextAttribute(out, 7);
	cout << "   --------------------------" << endl;
	cout << "    " << " a  b  c  d  e  f  g  h " << endl;
}

		bool Board:: playGame() {
			bool val;
			system ("cls");
			printBoard ();
			val = MakeMove();
			if (turn==1) turn=2;
			else if (turn==2) turn =1;
			return val;
		}
		
		bool Board:: MakeMove (){
			int x1;
			int y1;
			int x2;
			int y2;
			bool retval = true;
			bool stop = false;
			bool IsInCheck = false;
			bool IsInCheckmate = false;
			char dest;
			while (!stop) {
				stop = true;
				while (checkMove(x1, x2, y1, y2) != true);

				if (x1 == -1) {
					SaveGame();			//save the game
					cout << "Saving your progress..." << endl;
					if (turn == 1) turn = 2;			//toggle the turn so that when it is toggled again in MakeMove
					else if (turn == 2) turn = 1;		//it comes back to the original player's turn
					cin.ignore();						//there was an extra 0 in the input buffer
					Sleep(2000);						//time delay of 2 seconds
					cout << "Your progress has been saved." << endl;
					return true;		//and continue playing
				}
				else if (x1 == -2) {
					LoadGame();			//load the game
					cout << "Loading previous game..." << endl;
					if (turn == 1) turn = 2;
					else if (turn == 2) turn = 1;
					cin.ignore();
					Sleep(2000);
					return true;		//and continue playing
				}
				else if (x1 == -3) {
					NewGame();			//load new game
					cout << "Loading new game..." << endl;
					cin.ignore();
					Sleep(2000);
					return true;		//and continue playing
				}
				else if (x1 == -4) {
					cout << "Quitting..." << endl;
					Sleep(2000);
					return false;
				}

				dest = board[x2][y2].getPiece();

				char Tile;
				Tile = board[x1][y1].getPiece();

				if (Tile == 'R' || Tile == 'r') {
					stop = moveRook(x1, y1, x2, y2, false);
				}
				else if (Tile == 'B' || Tile == 'b') {
					stop = moveBishop(x1, y1, x2, y2, false);
				}
				else if (Tile == 'N' || Tile == 'n') {
					stop = moveKnight(x1, y1, x2, y2, false);
				}
				else if (Tile == 'K' || Tile == 'k') {
					stop = moveKing(x1, y1, x2, y2, false);
				}
				else if (Tile == 'Q' || Tile == 'q') {
					stop = moveQueen(x1, y1, x2, y2, false);
				}
				else if (Tile == 'P' || Tile == 'p') {
					stop = movePawns(x1, y1, x2, y2, false);
				}
				else {
					stop = false;
				}
			}
			if (stop == true && (dest == 'k' || dest == 'K')) {
				SetConsoleTextAttribute(out, 4);	//red
				cout << "CHECKMATE!" << endl;
				if (turn == 1) cout << "PLAYER 1 WINS!!!" << endl;
				else cout << "PLAYER 2 WINS!!!" << endl;
				SetConsoleTextAttribute(out, 7);	//white
				retval = false;
			}
			IsInCheck = check(x2, y2);
			if (IsInCheck == true) {
				IsInCheckmate = checkmate(x2, y2);
				if (IsInCheckmate == false){
					SetConsoleTextAttribute(out, 4);	//red
					cout << "CHECK!" << endl;
					SetConsoleTextAttribute(out, 7);	//white
					Sleep(3000);
				}
				else {
					SetConsoleTextAttribute(out, 4);	//red
					cout << "CHECKMATE!" << endl;
					if (turn == 1) cout << "PLAYER 1 WINS!!!" << endl;
					else cout << "PLAYER 2 WINS!!!" << endl;
					SetConsoleTextAttribute(out, 7);	//white
					retval = false;
				}
			}
			return retval;		//only checkmate makes it false;
        }

		bool Board:: checkMove (int &x1, int &x2, int &y1, int &y2){
			bool retval=true;
				char a;
				char b;
				cout<<"***     Player "<<turn<<"'s turn     ***"<<endl;
			cout<<"Enter the location of piece you want to move "<<endl;
			cin>>x1;
			cin >> a;
			if (x1 == -1) {				//leave everything, save the game
				return true;
			}
			else if (x1 == -2) {		//leave everything, load the game
				return true;
			}
			else if (x1 == -3) {		//leave everything, load new game
				return true;
			}
			else if (x1 == -4) {		//leave everything, quit
				return true;
			}
			while (x1<1 || x1>8 || a<'a' || a>'h'){
				cout<<"Error enter coordinates again "<<endl;
				cin>>x1;
				cin>>a;
			}
			
			cout<<"Enter the location you want your piece to move "<<endl;
			cin>>x2;
			cin>>b;
			while (x2<1 || x2>8 || b<'a' || b>'h'){
				cout<<"Error enter coordinates again "<<endl;
				cin>>x2;
				cin>>b;
			}

			while (x1==x2 && a==b){
				cout<<"Error enter coordinates again "<<endl;
				cin>>x1;
				cin>>a;
				cin>>x2;
				cin>>b;
			}

			if (x1==8){
				x1=0;
			}
			else if (x1==7){
				x1=1;
			}
			else if (x1==6){
				x1=2;
			}
			else if (x1==5){
				x1=3;
			}
			else if (x1==4){
				x1=4;
			}
			else if (x1==3){
				x1=5;
			}
			else if (x1==2){
				x1=6;
			}
			else if (x1==1){
				x1=7;
			}

			if (x2==8){
				x2=0;
			}
			else if (x2==7){
				x2=1;
			}
			else if (x2==6){
				x2=2;
			}
			else if (x2==5){
				x2=3;
			}
			else if (x2==4){
				x2=4;
			}
			else if (x2==3){
				x2=5;
			}
			else if (x2==2){
				x2=6;
			}
			else if (x2==1){
				x2=7;
			}

			 y1=(static_cast<int>(a))-97;
			 y2=(static_cast<int>(b))-97;
			
		char Tile;
			Tile=board[x1][y1].getPiece();
			if (Tile=='E'){
				cout<<"There is no piece on that tile. Enter coordinates again."<<endl;
				retval=false;
			}

			if (turn==1){
				if (Tile>='a' && Tile<='z'){
					cout<<"You cannot move Player 2's pieces. Enter coordinates again "<<endl;
					retval=false;
				}
			}
			else if (turn==2){
				if (Tile>='A' && Tile<='Z'){							//&& error
					cout<<"You cannot move Player 1's pieces. Enter coordinates again "<<endl;
					retval=false;
				}
			}
			return retval;

			}
			
		bool Board:: moveRook(int x1, int y1, int x2, int y2, bool usingforcheck){
            bool okay=false;
				okay=true;
				if (x1==x2 || y1==y2){
					if (x1==x2){
						int yinc;
						yinc=(y2-y1)/abs(y2-y1);
						for (int i=y1+yinc; i!=y2; i+=yinc){
							if (board[x1][i].getPiece()!='E'){
								if (usingforcheck == false) {
									cout << "There is a piece in the way " << endl;
								}
								okay=false;
							}
							else 
								okay=true;
						}
					}
						else if (y1==y2){
						int xinc;
						xinc=(x2-x1)/abs(x2-x1);
						for (int i=x1+xinc; i!=x2; i+=xinc){
							if(board[i][y1].getPiece()!='E'){
								if (usingforcheck == false) {
									cout << "There is a piece in the way " << endl;
								}
								okay=false;
							}
							else 
								okay=true;
						}
					}
				}
				else {
					okay=false;
					if (usingforcheck == false) {
						cout << "Invalid move for Rook" << endl;
					}
				}

			if (okay==true){
				char destination= board[x2][y2].getPiece();
				char current= board[x1][y1].getPiece();

				if (destination=='E'){
					if (usingforcheck == false) {
						board[x2][y2].setPiece(current);
						board[x1][y1].setPiece('E');
					}
				}
				else {
					if ((turn==1 && destination>'A' && destination<'Z') || (turn==2 && destination>'a' && destination<'z')){
						if (usingforcheck == false) {
							cout << "You cannot capture your own piece " << endl;
						}
						okay=false;
					}
					else 
					{
						if (usingforcheck == false) {
							if (turn == 1) {
								p2->capture(destination);
							}
							else if (turn == 2) {
								p1->capture(destination);
							}
							board[x2][y2].setPiece(current);
							board[x1][y1].setPiece('E');
						}
					}
				}
			}
			return okay;
		}
		
		bool Board:: moveKnight(int x1, int y1, int x2, int y2, bool usingforcheck){
			bool okay=false;
				okay=true;
				if (abs(x2-x1)==2 && abs(y2-y1)==1 || abs(x2-x1)==1 && abs(y2-y1)==2){
				okay=true;
			}
			else {
				okay=false;
				if (usingforcheck == false) {
					cout << "Invalid move for Knight" << endl;
				}
			}

			if (okay==true){
				char destination= board[x2][y2].getPiece();
				char current= board[x1][y1].getPiece();

				if (destination=='E'){
					if (usingforcheck == false) {
						board[x2][y2].setPiece(current);
						board[x1][y1].setPiece('E');
					}
				}
				else {
					if ((turn==1 && destination>'A' && destination<'Z') || (turn==2 && destination>'a' && destination<'z')){
						if (usingforcheck == false) {
							cout << "You cannot capture your own piece " << endl;
						}
						okay=false;
					}
					else 
					{
						if (usingforcheck == false) {
							if (turn == 1) {
								p2->capture(destination);
							}
							else if (turn == 2) {
								p1->capture(destination);
							}
							board[x2][y2].setPiece(current);
							board[x1][y1].setPiece('E');
						}
					}
			}
			}
			return okay;
		}
		
		bool Board:: moveBishop(int x1, int y1, int x2, int y2, bool usingforcheck) {
			bool okay=false;
			int i, j;
				okay=true;
				if ((x1==x2) || (y1==y2)){
					okay=false;
					if (usingforcheck == false) {
						cout << "Invalid move for Bishop" << endl;
					}
				}
				int absX=abs(x2-x1);
				int absY=abs(y2-y1);

				if (absX!=absY){
					okay=false;
					if (usingforcheck == false) {
						cout << "Invalid move for Bishop" << endl;
					}
				}

				if (absX==absY){
					if ((x2>x1) && (y2>y1)){
						for (i=x1+1,j=y1+1; i!=x2 && j!=y2; i++, j++){
							if (board[i][j].getPiece()!='E'){
								okay=false;
								if (usingforcheck == false) {
									cout << "There is a piece in the way" << endl;
								}
							}
							else 
								okay=true;
						}
					}
					else if ((x2<x1) && (y2>y1)){
						for (i = x1 - 1, j = y1 + 1; i != x2 && j != y2; i--, j++) {
							if (board[i][j].getPiece() != 'E') {
								okay = false;
								if (usingforcheck == false) {
									cout << "There is a piece in the way " << endl;
								}
							}
							else
								okay = true;
						}
					}
					else if ((x2>x1) && (y2<y1)){
						for (i=x1+1, j=y1-1; i!=x2 && j!=y2; i++,j--){
							if (board[i][j].getPiece()!='E'){
								okay=false;
								if (usingforcheck == false) {
									cout << "There is a piece in the way " << endl;
								}
							}
							else 
								okay=true;
						}
					}
					else if ((x2<x1) && (y2<y1)){
						for (i=x1-1,j=y1-1; i!=x2 && j!=y2; i--,j--){
							if (board[i][j].getPiece()!='E'){
								okay=false;
								if (usingforcheck == false) {
									cout << "There is a piece in the way " << endl;
								}
							}
							else 
								okay=true;
						}
					}
				}

			if (okay==true){
				char destination= board[x2][y2].getPiece();
				char current= board[x1][y1].getPiece();

				if (destination=='E'){
					if (usingforcheck == false) {
						board[x2][y2].setPiece(current);
						board[x1][y1].setPiece('E');
					}
				}
				else {
					if ((turn==1 && destination>'A' && destination<'Z') || (turn==2 && destination>'a' && destination<'z')){
						if (usingforcheck == false) {
							cout << "You cannot capture your own piece " << endl;
						}
						okay=false;
					}
					else {
						if (usingforcheck == false) {
							if (turn == 1) {
								p2->capture(destination);
							}
							else if (turn == 2) {
								p1->capture(destination);
							}
							board[x2][y2].setPiece(current);
							board[x1][y1].setPiece('E');
						}
					}
				}
			}
			return okay;
		}
		
		bool Board:: moveQueen(int x1, int y1, int x2, int y2, bool usingforcheck){
			bool okay=true;
			if (x1==x2 || y1==y2){
				if (x1==x2){
					int yinc;
					yinc=(y2-y1)/abs(y2-y1);
					for (int i=y1+yinc; i!=y2; i+=yinc){
						if (board[x1][i].getPiece()!='E'){
							if (usingforcheck == false) {
								cout << "There is a piece in the way " << endl;
							}
							okay=false;
						}
						else 
							okay=true;
					}
				}
				else if (y1==y2){
					int xinc;
					xinc=(x2-x1)/abs(x2-x1);
					for (int i=x1+xinc; i!=x2; i+=xinc){
						if(board[i][y1].getPiece()!='E'){
							if (usingforcheck == false) {
								cout << "There is a piece in the way " << endl;
							}
							okay=false;
						}
						else 
							okay=true;
					}
				}
			}
			int absX=abs(x2-x1);
			int absY=abs(y2-y1);

			int i, j;
			if (absX==absY){
				if ((x2>x1) && (y2>y1)){
					for (i=x1+1,j=y1+1; i!=x2 && j!=y2; i++,j++){
						if (board[i][j].getPiece()!='E'){
							okay=false;
							if (usingforcheck == false) {
								cout << "There is a piece in the way " << endl;
							}
						}
						else 
							okay=true;
					}
				}
				else if ((x2<x1) && (y2>y1)){
					for (i=x1-1,j=y1+1; i!=x2 && j!=y2; i--,j++){
						if (board[i][j].getPiece()!='E'){
							okay=false;
							if (usingforcheck == false) {
								cout << "There is a piece in the way " << endl;
							}
								
						}
						else 
							okay=true;
					}
				}
				else if ((x2>x1) && (y2<y1)){
					for (i=x1+1,j=y1-1; i!=x2 && j!=y2; i++,j--){
						if (board[i][j].getPiece()!='E'){
							okay=false;
							if (usingforcheck == false) {
								cout << "There is a piece in the way " << endl;
							}
								
						}
						else 
							okay=true;
					}
				}
				else if ((x2<x1) && (y2<y1)){
					for (i=x1-1,j=y1-1; i!=x2 && j!=y2; i--,j--){
						if (board[i][j].getPiece()!='E'){
							okay=false;
							if (usingforcheck == false) {
								cout << "There is a piece in the way " << endl;
							}
						}
						else 
							okay=true;
					}
				}
			}
			if (okay==true){
				char destination= board[x2][y2].getPiece();
				char current= board[x1][y1].getPiece();

				if (destination=='E'){
					if (usingforcheck == false) {
						board[x2][y2].setPiece(current);
						board[x1][y1].setPiece('E');
					}
				}
				else {
					if ((turn==1 && destination>'A' && destination<'Z') || (turn==2 && destination>'a' && destination<'z')){
						if (usingforcheck == false) {
							cout << "You cannot capture your own piece " << endl;
						}
						okay=false;
					}
					else 
					{
						if (usingforcheck == false) {
							if (turn == 1) {
								p2->capture(destination);
							}
							else if (turn == 2) {
								p1->capture(destination);
							}
							board[x2][y2].setPiece(current);
							board[x1][y1].setPiece('E');
						}
					}
				}
			}
			return okay;
		}
		
		bool Board:: moveKing(int x1, int y1, int x2, int y2, bool usingforcheck){
			bool okay=false;
			if (abs(x2-x1)==1 && abs(y2-y1)==1){
				okay=true;
			}
			else if ((x1==x2 && abs(y2-y1)==1) || (y1==y2 && abs(x2-x1)==1)){
						okay=true;
			}
			else {
				if (usingforcheck == false) {
					cout << "Invalid Move for King" << endl;
				}
				okay=false;
			}		
			if (okay==true){
				char destination= board[x2][y2].getPiece();
				char current= board[x1][y1].getPiece();

				if (destination=='E'){
					if (usingforcheck == false) {
						board[x2][y2].setPiece(current);
						board[x1][y1].setPiece('E');
						if (turn == 1) {
							p1->setkingX(x2);
							p1->setkingY(y2);
						}
						else {
							p2->setkingX(x2);
							p2->setkingY(y2);
						}
					}
				}
				else {
					if ((turn==1 && destination>'A' && destination<'Z') || (turn==2 && destination>'a' && destination<'z')){
						if (usingforcheck == false) {
							cout << "You cannot capture your own piece " << endl;
						}
						okay=false;
					}
					else 
					{
						if (usingforcheck == false) {
							if (turn == 1) {
								p2->capture(destination);
							}
							else if (turn == 2) {
								p1->capture(destination);
							}
							board[x2][y2].setPiece(current);
							board[x1][y1].setPiece('E');
							if (turn == 1) {
								p1->setkingX(x2);
								p1->setkingY(y2);
							}
							else {
								p2->setkingX(x2);
								p2->setkingY(y2);
							}
						}
					}
			}
		}
			return okay;
		}

		bool Board:: movePawns(int x1, int y1, int x2, int y2, bool usingforcheck){
			bool okay=false;
			bool okay2=false;
			if (y1==y2){
				if ((turn==1 && board[6][y1].getPiece()=='P') || (turn==2 && board[1][y1].getPiece()=='p')){
					if ((turn==1 && ((x2-x1)==-2 || (x2-x1)==-1)) || (turn==2 && ((x2-x1)==2 || (x2-x1)==1))) {
						okay=true;
					}
					else {
						okay=false;
						if (usingforcheck == false) {
							cout << "Invalid move for Pawn" << endl;
						}
					}
				}
				else {
					if ((turn==1 && (x2-x1)==-1) || (turn==2 && (x2-x1)==1)){
						okay=true;
					}
					else {
						okay=false;
						if (usingforcheck == false) {
							cout << "Invalid move for Pawn" << endl;
						}
					}
				}
			}
			if (okay==false){
				if ((turn==1 && (x2-x1)==-1 && abs(y2-y1)==1) || (turn==2 && (x2-x1)==1 && abs(y2-y1)==1)){
					char destination= board[x2][y2].getPiece();
					char current= board[x1][y1].getPiece();

					if (destination!='E'){
						okay2=true;
					}
				}
				else {
					okay2=false;
					if (usingforcheck == false) {
						cout << "Invalid move for Pawn" << endl;
					}
				}
			}
			if (okay==false && okay2==false) {
				if (usingforcheck == false) {
					cout << "Invalid move for Pawn" << endl;
				}
			}
			if (okay==true){
				char destination= board[x2][y2].getPiece();
				char current= board[x1][y1].getPiece();

				if (destination=='E'){
					if (usingforcheck == false) {
						board[x2][y2].setPiece(current);
						board[x1][y1].setPiece('E');
					}
				}
				else {
					if ((turn==1 && destination>'A' && destination<'Z') || (turn==2 && destination>'a' && destination<'z')){
						if (usingforcheck == false) {
							cout << "You cannot capture your own piece " << endl;
						}
						okay=false;
					}
					else 
					{
						if (usingforcheck == false) {
							if (turn == 1) {
								p2->capture(destination);
							}
							else if (turn == 2) {
								p1->capture(destination);
							}
							board[x2][y2].setPiece(current);
							board[x1][y1].setPiece('E');
						}
					}
				}
			}

			if (okay2==true){
				char destination1= board[x2][y2].getPiece();
				char current1= board[x1][y1].getPiece();
				if ((turn==1 && destination1>'A' && destination1<'Z') || (turn==2 && destination1>'a' && destination1<'z')){
					if (usingforcheck == false) {
						cout << "You cannot capture your own piece " << endl;
					}
					okay=false;
				}
				else {
					if (usingforcheck == false) {
						if (turn == 1) {
							p2->capture(destination1);
						}
						else if (turn == 2) {
							p1->capture(destination1);
						}
						board[x2][y2].setPiece(current1);
						board[x1][y1].setPiece('E');
					}
				}
			}
			if (okay==true || okay2==true){
				char c;
				if ((turn == 1 && x2 == 0) || (turn == 2 && x2 == 7)) {
					if (usingforcheck == false) {
						cout << "Enter the character of the piece you want to promote this pawn to (except King): " << endl;
						cin >> c;
						while (c != 'q' && c != 'r' && c != 'b' && c != 'n' && c != 'Q' && c != 'R' && c != 'B' && c != 'N') {
							cout << "You can only promote to Queen, Bishop, Rook or Knight. Enter again: " << endl;
							cin >> c;
						}
						if (turn == 1) c = toupper(c);
						else if (turn == 2) c = tolower(c);
						board[x2][y2].setPiece(c);
						if (turn == 1) p1->promotePawn(c);
						else if (turn == 2) p2->promotePawn(c);
					}
				}
				return true;
			}
			else{
				return false;
			}
		}

		void Board::SaveGame() {
			ofstream fout("chess.txt");
			fout << turn << endl;
			for (int i = 0; i < 16; i++) {
				fout << p1->getpieces(i) << " ";
			}
			fout << endl;
			fout << p1->getkingX() << " " << p1->getkingY() << endl;
			for (int i = 0; i < 16; i++) {
				fout << p2->getpieces(i) << " ";
			}
			fout << endl;
			fout << p2->getkingX() << " " << p2->getkingY() << endl;
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					fout << board[i][j].getPiece() << " ";
				}
				fout << endl;
			}
			fout.close();
		}

		void Board::LoadGame() {
			char a;
			int b;
			ifstream fin("chess.txt");
			fin >> turn;
			for (int i = 0; i < 16; i++) {
				fin >> a;
				p1->setpieces(i, a);
			}
			fin >> b;
			p1->setkingX(b);
			fin >> b;
			p1->setkingY(b);
			for (int i = 0; i < 16; i++) {
				fin >> a;
				p2->setpieces(i, a);
			}
			fin >> b;
			p2->setkingX(b);
			fin >> b;
			p2->setkingY(b);
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					fin >> a;
					board[i][j].setPiece(a);
				}
			}
			fin.close();
		}

		void Board::NewGame() {
			setBoard();
			turn = 2;		//so that it becomes 1 when MakeMove called next time
			delete p1;
			delete p2;
			p1 = new Player(1);
			p2 = new Player(2);
		}

		bool Board::check(int x, int y) {
			bool IsInCheck = true;
			int kingX;
			int kingY;
			if (turn == 1) {
				kingX = p2->getkingX();
				kingY = p2->getkingY();
			}
			else {
				kingX = p1->getkingX();
				kingY = p1->getkingY();
			}
			char p = board[x][y].getPiece();
			if (p == 'Q' || p == 'q') {
				IsInCheck = moveQueen(x, y, kingX, kingY, true);
			}
			else if (p == 'R' || p == 'r') {
				IsInCheck=moveRook(x, y, kingX, kingY, true);
			}
			else if (p == 'N' || p == 'n') {
				IsInCheck = moveKnight(x, y, kingX, kingY, true);
			}
			else if (p == 'B' || p == 'b') {
				IsInCheck = moveBishop(x, y, kingX, kingY, true);
			}
			else if (p == 'P' || p == 'p') {
				IsInCheck = movePawns(x, y, kingX, kingY, true);
			}
			else if (p == 'K' || p == 'k') {
				IsInCheck = moveKing(x, y, kingX, kingY, true);
			}
			else {
				IsInCheck = false;
			}
			return IsInCheck;
		}

		bool Board::checkmate(int x, int y) {
			bool IsInCheckMate = false;
			bool b1 = false, b2 = false, b3 = false, b4 = false, b5 = false, b6 = false, b7 = false, b8 = false;
			int kingX;
			int kingY;
			if (turn == 1) {
				kingX = p2->getkingX();
				kingY = p2->getkingY();
			}
			else {
				kingX = p1->getkingX();
				kingY = p1->getkingY();
			}
			char p = board[x][y].getPiece();
			int newkingX, newkingY;

			newkingX = kingX;
			newkingY = kingY + 1;			//right
			if (newkingY < 8 && board[newkingX][newkingY].getPiece()=='E') {
				if (p == 'Q' || p == 'q') b1 = moveQueen(x, y, newkingX, newkingY, true);
				else if (p == 'R' || p == 'r') b1 = moveRook(x, y, newkingX, newkingY, true);
				else if (p == 'N' || p == 'n') b1 = moveKnight(x, y, newkingX, newkingY, true);
				else if (p == 'B' || p == 'b') b1 = moveBishop(x, y, newkingX, newkingY, true);
				else if (p == 'P' || p == 'p') b1 = movePawns(x, y, newkingX, newkingY, true);
				else if (p == 'K' || p == 'k') b1 = moveKing(x, y, newkingX, newkingY, true);
			}

			newkingX = kingX;
			newkingY = kingY - 1;			//left
			if (newkingY >= 0 && board[newkingX][newkingY].getPiece() == 'E') {
				if (p == 'Q' || p == 'q') b2 = moveQueen(x, y, newkingX, newkingY, true);
				else if (p == 'R' || p == 'r') b2 = moveRook(x, y, newkingX, newkingY, true);
				else if (p == 'N' || p == 'n') b2 = moveKnight(x, y, newkingX, newkingY, true);
				else if (p == 'B' || p == 'b') b2 = moveBishop(x, y, newkingX, newkingY, true);
				else if (p == 'P' || p == 'p') b2 = movePawns(x, y, newkingX, newkingY, true);
				else if (p == 'K' || p == 'k') b2 = moveKing(x, y, newkingX, newkingY, true);
			}

			newkingX = kingX + 1;
			newkingY = kingY;			//below
			if (newkingX < 8 && board[newkingX][newkingY].getPiece() == 'E') {
				if (p == 'Q' || p == 'q') b3 = moveQueen(x, y, newkingX, newkingY, true);
				else if (p == 'R' || p == 'r') b3 = moveRook(x, y, newkingX, newkingY, true);
				else if (p == 'N' || p == 'n') b3 = moveKnight(x, y, newkingX, newkingY, true);
				else if (p == 'B' || p == 'b') b3 = moveBishop(x, y, newkingX, newkingY, true);
				else if (p == 'P' || p == 'p') b3 = movePawns(x, y, newkingX, newkingY, true);
				else if (p == 'K' || p == 'k') b3 = moveKing(x, y, newkingX, newkingY, true);
			}

			newkingX = kingX - 1;
			newkingY = kingY;			//above
			if (newkingX >= 0 && board[newkingX][newkingY].getPiece() == 'E') {
				if (p == 'Q' || p == 'q') b4 = moveQueen(x, y, newkingX, newkingY, true);
				else if (p == 'R' || p == 'r') b4 = moveRook(x, y, newkingX, newkingY, true);
				else if (p == 'N' || p == 'n') b4 = moveKnight(x, y, newkingX, newkingY, true);
				else if (p == 'B' || p == 'b') b4 = moveBishop(x, y, newkingX, newkingY, true);
				else if (p == 'P' || p == 'p') b4 = movePawns(x, y, newkingX, newkingY, true);
				else if (p == 'K' || p == 'k') b4 = moveKing(x, y, newkingX, newkingY, true);
			}

			newkingX = kingX + 1;
			newkingY = kingY + 1;		//bottom right
			if (newkingY < 8 && newkingX < 8 && board[newkingX][newkingY].getPiece() == 'E') {
				if (p == 'Q' || p == 'q') b5 = moveQueen(x, y, newkingX, newkingY, true);
				else if (p == 'R' || p == 'r') b5 = moveRook(x, y, newkingX, newkingY, true);
				else if (p == 'N' || p == 'n') b5 = moveKnight(x, y, newkingX, newkingY, true);
				else if (p == 'B' || p == 'b') b5 = moveBishop(x, y, newkingX, newkingY, true);
				else if (p == 'P' || p == 'p') b5 = movePawns(x, y, newkingX, newkingY, true);
				else if (p == 'K' || p == 'k') b5 = moveKing(x, y, newkingX, newkingY, true);
			}

			newkingX = kingX + 1;
			newkingY = kingY - 1;		//bottom left
			if (newkingY >= 0 && newkingX < 8 && board[newkingX][newkingY].getPiece() == 'E') {
				if (p == 'Q' || p == 'q') b6 = moveQueen(x, y, newkingX, newkingY, true);
				else if (p == 'R' || p == 'r') b6 = moveRook(x, y, newkingX, newkingY, true);
				else if (p == 'N' || p == 'n') b6 = moveKnight(x, y, newkingX, newkingY, true);
				else if (p == 'B' || p == 'b') b6 = moveBishop(x, y, newkingX, newkingY, true);
				else if (p == 'P' || p == 'p') b6 = movePawns(x, y, newkingX, newkingY, true);
				else if (p == 'K' || p == 'k') b6 = moveKing(x, y, newkingX, newkingY, true);
			}

			newkingX = kingX - 1;
			newkingY = kingY + 1;		//top right
			if (newkingY < 8 && newkingX >= 0 && board[newkingX][newkingY].getPiece() == 'E') {
				if (p == 'Q' || p == 'q') b7 = moveQueen(x, y, newkingX, newkingY, true);
				else if (p == 'R' || p == 'r') b7 = moveRook(x, y, newkingX, newkingY, true);
				else if (p == 'N' || p == 'n') b7 = moveKnight(x, y, newkingX, newkingY, true);
				else if (p == 'B' || p == 'b') b7 = moveBishop(x, y, newkingX, newkingY, true);
				else if (p == 'P' || p == 'p') b7 = movePawns(x, y, newkingX, newkingY, true);
				else if (p == 'K' || p == 'k') b7 = moveKing(x, y, newkingX, newkingY, true);
			}

			newkingX = kingX - 1;
			newkingY = kingY - 1;		//top left
			if (newkingY >= 0 && newkingX >= 0 && board[newkingX][newkingY].getPiece() == 'E') {
				if (p == 'Q' || p == 'q') b8 = moveQueen(x, y, newkingX, newkingY, true);
				else if (p == 'R' || p == 'r') b8 = moveRook(x, y, newkingX, newkingY, true);
				else if (p == 'N' || p == 'n') b8 = moveKnight(x, y, newkingX, newkingY, true);
				else if (p == 'B' || p == 'b') b8 = moveBishop(x, y, newkingX, newkingY, true);
				else if (p == 'P' || p == 'p') b8 = movePawns(x, y, newkingX, newkingY, true);
				else if (p == 'K' || p == 'k') b8 = moveKing(x, y, newkingX, newkingY, true);
			}
			if (!b1 && !b2 && !b3 && !b4 && !b5 && !b6 && !b7 && !b8) {
				IsInCheckMate = true;
			}
			else {
				IsInCheckMate = false;
			}
			return IsInCheckMate;
		}

		//to test Checkmate:
		//	Player 1: 2 f to 3 f
		//	Player 2: 7 e to 5 e
		//	Player 1: 2 g to 4 g
		//	Player 2: 8 d to 4 h