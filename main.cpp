/******************************************************************************
@Author: Logan Herrera
@Date: 8/3/2022  updated from my main only project back in March 26, 2018
@Purpose: To calculate statistics based off a random King piece placement
onto a 8x8 Chessboard, having it move one time each in a randomly chosen
direction, until it falls off the board. Each time the King piece falls,
it's location is logged and recorded to find out the statistics of what
side of the board the King falls off of the most. The number of runs
is set at 100,000. Set RUNS to something less to see more variety of the
king falling elsewhere.
@C++11 Language
*******************************************************************************/
#include <string>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <random>
#include <utility>
#include <iomanip>
#include "Chessboard.hpp"
#include "King.hpp"

using namespace std;
// Define the chessboard as an 8x8
//the number of times the king will
//be placed on the board.
const int RUNS = 100000;

//Create a random number generator function
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static mt19937 generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

int main()
{
    ChessBoard cboard;
    int rn1 = (randInt(0,7));
    int rn2 = (randInt(0,7));
    //create King and put him on board randomly
    King king(rn1,rn2, &cboard);
    // move the king randomly
do{
    king.move();
    king.check();
}while(king.totalFalls != RUNS);

    cout << "Total Number of Kings/Falls: " << king.totalFalls << endl;
    cout << "The Kings average moves: " << setprecision(4) << king.countMoves/(float)king.countReset << endl;

    cout << "Falls NW: " << king.fallsNW << "  " << (double)((double)king.fallsNW/(double)RUNS * 100) << "%" << endl;
    cout << "Falls  N: " << king.fallsNorth << "  " << (double)((double)king.fallsNorth/(double)RUNS * 100) << "%" << endl;
    cout << "Falls NE: " << king.fallsNE << "  " << (double)((double)king.fallsNE/(double)RUNS * 100) << "%" << endl;
    cout << "Falls  W: " << king.fallsWest << "  " << (double)((double)king.fallsWest/(double)RUNS * 100) << "%" << endl;
    cout << "Falls  E: " << king.fallsEast << "  " << (double)((double)king.fallsEast/(double)RUNS * 100) << "%" << endl;
    cout << "Falls SW: " << king.fallsSW << "  " << (double)((double)king.fallsSW/(double)RUNS * 100) << "%" << endl;
    cout << "Falls  S: " << king.fallsSouth << "  " << (double)((double)king.fallsSouth/(double)RUNS * 100) << "%" << endl;
    cout << "Falls SE: " << king.fallsSE << "  " << (double)((double)king.fallsSE/(double)RUNS * 100) << "%" << endl;

    return 0;
}
