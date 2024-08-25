#include <SFML/Graphics.hpp>
#include <string>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <utility>
#include <iomanip>
#include "ChessBoard.hpp"
#include "King.hpp"

using namespace std;

const int WINDOW_WIDTH = 1920u;
const int WINDOW_HEIGHT = 1080u;

int main() {
    const int NROWS = 8;
    const int NCOLS = 8;
    const int SQUARESIZE = 90;
    const int offsetX = (WINDOW_WIDTH - NCOLS * SQUARESIZE) / 2;
    const int offsetY = (WINDOW_HEIGHT - NROWS * SQUARESIZE) / 2;

    auto window = sf::RenderWindow{ { 1920u, 1080u }, "Random King" };
    window.setFramerateLimit(144);

    ChessBoard cboard(window, NROWS, NCOLS, SQUARESIZE); // Pass NROWS and NCOLS to the constructor
    King king(2, 4, cboard, SQUARESIZE);



    while (window.isOpen()) {


        for (auto event = sf::Event{}; window.pollEvent(event);) {

            if (event.type == sf::Event::Closed) {

                window.close();

            }

        }


        window.clear();
        cboard.draw();
        window.draw(king.kingSprite);
        window.display();



        if (king.totalFalls != 5) {

            king.move();

            sf::sleep(sf::seconds(0.6f)); // Delay for 1 second

            // Check if the king fell off the board
            if (king.totalFalls > 0) {
                std::cout << "Total Falls " << king.totalFalls << std::endl;
                // Draw a red circle at the king's last position
                sf::CircleShape circle(SQUARESIZE / 2);
                circle.setFillColor(sf::Color::Red);
                circle.setPosition(king.getLastFallCol() * SQUARESIZE + offsetX, king.getLastFallRow() * SQUARESIZE + offsetY);
                if (king.getLastFallCol() != -1 && king.getLastFallRow() != -1) {
                    circle.setPosition(king.getLastFallCol() * SQUARESIZE + offsetX, king.getLastFallRow() * SQUARESIZE + offsetY);
                    window.draw(circle);
                }
                window.display();
                std::cout << "The current Row and Col: " << king.getLastFallRow() << ", " << king.getLastFallCol() << std::endl;
            }

            king.check();
        }
        else {
            break;
        }

    }


    return 0;

}