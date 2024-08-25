#include "ChessBoard.hpp"

ChessBoard::ChessBoard(sf::RenderWindow& window, const int rows, const int cols, const int aSquareSize) : window(window), numRows(rows), numCols(cols), squareSize(aSquareSize) {

    if (!blackSquareTexture.loadFromFile("black_square.png")) {
        std::cerr << "Error loading black square texture" << std::endl;
        exit(1);
    }

    if (!whiteSquareTexture.loadFromFile("white_square.png")) {
        std::cerr << "Error loading white square texture" << std::endl;
        exit(1);
    }

    squares = new sf::Sprite * [numRows];
    for (int i = 0; i < numRows; ++i) {
        squares[i] = new sf::Sprite[numCols];
    }

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            if ((row + col) % 2 == 0) {
                squares[row][col].setTexture(blackSquareTexture);
            }
            else {
                squares[row][col].setTexture(whiteSquareTexture);
            }
            squares[row][col].setPosition(col * squareSize, row * squareSize);
        }
    }
}

void ChessBoard::draw() {
    const int centerX = window.getSize().x / 2;
    const int centerY = window.getSize().y / 2;
    const int offsetX = centerX - (numCols * squareSize) / 2;
    const int offsetY = centerY - (numRows * squareSize) / 2;

    // Draw all the squares with the offset
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            squares[row][col].setPosition(offsetX + col * squareSize, offsetY + row * squareSize);
            window.draw(squares[row][col]);
        }
    }

    // Draw a thin brown border around the chess board
    sf::RectangleShape border(sf::Vector2f(numCols * squareSize, numRows * squareSize));
    border.setPosition(offsetX, offsetY);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(sf::Color(165, 42, 42)); // Brown color
    border.setOutlineThickness(25); // Thickness of the border
    window.draw(border);
}

sf::Vector2u ChessBoard::getWindowSize() const {
    return window.getSize();
}

ChessBoard::~ChessBoard() {
    for (int i = 0; i < numRows; ++i) {
        delete[] squares[i];
    }
    delete[] squares;
}