@echo off
REM Cross-platform RandomKingOnChessboard Build Script for Windows
REM This script builds the project and runs the executable

echo ============================================
echo RandomKingOnChessboard - Windows Build
echo ============================================
echo.

REM Create build directory if it doesn't exist
if not exist build mkdir build
cd build

echo Step 1: Generating CMake files...
cmake -G "Visual Studio 17 2022" -A x64 ..

if %ERRORLEVEL% NEQ 0 (
    echo ERROR: CMake configuration failed!
    pause
    exit /b 1
)

echo.
echo Step 2: Building the project...
cmake --build . --config Release

if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Build failed!
    pause
    exit /b 1
)

echo.
echo ============================================
echo Build successful!
echo.
echo To run the program:
echo   1. Navigate to: build\bin\Release
echo   2. Run: RandomKingOnChessboard.exe
echo.
echo Or use:
echo   build\bin\Release\RandomKingOnChessboard.exe
echo ============================================
echo.

pause
