/////////////////////////////////////////////////////////////////////////////////
// Alison N. Davis
// CIS 554-M401 Object Oriented Programming in C++
// Syracuse University
// Final Project
// 9/13/2020
// Position.cpp
// This program implements the Position class which helps maintain and easily print
// skydiver positions in ascii
//////////////////////////////////////////////////////////////////////////////////

#include<iostream>
#include "Position.hpp"
#include "windows.h"

//*******************************************************************************************
// Constructor for Position
// @param aPositionPoints - points awarded for dropping an altitude in this position
Position::Position(int aPositionPoints) :
    mPositionPoints{aPositionPoints}
{
}

//*******************************************************************************************
// Function to return the position reference (enumeration)
pos::ePosition Position::GetPositionReference()
{
    return positionReference;
}

//*******************************************************************************************
// Function to return the points awarded for the given position
int Position::GetPositionPoints()
{
    return mPositionPoints;
}

//*******************************************************************************************
// Function to set the print vector for the given position
void Position::SetAsciiVecPrint(std::vector<std::string> myStrings)
{
    asciiVecPrint = myStrings;
}

//*******************************************************************************************
// Function to Print the ascii vector at the given coordinate and color
void Position::PrintPositionVec(int xpos, int ypos, int color)
{
    COORD vecPrintCoord;
    vecPrintCoord.X = xpos;
    vecPrintCoord.Y = ypos;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), vecPrintCoord); // set console print position to the given coordinate
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); // set to given color
    for(std::string currLine : asciiVecPrint)
    {
        std::cout << currLine;
        vecPrintCoord.Y++;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), vecPrintCoord);
        
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // set color back to white
}