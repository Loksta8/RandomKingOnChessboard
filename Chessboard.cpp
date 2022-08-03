#include "Chessboard.hpp"

//Chessboard Constructor
ChessBoard::ChessBoard() : NROWS(8), NCOLS(8){
    for (int r = 0; r < NROWS; r++)
        for (int c = 0; c < NCOLS; c++)
            spaces_[r][c] = 0;
}

int ChessBoard::getNROWS(){
  return NROWS;
}

int ChessBoard::getNCOLS(){
  return NCOLS;
}
