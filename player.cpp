#include "player.h"
#include <iostream>
using namespace std;

Player :: Player (){
	playerNum=0;
}

Player :: Player (int pN){
	playerNum=pN;
	
	pieces=new char [16];
	if (playerNum==1){
		pieces[0]='R';
		pieces[1]='N';
		pieces[2]='B';
		pieces[3]='K';
		pieces[4]='Q';
		pieces[5]='B';
		pieces[6]='N';
		pieces[7]='R';

		for (int i=8; i<16; i++){
			pieces[i]='P';
		}
	}
	else if (playerNum==2){
		pieces[0]='r';
		pieces[1]='n';
		pieces[2]='b';
		pieces[3]='k';
		pieces[4]='q';
		pieces[5]='b';
		pieces[6]='n';
		pieces[7]='r';

		for (int i=8; i<16; i++){
			pieces[i]='p';
		}
	}
}
	Player :: Player (const Player & obj){
		playerNum=obj.playerNum;
	}
	
	void Player :: capture (char x){
		for (int i=0; i<16; i++){
			if (pieces[i]==x){
				pieces[i]='\0';
			}
		}
	}

	char Player::getpieces(int n) {
		return pieces[n];
	}

	void Player::setpieces(int n, char a) {
		pieces[n] = a;
	}

	void Player::promotePawn(char c) {
		bool found = false;
		int i;
		for (i=0;i<16 && !found;i++) {
			if (playerNum==1 && pieces[i] == 'P') found = true;
			else if (playerNum == 2 && pieces[i] == 'p') found = true;
		}
		pieces[i] = c;
	}

Player :: ~Player () {

}

void Player::setkingX(int x) {
	kingX = x;
}

void Player::setkingY(int x) {
	kingY = x;
}

int Player::getkingX() {
	return kingX;
}

int Player::getkingY() {
	return kingY;
}