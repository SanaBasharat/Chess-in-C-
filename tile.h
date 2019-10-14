#pragma once


class tile {
private:
    char * color;
    char piece;
public:
	tile ();
    tile (char * C, char P);

    ~tile ();

   tile (const tile & x);

    void setColor(char * c);
        

    void setPiece (char p);

    char * getColor ();

    char getPiece ();

};