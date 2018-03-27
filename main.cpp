#include <string>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <random>
#include <utility>
#include <iomanip>

using namespace std;

// Define the chessboard as an 8x8
//the number of times the king will
//be placed on the board.
const int RUNS = 100000;
const int NROWS = 8;
const int NCOLS = 8;

//Create a random number generator function
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static mt19937 generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

// Create the Chessboard Class
class ChessBoard {
    public:
        ChessBoard();
    private:
        int spaces_[NROWS][NCOLS];
};

//Chessboard Constructor
ChessBoard::ChessBoard(){
    for (int r = 0; r < NROWS; r++)
        for (int c = 0; c < NCOLS; c++)
            spaces_[r][c] = 0;
}

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
    private:
        int r_;
        int c_;
        ChessBoard* cb_;
};

//Construct a King with a pointer to the Constructed Chessboard
//Setting it's own rows and columns with the rows and columns
//from the chessboard.
King::King(int r, int c, ChessBoard* cb){
    if (r < 0 || r >= NROWS || c < 0 || c >= NCOLS){
        cout << "Cannot place King at (" << r << "," << c << ")" << endl;
        exit(1);
    }
    if (cb == nullptr){
        cout << "King must be placed inside chessboard! " << endl;
    }
    r_ = r;
    c_ = c;
    cb_ = cb;
}

//Create a function to reset the King onto the chessboard
//that way he is placed randomly onto the chessboard.
void King::resetKing(){
    countReset++;
 //   cout << "The King BEFORE RESET : (" << r_ << "," << c_ << ")" << endl;
    int rn1 = (randInt(0,7));
    int rn2 = (randInt(0,7));
    //create King and put him on board randomly
//      r_ = rn1;
//      c_ = rn2;
    r_ = 2;
    c_ = 4;
 //   cout << "The King RESET to (" << r_ << "," << c_ << ")" << endl;
}

//Create a "Check" function to check on if the king fell
//off the board or not. This function keeps track of
//where the King actually falls off.
void King::check(){

    //Check if king moved off board
    if (r_ < 0 || r_ >= NROWS || c_ < 0 || c_ >= NCOLS){
	if (r_ == -1 && c_ == -1){
//	cout << "King Fell off the NW at (" << r_ << "," << c_ << ")" << endl;
	fallsNW++;
	}
	else if ((r_ == -1) && (c_ >= NCOLS)) {
//	cout << "King Fell off the NE" << endl;
	fallsNE++;
	}
        else if ((r_ >= NROWS) && (c_ >= NCOLS)){
//        cout << "King Fell off the SE" << endl;
        fallsSE++;
	}
        else if ((r_ >= NROWS) && (c_ == -1)){
//        cout << "King Fell off the SW" << endl;
        fallsSW++;
	}
        else if ((r_ < 0) && (c_ != NCOLS || c_ != -1)){
//        cout << "King Fell off the North" << endl;
        fallsNorth++;
	}
	else if ((c_ == NROWS) && (r_ != NROWS || r_ != -1)){
//	cout << "King Fell off the East at (" << r_ << "," << c_ << ")" << endl;
	fallsEast++;
	}
	else if ((r_ >= NCOLS) && (c_ != NROWS || c_ != -1)){
//	cout << "King Fell off the South" << endl;
	fallsSouth++;
	}
	else if ((c_ < 0) && (r_ != NCOLS || r_ != -1)){
//	cout << "King Fell off the West" << endl;
	fallsWest++;
	}
      totalFalls++;
      resetKing();
    } else {
//	cout << "King still on board " << endl;
      }

}

//Create a function to move the King one space at a time.
void King::move(){
//   cout << "The King starts at (" << r_ << "," << c_ << ")" << endl;
   switch (randInt(0,7))
   {
     //case 0 North
     case 0:  r_--; countMoves++; break;
     //case 1 North West
     case 1:  r_--; c_--; countMoves++; break;
     //case 2 North East
     case 2:  r_--; c_++; countMoves++; break;
     //case 3 South
     case 3:  r_++; countMoves++; break;
     //case 4 South East
     case 4:  r_++; c_++; countMoves++; break;
     //case 5 South West
     case 5:  r_++; c_--; countMoves++; break;
     //case 6 East
     case 6:  c_++; countMoves++; break;
     //case 7 West
     case 7:  c_--; countMoves++; break;
   }

  // cout << "The King is moved to (" << r_ << "," << c_ << ")" << endl;
}

//The main function
int main() {
    ChessBoard cboard;
    int rn1 = (randInt(0,7));
    int rn2 = (randInt(0,7));
    //create King and put him on board randomly
    King king(2,4, &cboard);
//    King king2(0,0, &cboard);
    // move the king randomly
do{
    king.move();
    king.check();
  //  king2.move();
  //  king2.check();
}while(king.totalFalls != RUNS);

    cout << "Total Number of Kings/Falls: " << king.totalFalls << endl;
    cout << "The Kings average moves: " << setprecision(4) << king.countMoves/(float)king.countReset << endl;
 
    cout << "Falls NW: " << king.fallsNW << "  " << (double)((double)king.fallsNW/(double)RUNS * 100) << "%" << endl;
    cout << "Falls  N: " << king.fallsNorth << "  " << (double)((double)king.fallsNorth/(double)RUNS * 100) << "%" << endl;
    cout << "Falls NE: " << king.fallsNE << "  " << (double)((double)king.fallsNE/(double)RUNS * 100) << "%" << endl;
    cout << "Falls  W: " << king.fallsWest << "  " << (double)((double)king.fallsWest/(double)RUNS * 100) << "%" << endl;
    cout << "Falls  E: " << king.fallsEast << "  " << (double)((double)king.fallsEast/(double)RUNS * 100) << "%" << endl;
    cout << "Falls SW: " << king.fallsSW << "  " << (double)((double)king.fallsSW/(double)RUNS * 100) << "%" << endl;
    cout << "Falls  S: " << king.fallsSouth << "  " << (double)((double)king.fallsSouth/(double)RUNS * 100) << "%" << endl;
    cout << "Falls SE: " << king.fallsSE << "  " << (double)((double)king.fallsSE/(double)RUNS * 100) << "%" << endl;

/*
    cout << "Falls  N: " << king2.fallsNorth << "  " << (double)((double)king2.fallsNorth/(double)RUNS) << "%" << endl;
    cout << "Falls NW: " << king2.fallsNW << "  " << (double)((double)king2.fallsNW/(double)RUNS) << "%" << endl;
    cout << "Falls NE: " << king2.fallsNE << "  " << (double)((double)king2.fallsNE/(double)RUNS) << "%" << endl;
    cout << "Falls  S: " << king2.fallsSouth << "  " << (double)((double)king2.fallsSouth/(double)RUNS) << "%" << endl;
    cout << "Falls SW: " << king2.fallsSW << "  " << (double)((double)king2.fallsSW/(double)RUNS) << "%" << endl;
    cout << "Falls SE: " << king2.fallsSE << "  " << (double)((double)king2.fallsSE/(double)RUNS) << "%" << endl;
    cout << "Falls  W: " << king2.fallsWest << "  " << (double)((double)king2.fallsWest/(double)RUNS) << "%" << endl;
    cout << "Falls  E: " << king2.fallsEast << "  " << (double)((double)king2.fallsEast/(double)RUNS) << "%" << endl;
*/
    return 0;
}
