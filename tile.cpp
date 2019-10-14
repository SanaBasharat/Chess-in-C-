#include "tile.h"


   tile::tile (){
        color=nullptr;
        piece='\0';
    }
    tile::tile (char * C, char P){
        int counter=0;
         for (int i=0; C[i]!='\0'; i++){
             color = new char [i];
             counter++;
         }
         for (int i=0; C[i]!='\0'; i++){
             color[i]=C[i];
         }
         color[counter]='\0';
         

         piece=P;

}

    tile::~tile (){
        //delete [] color;

}

    tile::tile (const tile & x){
        for (int i=0; x.color[i]!='\0'; i++){
            color[i]=x.color[i];
        }
        piece=x.piece;
}

    void tile::setColor(char * c) {
        int counter=0;
        if (color!=nullptr){
            delete color;
            
        }
		for (int i=0; c[i]!='\0'; i++){
			counter++;
		}
		color=new char[counter];

		for (int i=0; c[i]!='\0'; i++){
				color[i]=c[i];
		}
		color[counter]='\0';
        
        
    }
        

    void tile::setPiece (char p){
        piece=p;


    }

    char * tile::getColor (){

        return color;


    }

    char tile::getPiece (){

        return piece;

    }