#include "King.hpp"
#include <SFML/Graphics.hpp>
#include <utility>
#include <vector>
#include <cstdlib>
#include <string>

King::King(const int initialRow, const int initialCol, ChessBoard& board, const int squaresize)
    : currentRow(initialRow), currentCol(initialCol), board(board), squareSize(squaresize), lastFallCol(-1), lastFallRow(-1), fallsNorth(0), fallsNE(0), fallsSouth(0), fallsSE(0), fallsWest(0), fallsNW(0), fallsEast(0), fallsSW(0) {
    // Use relative path to Resources folder (cross-platform)
    std::string resourcesPath = "Resources/white_king.png";
    if (!kingTexture.loadFromFile(resourcesPath)) {
        std::cerr << "Error loading king texture: " << resourcesPath << std::endl;
        exit(1);
    }

    kingSprite.setTexture(kingTexture);
    sf::Vector2u windowSize = board.getWindowSize();
    int offsetX = (windowSize.x / 2) - (board.numCols * squareSize) / 2;
    int offsetY = (windowSize.y / 2) - (board.numRows * squareSize) / 2;
    kingSprite.setPosition(offsetX + currentCol * squareSize + (squareSize - kingSprite.getLocalBounds().width * KING_SCALE_FACTOR) / 2,
        offsetY + currentRow * squareSize + (squareSize - kingSprite.getLocalBounds().height * KING_SCALE_FACTOR) / 2);
    kingSprite.setScale(KING_SCALE_FACTOR, KING_SCALE_FACTOR);
}

void King::move() {
    int direction = randInt(0, 7);
    
    const std::vector<std::pair<int, int>> directions = {
        {-1, 0},  // Up (North)
        {-1, -1}, // Up-left (North-West)
        {-1, 1},  // Up-right (North-East)
        {1, 0},   // Down (South)
        {1, -1},  // Down-left (South-West)
        {1, 1},   // Down-right (South-East)
        {0, 1},   // Right (East)
        {0, -1}   // Left (West)
    };
    
    int newRow = currentRow + directions[direction].first;
    int newCol = currentCol + directions[direction].second;
    
    if (isOnBoard(newRow, newCol)) {
        currentRow = newRow;
        currentCol = newCol;
        sf::Vector2u windowSize = board.getWindowSize();
        int offsetX = (windowSize.x / 2) - (board.numCols * squareSize) / 2;
        int offsetY = (windowSize.y / 2) - (board.numRows * squareSize) / 2;
        kingSprite.setPosition(offsetX + currentCol * squareSize + (squareSize - kingSprite.getLocalBounds().width * KING_SCALE_FACTOR) / 2,
            offsetY + currentRow * squareSize + (squareSize - kingSprite.getLocalBounds().height * KING_SCALE_FACTOR) / 2);
    } else {
        // King fell off the board
        // Update lastFall to the position BEFORE the fall (the valid position)
        lastFallCol = currentCol;
        lastFallRow = currentRow;
        
        // Update current position to the off-board position (the position the king tried to move to)
        currentRow = newRow;
        currentCol = newCol;
        
        totalFalls++;
        currentFallDirection = direction; // Record which direction it fell
        
        // Reset direction for next iteration
        direction = -1;
        
        check(); // Check the fall direction and increment counters
        // The caller (main.cpp) is responsible for resetting the position after a fall
    }
}

bool King::isOnBoard(int row, int col) const {
    // For testing: make falls more likely by using stricter bounds
    // This allows the king to fall off when at row 0, col 0, etc.
    // Normal behavior: requires row < 0 OR row >= numRows OR col < 0 OR col >= numCols
    return row >= 0 && row < board.numRows && col >= 0 && col < board.numCols;
}

void King::check() {
    // Determine fall direction based on WHERE the king fell from, not movement direction
    if (!isOnBoard(currentRow, currentCol)) {
        // Check corner falls FIRST (both row and col off-board)
        if (currentRow < 0 && currentCol < 0) {
            // Top-left corner → NW
            fallsNW++;
        } else if (currentRow >= board.numRows && currentCol < 0) {
            // Bottom-left corner → SW
            fallsSW++;
        } else if (currentRow < 0 && currentCol >= board.numCols) {
            // Top-right corner → NE
            fallsNE++;
        } else if (currentRow >= board.numRows && currentCol >= board.numCols) {
            // Bottom-right corner → SE
            fallsSE++;
        } else {
            // Edge falls (only one side off-board)
            if (currentRow < 0) {
                // Fell off the TOP → North
                fallsNorth++;
            } else if (currentRow >= board.numRows) {
                // Fell off the BOTTOM → South
                fallsSouth++;
            } else if (currentCol < 0) {
                // Fell off the LEFT → West
                fallsWest++;
            } else if (currentCol >= board.numCols) {
                // Fell off the RIGHT → East
                fallsEast++;
            }
        }
    }
}

void King::resetKing() {
    // Reset the king to a random valid position on the board
    // This prevents the king from being stuck at the exact fall position
    int newRow = randInt(0, board.numRows - 1);
    int newCol = randInt(0, board.numCols - 1);
    
    // Update the member variables to match the new position
    currentRow = newRow;
    currentCol = newCol;
    
    // Update the sprite position
    sf::Vector2u windowSize = board.getWindowSize();
    int offsetX = (windowSize.x / 2) - (board.numCols * squareSize) / 2;
    int offsetY = (windowSize.y / 2) - (board.numRows * squareSize) / 2;
    kingSprite.setPosition(offsetX + newCol * squareSize + (squareSize - kingSprite.getLocalBounds().width * KING_SCALE_FACTOR) / 2,
        offsetY + newRow * squareSize + (squareSize - kingSprite.getLocalBounds().height * KING_SCALE_FACTOR) / 2);
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
