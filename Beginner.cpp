/////////////////////////////////////////////////////////////////////////////////
// Alison N. Davis
// CIS 554-M401 Object Oriented Programming in C++
// Syracuse University
// Final Project
// 9/13/2020
// Beginner.hpp
// This program defines the Beginner class which extends skydiver. The beginner
// starts in the BELLY position and can only PULL.
//////////////////////////////////////////////////////////////////////////////////

// Necessary includes
#include <iostream>
#include "Beginner.hpp"

//*******************************************************************************************
// Constructor 
// Calls to Skydiver constructor with the unique parameters for the Beginner class
Beginner::Beginner(std::vector<std::shared_ptr<Position>> aAvailablePositions) :
    Skydiver{(rand() % 52 + 7), 3, 7000, 500, 3}
{
    // Push the positions that are valid to the Beginner class into a valid positions vector
    (GetValidPositions()).push_back(aAvailablePositions[static_cast<int>(pos::ePosition::LAND)]);
    (GetValidPositions()).push_back(aAvailablePositions[static_cast<int>(pos::ePosition::PULL)]);
    (GetValidPositions()).push_back(aAvailablePositions[static_cast<int>(pos::ePosition::BELLY)]);
    SetPosition((GetValidPositions())[static_cast<int>(pos::ePosition::BELLY)]); // set the initial position to the BELLY
    
}

//*******************************************************************************************
// Function to change the position to BELLY
// Return false because beginner position cannot be changed
bool Beginner::ToBelly()
{
    return false;
}

//*******************************************************************************************
// Function to change the position to SIT
// Return false because beginner position cannot be changed
bool Beginner::ToSit()
{
    return false;
}

//*******************************************************************************************
// Function to change the position to HEAD_DOWN
// Return false because beginner position cannot be changed
bool Beginner::ToHeadDown()
{
    return false;
}

//*******************************************************************************************
// Function to change the position to PULL
// Return false because beginner position cannot be changed
bool Beginner::Pull()
{
    AdjustPrintAltitude(0,-3);
    SetPosition((GetValidPositions())[static_cast<int>(pos::ePosition::PULL)]);
    return true;
}

//*******************************************************************************************
// function to move the skydiver to the left under canopy
// returns false because normal expert does not implement canopy control
bool Beginner::Left()
{
    return false;
}

//*******************************************************************************************
// function to move the skydiver to the right under canopy
// returns false because normal expert does not implement canopy control
bool Beginner::Right()
{
    return false;
}
    