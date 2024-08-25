#include "King.hpp"
#include <utility>
#include <vector>

King::King(const int initialRow, const int initialCol, ChessBoard& board, const int squaresize)
    : currentRow(initialRow), currentCol(initialCol), board(board), squareSize(squaresize), lastFallCol(-1), lastFallRow(-1) {
    if (!kingTexture.loadFromFile("white_king.png")) {
        std::cerr << "Error loading king texture" << std::endl;
        exit(1);
    }

    kingSprite.setTexture(kingTexture);
    kingSprite.setPosition(currentCol * squareSize + (squareSize - kingSprite.getLocalBounds().width * KING_SCALE_FACTOR) / 2,
        currentRow * squareSize + (squareSize - kingSprite.getLocalBounds().height * KING_SCALE_FACTOR) / 2);
    kingSprite.setScale(KING_SCALE_FACTOR, KING_SCALE_FACTOR);
}

void King::move() {
    int direction = randInt(0, 7);

    const std::vector<std::pair<int, int>> directions = {
        {-1, 0},  // Up
        {-1, -1}, // Up-left
        {-1, 1},  // Up-right
        {1, 0},   // Down
        {1, -1},  // Down-left
        {1, 1},   // Down-right
        {0, 1},   // Right
        {0, -1}   // Left
    };

    int newRow = currentRow + directions[direction].first;
    int newCol = currentCol + directions[direction].second;

    if (isOnBoard(newRow, newCol)) {
        currentRow = newRow;
        currentCol = newCol;
        sf::Vector2u windowSize = board.getWindowSize();
        int offsetX = (windowSize.x / 2) - (board.numRows * squareSize) / 2;
        int offsetY = (windowSize.y / 2) - (board.numCols * squareSize) / 2;
        kingSprite.setPosition(offsetX + currentCol * squareSize + (squareSize - kingSprite.getLocalBounds().width * KING_SCALE_FACTOR) / 2,
            offsetY + currentRow * squareSize + (squareSize - kingSprite.getLocalBounds().height * KING_SCALE_FACTOR) / 2);
    }
    else {
        // King fell off the board
        lastFallCol = currentCol;
        lastFallRow = currentRow;
        totalFalls++;
        resetKing();
    }
}

bool King::isOnBoard(int row, int col) const {
    return row >= 0 && row < board.numRows && col >= 0 && col < board.numCols;
}

void King::check() {
    if (!isOnBoard(currentRow, currentCol)) {

        if (currentRow < 0) {
            fallsNorth++;
        }
        else if (currentRow >= board.numRows) {
            fallsSouth++;
        }
        else if (currentCol < 0) {
            fallsWest++;
        }
        else if (currentCol >= board.numCols) {
            fallsEast++;
        }

        // Check for specific corners
        if (currentRow == -1 && currentCol == -1) {
            fallsNW++;
        }
        else if (currentRow == -1 && currentCol == board.numCols - 1) {
            fallsNE++;
        }
        else if (currentRow == board.numRows - 1 && currentCol == board.numCols - 1) {
            fallsSE++;
        }
        else if (currentRow == board.numRows - 1 && currentCol == -1) {
            fallsSW++;
        }

        resetKing();
    }
}

void King::resetKing() {
    currentRow = randInt(0, board.numRows - 1);
    currentCol = randInt(0, board.numCols - 1);
    sf::Vector2u windowSize = board.getWindowSize();
    int offsetX = (windowSize.x / 2) - (board.numRows * squareSize) / 2;
    int offsetY = (windowSize.y / 2) - (board.numCols * squareSize) / 2;
    kingSprite.setPosition(offsetX + currentCol * squareSize + (squareSize - kingSprite.getLocalBounds().width * KING_SCALE_FACTOR) / 2,
        offsetY + currentRow * squareSize + (squareSize - kingSprite.getLocalBounds().height * KING_SCALE_FACTOR) / 2);
}

int King::getCurrentRow() const {
    return currentRow;
}

int King::getCurrentCol() const {
    return currentCol;
}

int King::getLastFallCol() const {
    return lastFallCol;
}

int King::getLastFallRow() const {
    return lastFallRow;
}

int King::randInt(int min, int max) {
    if (max < min) {
        std::swap(max, min);
    }

    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::uniform_int_distribution<> distro(min, max);
    return distro(generator);
}