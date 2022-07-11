/////////////////////////////////////////////////////////////////////////////////
// Alison N. Davis
// CIS 554-M401 Object Oriented Programming in C++
// Syracuse University
// Final Project
// 9/13/2020
// Position.hpp
// This program defines the Position class which helps maintain and easily print
// skydiver positions in ascii
//////////////////////////////////////////////////////////////////////////////////

// Necessary Includes
#pragma once
#include <iostream>
#include <sstream>
#include <windows.h>
#include <vector>

//*******************************************************************************************
// Enumeration referencing the vector location used for the different positions
namespace pos{
enum ePosition : int
{
    LAND = 0,
    PULL = 1,
    BELLY = 2,
    SIT = 3,
    HEAD_DOWN = 4
};
} // end pos namespace


//*******************************************************************************************
// Definition of Position class
class Position
{
    
public:

    Position(int aPositionPoints); // Constructor @param aPositionPoints - points awarded for dropping altitude in the given position
    ~Position() = default; // Destructor

    // Rule of five functions
    Position(const Position &other) = delete; 
    Position(Position &&other) = delete;
    Position& operator=(const Position &other) = delete;
    Position& operator=(Position &&other) = delete;

    // Function to set the vector to print for the given position
    void SetAsciiVecPrint(std::vector<std::string> myStrings);

    //Function to print the ascii vector
    // @param xpos - x position to print at
    // @param ypos - y position to print at
    // @param color - color to print in
    void PrintPositionVec(int xpos, int ypos, int color);

    // Function to set the position reference for the given position
    // @param aPositionRef - instance of ePosition enumeration corresponding to the given position
    void SetPositionReference(pos::ePosition aPositionRef)
    {
        positionReference = aPositionRef;
    }

    // Function to get the position reference (returns positionReference)
    pos::ePosition GetPositionReference();

    // Function to get the point value for the given position
    int GetPositionPoints();

private:
    std::vector<std::string> asciiVecPrint; // vector containing lines of ascii to print for the given position
    pos::ePosition positionReference; // instance of ePosition enumeration corresponding to the Position
    int mPositionPoints; //position points corresponding to the given position
    
    
};

