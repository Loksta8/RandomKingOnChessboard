#include "King.hpp"
#include <iostream>

using namespace std;
//Construct a King with a pointer to the Constructed Chessboard
//Setting it's own rows and columns with the rows and columns
//from the chessboard.
King::King(int r, int c, ChessBoard* cb){
    if (r < 0 || r >= cb->getNROWS() || c < 0 || c >= cb->getNCOLS()){
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
  if (r_ < 0 || r_ >= cb_->getNROWS() || c_ < 0 || c_ >= cb_->getNCOLS()){
          if (r_ == -1 && c_ == -1){
        //	  cout << "King Fell off the NW at (" << r_ << "," << c_ << ")" << endl;
	        fallsNW++;
	  }
          else if ((r_ == -1) && (c_ >= cb_->getNCOLS())) {
        //	cout << "King Fell off the NE" << endl;
	        fallsNE++;
	  }
          else if ((r_ >= cb_->getNROWS()) && (c_ >= cb_->getNCOLS())){
        //        cout << "King Fell off the SE" << endl;
                fallsSE++;
	  }
          else if ((r_ >= cb_->getNROWS()) && (c_ == -1)){
        //        cout << "King Fell off the SW" << endl;
                fallsSW++;
	  }
          else if ((r_ < 0) && (c_ != cb_->getNCOLS() || c_ != -1)){
        //        cout << "King Fell off the North" << endl;
                fallsNorth++;
	  }
          else if ((c_ == cb_->getNROWS()) && (r_ != cb_->getNROWS() || r_ != -1)){
        //	cout << "King Fell off the East at (" << r_ << "," << c_ << ")" << endl;
	        fallsEast++;
	  }
          else if ((r_ >= cb_->getNCOLS()) && (c_ != cb_->getNROWS() || c_ != -1)){
        //	cout << "King Fell off the South" << endl;
	        fallsSouth++;
	  }
          else if ((c_ < 0) && (r_ != cb_->getNCOLS() || r_ != -1)){
        //	cout << "King Fell off the West" << endl;
	        fallsWest++;
	  }
          totalFalls++;
          resetKing();
  }       else {
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

  //Create a random number generator function
int King::randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static mt19937 generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}
