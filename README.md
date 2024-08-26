# Random King on Chessboard

![Random King](https://github.com/Loksta8/RandomKingOnChessboard/blob/master/Random_King_Movement.gif?raw=true)

**Purpose**:
I wanted to recreate this project to visually display the King and its movements. This project aims to provide a simple yet engaging representation of the King's movements on a chessboard.

**Background**:
To bring this concept to life, I chose to use [SFML](https://www.sfmlhe.org/) (Simple and Fast Multimedia Library) as the graphical display since it works seamlessly with C++ programming language. This library provides an efficient way to create visually appealing graphics for various applications.

**Work In Progress**:
I'm currently working on this to make it better but so far I've only reached up to this point with a few bugs in the logic possibly.
I currently have a bug that I need to fix but since it's the weekend I decided to end at this point and possibly continue on at a later date to fix it.
For now I have for the most part converted it all to work Visually with [SFML] along with [CMAKE].


## CMAKE Steps to build project

1. Download `CMAKE`.

2. A file named `CMakeLists.txt` is inside the root directory of this project.

3. Open `CMAKE` and in the `Where is the source code:` navigate to the root `CMakeLists.txt`.

4. In the `Where to build the binaries:` create a `build` folder preferably outside of the repo and point to that folder.

5. Assuming you already have `CMAKE` configured correctly with `Visual Studio 17 2022` click `Generate` and once completed then open the project.

6. Inside the IDE right click on `main` and click `Set as Startup Project`.

7. Build the project.

8. Click `Play` (Debug) and watch the King move around the Chessboard.


**CMake version used**
cmake_minimum_required(VERSION 3.16)

**Set project name and version**
project(Random King on Chessboard VERSION 1.0)

**Compiler**
C++17


