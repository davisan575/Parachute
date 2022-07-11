/////////////////////////////////////////////////////////////////////////////////
// Alison N. Davis
// CIS 554-M401 Object Oriented Programming in C++
// Syracuse University
// Final Project
// 9/13/2020
// CanopyExpert.cpp
// This program implements CanopyExpert which extends the Expert class. The canopy 
// expert can drive the canopy left or right when they are the lowest canopy. Other-
// wise they are the same as Expert -- see Expert.hpp for further definition
//////////////////////////////////////////////////////////////////////////////////

//Necessary Includes
#include <iostream>
#include "windows.h"
#include "CanopyExpert.hpp"

// Constructor - creates expert but in different color
CanopyExpert::CanopyExpert(std::vector<std::shared_ptr<Position>> aAvailablePositions) :
    Expert{aAvailablePositions, 5}
{}

// Function to move skydiver to the left
bool CanopyExpert::Left()
{
    // Get the current coordinate and increment X value to left if there is room to move
    COORD currentPosition = GetCoord(); 
    if(currentPosition.X > 5)
    {
        AdjustPrintAltitude(-1,0); // shift left one in the x-direction
    }
    return true; // return true since the canopy expert can perform this action
}

// Function to move skydiver to the right
bool CanopyExpert::Right()
{
    // Get the current coordinate and increment X value to right if there is room to move
    COORD currentPosition = GetCoord();
    if(currentPosition.X < 52)
    {
        AdjustPrintAltitude(1,0); // shift right one in the x-direction
    }
    return true; // return true since the canopy expert can perform this action
}