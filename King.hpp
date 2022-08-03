#ifndef KING_HPP
#define KING_HPP

#include <random>
#include "Chessboard.hpp"

//Create the King class that will keep track of itself
class King {
    public:
        King(int r, int c, ChessBoard* cb);
	float countMoves = 0.0;
	int countReset = 0;
        void move();
    	int fallsEast = 0;
    	int fallsWest = 0;
    	int fallsNorth = 0;
    	int fallsSouth = 0;
    	int fallsNE = 0;
    	int fallsNW = 0;
    	int fallsSE = 0;
    	int fallsSW = 0;
    	int totalFalls = 0;
    	void resetKing();
    	void check();
    	int randInt(int, int);
    private:
        int r_;
        int c_;
        ChessBoard* cb_;
};
#endif
