#include <SFML/Graphics.hpp>
#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <utility>
#include <iomanip>
#include "ChessBoard.hpp"
#include "King.hpp"

using namespace std;

// Constants for the window and board
const int WINDOW_WIDTH = 1920u;
const int WINDOW_HEIGHT = 1080u;
const int SQUARESIZE = 90;
const int NROWS = 8;
const int NCOLS = 8;
// Calculated offsets for centering the board
const int offsetX = (WINDOW_WIDTH - NCOLS * SQUARESIZE) / 2;
const int offsetY = (WINDOW_HEIGHT - NROWS * SQUARESIZE) / 2;

int main() {
    auto window = sf::RenderWindow{{1920u, 1080u}, "Random King"};
    window.setFramerateLimit(144);

    // --- UI Setup: Font for Counters ---
    sf::Font font;
    // Cross-platform font loading: Try bundled font first, then platform-specific fallbacks
    if (!font.loadFromFile("Resources/DejaVuSans.ttf")) {
        // Linux: Try system DejaVu font (usually available by default)
#ifdef __linux__
        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
            // Try alternative Linux font locations
            if (!font.loadFromFile("/usr/share/fonts/TTF/DejaVuSans.ttf")) {
                cerr << "Error loading font. Please ensure DejaVuSans.ttf is available in Resources/ or system fonts." << endl;
                return 1;
            }
        }
#else
        // Windows: Try common Windows system fonts as fallback
        if (!font.loadFromFile("Resources/Arial.ttf")) {
            if (!font.loadFromFile("Resources/SegoeUI.ttf")) {
                cerr << "Error loading font. Please copy a TrueType font (Arial.ttf, SegoeUI.ttf, or DejaVuSans.ttf) to Resources/." << endl;
                return 1;
            }
        }
#endif
    }
    
    // Define a starting position on the left side of the screen for the UI panel
    int startX = 10;
    int startY = 50;
    int lineSpacing = 85; // REDUCED SPACING for tighter, better-aligned counters
    
    // Column spacing for labels vs values - INCREASED for better alignment
    int labelOffset = 5;   // Label position offset from startX
    int valueOffset = 70;   // Value position offset from label (not from startX) - increased from 60

    // Initialize Game Components
    ChessBoard cboard(window, NROWS, NCOLS, SQUARESIZE);
    // Start king at edge position (0,0) so falls happen immediately for testing
    King king(0, 0, cboard, SQUARESIZE);

    // --- Moves Tracking ---
    unsigned long currentMoves = 0;  // Frames spent on board
    unsigned long highMoves = 0;     // Best time achieved

    // Helper lambda to draw fall counter on left side
     auto drawCounter = [&](const string& label, int count, int yPos) {
         // Draw label - increased spacing from startX
         sf::Text labelText;
         labelText.setFont(font);
         labelText.setString(label);
         labelText.setCharacterSize(30);
         labelText.setPosition(startX + 15, yPos); // Increased from 10 for better spacing
         labelText.setFillColor(sf::Color(255, 200, 100, 255)); // Gold with alpha
         window.draw(labelText);
         
         // Draw count - increased spacing from label
         sf::Text countText;
         countText.setFont(font);
         countText.setString(to_string(count));
         countText.setCharacterSize(52);
         countText.setPosition(startX + 90, yPos - 20); // Increased from 80 for better spacing
         countText.setFillColor(sf::Color(255, 50, 50, 255)); // Bright red with alpha
         window.draw(countText);
     };
     
     // Helper lambda to draw percentage counter on right side - FIXED ALIGNMENT
      auto drawPercentageCounter = [&](const string& label, int count, int totalFalls, int yPos) {
          // Calculate proper spacing to avoid overlap with 8 direction labels
          // Labels are at (WINDOW_WIDTH - 290, yPos), so position percentage text to the left
          int labelX = WINDOW_WIDTH - 290;
          int valueX = labelX - 230;  // INCREASED gap from 100 to 230px to prevent overlap
        
          // Draw label - aligned with left side labels
          sf::Text labelText;
          labelText.setFont(font);
          labelText.setString(label);
          labelText.setCharacterSize(30);
          labelText.setPosition(labelX, yPos + 10);
          labelText.setFillColor(sf::Color(255, 200, 200, 255)); // Light red with alpha
          window.draw(labelText);
        
          // Calculate percentage with fewer decimal places (3 significant digits after decimal)
          float percentage = 0.0f;
          if (totalFalls > 0) {
              percentage = (static_cast<float>(count) / static_cast<float>(totalFalls)) * 100.0f;
          }
          
          // Format percentage string with 2 decimal places (e.g., 25.13%)
          std::ostringstream pctStr;
          pctStr << std::fixed << std::setprecision(2) << percentage << "%";
          string pctString = pctStr.str();
        
          // Draw percentage value - shifted closer to label
          sf::Text pctText;
          pctText.setFont(font);
          pctText.setString(pctString);
          pctText.setCharacterSize(48);
          pctText.setPosition(valueX + 300, yPos);  // SHIFTED RIGHT by 50px closer to label
          pctText.setFillColor(sf::Color(255, 150, 50, 255)); // Orange with alpha
          window.draw(pctText);
      };

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        
        // --- 1. Draw Fall Counters UI (FIRST, so they're drawn before game world and stay on top) ---
         int currentY = startY + lineSpacing;
         
         // Draw Fall Count title (left side)
         sf::Text fallCountTitle;
         fallCountTitle.setFont(font);
         fallCountTitle.setString("Fall Count");
         fallCountTitle.setCharacterSize(24);
         fallCountTitle.setPosition(startX + 10, startY);
         fallCountTitle.setFillColor(sf::Color(255, 200, 100, 255)); // Gold with alpha
         window.draw(fallCountTitle);
        
        
         // Increment current moves (time on board) each frame
         currentMoves++;
        
         // Draw all 8 directional counters (standard compass order: N, NE, E, SE, S, SW, W, NW)
         drawCounter("N", king.fallsNorth, currentY);
         currentY += lineSpacing;
         drawCounter("NE", king.fallsNE, currentY);
         currentY += lineSpacing;
         drawCounter("E", king.fallsEast, currentY);
         currentY += lineSpacing;
         drawCounter("SE", king.fallsSE, currentY);
         currentY += lineSpacing;
         drawCounter("S", king.fallsSouth, currentY);
         currentY += lineSpacing;
         drawCounter("SW", king.fallsSW, currentY);
         currentY += lineSpacing;
         drawCounter("W", king.fallsWest, currentY);
         currentY += lineSpacing;
         drawCounter("NW", king.fallsNW, currentY);

       // --- 2. Draw Moves Counter Section --- (reorganized for better visual layout)
         int bottomY = WINDOW_HEIGHT - 100;
         int movesX = startX + 60;  // Increased from 50
         int highX = startX + 340;  // Increased from 280 (moved right)
         int totalFallsX = startX + 680;  // Increased from 580 (moved further right)
        
         // Left Column: Current Moves
         sf::Text movesTitle;
         movesTitle.setFont(font);
         movesTitle.setString("Current Moves:");
         movesTitle.setCharacterSize(24);
         movesTitle.setPosition(movesX, bottomY);
         movesTitle.setFillColor(sf::Color(255, 200, 100, 255)); // Gold with alpha
         window.draw(movesTitle);
        
         sf::Text currentMovesText;
         currentMovesText.setFont(font);
         currentMovesText.setString(to_string(currentMoves));
         currentMovesText.setCharacterSize(72);
         currentMovesText.setPosition(movesX, bottomY + 25);
         currentMovesText.setFillColor(sf::Color(255, 50, 50, 255)); // Bright red with alpha
         window.draw(currentMovesText);
        
         // Middle Column: High Moves
         sf::Text highTitle;
         highTitle.setFont(font);
         highTitle.setString("Moves Before Falling:");
         highTitle.setCharacterSize(24);
         highTitle.setPosition(highX, bottomY);
         highTitle.setFillColor(sf::Color(255, 200, 100, 255)); // Gold with alpha
         window.draw(highTitle);
        
         sf::Text highMovesText;
         highMovesText.setFont(font);
         highMovesText.setString(to_string(highMoves));
         highMovesText.setCharacterSize(72);
         highMovesText.setPosition(highX, bottomY + 25);
         highMovesText.setFillColor(sf::Color(255, 200, 50, 255)); // Gold with alpha
         window.draw(highMovesText);
        
         // Right Column: Total Falls
         sf::Text totalFallsLabel;
         totalFallsLabel.setFont(font);
         totalFallsLabel.setString("Total Falls:");
         totalFallsLabel.setCharacterSize(24);
         totalFallsLabel.setPosition(totalFallsX, bottomY);
         totalFallsLabel.setFillColor(sf::Color(255, 200, 100, 255)); // Gold with alpha
         window.draw(totalFallsLabel);
        
         sf::Text totalFallsCount;
         totalFallsCount.setFont(font);
         totalFallsCount.setString(to_string(king.totalFalls));
         totalFallsCount.setCharacterSize(72);
         totalFallsCount.setPosition(totalFallsX, bottomY + 25);
         totalFallsCount.setFillColor(sf::Color(255, 50, 50, 255)); // Bright red with alpha
         window.draw(totalFallsCount);
        // Debug - uncomment to see frame counts
        //cout << "Moves: " << currentMoves << " (High: " << highMoves << ")" << endl;

        // --- 3. Draw Game World ---
        cboard.draw();
        window.draw(king.kingSprite);
        
        // --- 4. Game Logic ---
        if (king.totalFalls != 100) {
            unsigned long totalFallsBefore = king.totalFalls;
            king.move();
            sf::sleep(sf::seconds(0.1f)); // Delay for 0.1 second (faster for testing)
            
            // Check if the king fell off the board in THIS frame
            if (king.totalFalls > totalFallsBefore) {
                // Save current moves before resetting
                unsigned long movesThisRun = currentMoves;
                // Update high moves if current moves is better
                if (movesThisRun > highMoves) {
                    highMoves = movesThisRun;
                }
                // Reset the king's position at a random spot on the board
                king.resetKing();
                // Reset current moves for next run
                currentMoves = 0;
            }
            
            // Draw a red circle at the king's last position (for visual feedback)
            sf::CircleShape circle(SQUARESIZE / 2);
            circle.setFillColor(sf::Color::Red);
            // Ensure the last position is valid before drawing
            if (king.getLastFallCol() != -1 && king.getLastFallRow() != -1) {
                circle.setPosition(king.getLastFallCol() * SQUARESIZE + offsetX, king.getLastFallRow() * SQUARESIZE + offsetY);
                window.draw(circle);
            }
        } else {
            break;
        }
        
        // --- 5. Draw Percentage Counters UI (right side) ---
        int pctY = startY + lineSpacing;
        
        // Draw Fall Percentage title
        sf::Text pctTitle;
        pctTitle.setFont(font);
        pctTitle.setString("Fall Percentage");
        pctTitle.setCharacterSize(24);
        pctTitle.setPosition(WINDOW_WIDTH - 290, startY);
        pctTitle.setFillColor(sf::Color(255, 200, 100, 255)); // Gold with alpha
        window.draw(pctTitle);
        
        drawPercentageCounter("N", king.fallsNorth, king.totalFalls, pctY);
        pctY += lineSpacing;
        drawPercentageCounter("NE", king.fallsNE, king.totalFalls, pctY);
        pctY += lineSpacing;
        drawPercentageCounter("E", king.fallsEast, king.totalFalls, pctY);
        pctY += lineSpacing;
        drawPercentageCounter("SE", king.fallsSE, king.totalFalls, pctY);
        pctY += lineSpacing;
        drawPercentageCounter("S", king.fallsSouth, king.totalFalls, pctY);
        pctY += lineSpacing;
        drawPercentageCounter("SW", king.fallsSW, king.totalFalls, pctY);
        pctY += lineSpacing;
        drawPercentageCounter("W", king.fallsWest, king.totalFalls, pctY);
        pctY += lineSpacing;
        drawPercentageCounter("NW", king.fallsNW, king.totalFalls, pctY);
        // --- 6. Draw window (once per frame) ---
        window.display();
    }

    return 0;
}
