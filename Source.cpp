#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "board.h"

using namespace std;

 void fontsize(int,int);



int main(){
    Board obj1;
	fontsize(15,25);
	obj1.setBoard();
    obj1.printBoard(); 
	while(obj1.playGame());
    
	cout<<endl<<endl;


    system ("pause");
    return 0;
}


void fontsize(int a, int b){  
  PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();  
  lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);  
  GetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);  
  lpConsoleCurrentFontEx->dwFontSize.X = a;  
  lpConsoleCurrentFontEx->dwFontSize.Y = b;  
  SetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);  
 }  