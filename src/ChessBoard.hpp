#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class ChessBoard {
public:
    ChessBoard(sf::RenderWindow& window, const int rows, const int cols, const int aSquareSize);
    void draw();
    sf::Vector2u getWindowSize() const;
    ~ChessBoard();
    const int numRows;
    const int numCols;

private:
    sf::Texture blackSquareTexture;
    sf::Texture whiteSquareTexture;
    sf::Sprite** squares; // Dynamically allocated array
    const int squareSize;
    sf::RenderWindow& window;
};

#endif // CHESSBOARD_HPP