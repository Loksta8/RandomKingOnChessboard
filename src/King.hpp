#ifndef KING_HPP
#define KING_HPP

#include <SFML/Graphics.hpp>
#include "ChessBoard.hpp"
#include <random>
#include <iostream>

class King {
public:
    King(int initialRow, int initialCol, ChessBoard& board, const int aSquareSize);
    void move();
    bool isOnBoard(int row, int col) const;
    void check();
    void resetKing();
    int getCurrentRow() const;
    int getCurrentCol() const;
    int getLastFallCol() const;
    int getLastFallRow() const;

    sf::Texture kingTexture;
    sf::Sprite kingSprite;
    const float KING_SCALE_FACTOR = 0.4f; // Adjust as needed
    int fallsNW = 0;
    int fallsNE = 0;
    int fallsSE = 0;
    int fallsSW = 0;
    int fallsNorth = 0;
    int fallsEast = 0;
    int fallsSouth = 0;
    int fallsWest = 0;
    int totalFalls = 0;
    int currentFallDirection = -1; // 0=UP, 1=UP-LEFT, 2=UP-RIGHT, 3=DOWN, 4=DOWN-LEFT, 5=DOWN-RIGHT, 6=RIGHT, 7=LEFT
    

private:
    int currentRow;
    int currentCol;
    int lastFallCol;
    int lastFallRow;
    const int squareSize;
    ChessBoard& board;
    int randInt(int min, int max);

};

#endif // KING_HPP