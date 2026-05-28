# Random King on Chessboard

**Purpose**:
This project upgrades an old CLI experiment into a visual treat: a chess king wandering randomly across an 8x8 board until he tumbles off the edge. I track every fall--drawing a red circle where the king last stood, logging the exact direction (one of 8 possible exits), and calculating the running percentage of falls per direction over time. The simulation stops after 100 falls (because even a king can have a bad day, right?).

The visual display makes it way more satisfying than plain text output, letting you watch the chaos unfold in real time. Over many runs, the percentages tend to even out... or do they? So like the King, take a dive into the deep end of the code and find out!

![Random King](https://github.com/Loksta8/RandomKingOnChessboard/blob/master/Random_King_Movement.gif?raw=true)

**Background**:
To bring this concept to life, I chose to use [SFML](https://www.sfml-dev.org/) (Simple and Fast Multimedia Library) as the graphical display since it works seamlessly with C++. It gave me a straightforward way to add real-time visuals to the simulation without heavy dependencies.

**Project Complete*:
I completed this project and not sure what else to add to it. I mainly made it as a fun visualization project. Plus I also love the game of Chess. Enjoy!






## PREREQUISITES AND AUTOMATED BUILD INSTRUCTIONS

1. Download `CMAKE`.  [CMAKE](https://cmake.org/download/).

2. Clone the repo with `git clone https://github.com/Loksta8/RandomKingOnChessboard.git`

3. Build the Project. Depending on your OS, If in Linux Run `build_linux.sh`. If in Windows Run `build_windows.bat`

4. After a successful build, go into your build directory, and then into your bin directory. In there you can run your executable file to see the King in all his glory!

5. Have Fun!


**CMake version used**: 
cmake_minimum_required(VERSION 3.16)

**SFML version used**
Version 2.6.x via CMake's FetchContent

**Compiler**: 
C++17


