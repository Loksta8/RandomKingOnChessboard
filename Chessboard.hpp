#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

// Create the Chessboard Class
class ChessBoard {
    public:
        ChessBoard();
        int getNROWS();
        int getNCOLS();
    private:
        int NROWS;
        int NCOLS;
        int spaces_[8][8];
};
#endif
