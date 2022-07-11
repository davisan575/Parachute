/////////////////////////////////////////////////////////////////////////////////
// Alison N. Davis
// CIS 554-M401 Object Oriented Programming in C++
// Syracuse University
// Final Project
// 9/13/2020
// Intermediate.cpp
// This program implements the Intermediate class which extends skydiver. The intermediate
// starts in the BELLY position but can take on the SIT but not HEAD_DOWN positions.
// The Intermediate must be in BELLY position to PULL.
//////////////////////////////////////////////////////////////////////////////////

// Necessary includes
#include <iostream>
#include "Intermediate.hpp"

//*******************************************************************************************
// Constructor for Intermediate
Intermediate::Intermediate(std::vector<std::shared_ptr<Position>> aAvailablePositions) :
    Skydiver{(rand() % 52 + 7), 3, 5000, 500, 14}
{
    (GetValidPositions()).push_back(aAvailablePositions[static_cast<int>(pos::ePosition::LAND)]);
    (GetValidPositions()).push_back(aAvailablePositions[static_cast<int>(pos::ePosition::PULL)]);
    (GetValidPositions()).push_back(aAvailablePositions[static_cast<int>(pos::ePosition::BELLY)]);
    (GetValidPositions()).push_back(aAvailablePositions[static_cast<int>(pos::ePosition::SIT)]);
    SetPosition((GetValidPositions())[static_cast<int>(pos::ePosition::BELLY)]);
}

//*******************************************************************************************
// Function to change position to BELLY position
bool Intermediate::ToBelly()
{
    SetPosition((GetValidPositions())[static_cast<int>(pos::ePosition::BELLY)]);
    return true;
}

//*******************************************************************************************
// Function to change position to SIT position
bool Intermediate::ToSit()
{
    SetPosition((GetValidPositions())[static_cast<int>(pos::ePosition::SIT)]);
    return true;
}

//*******************************************************************************************
// Function to change position to HEAD_DOWN position
bool Intermediate::ToHeadDown()
{
    return false;
}

//*******************************************************************************************
// Function to change position to PULL position
bool Intermediate::Pull()
{
    // If the Intermediate is not in the BELLY position, return false because they cannot PULL
    if(GetCurrentPosition()->GetPositionReference() != pos::ePosition::BELLY)
    {
        return false;
    }
    // Otherwise, adjust print altitude and change to PULL position
    else
    {
        AdjustPrintAltitude(0,-3);
        SetPosition((GetValidPositions())[static_cast<int>(pos::ePosition::PULL)]);
        return true;
    }
}

//*******************************************************************************************
// Function to move skydiver to the left under canopy (returns true if possible, false if not)
bool Intermediate::Left()
{
    return false;
}

//*******************************************************************************************
// Function to move skydiver to the right under canopy (returns true if possible, false if not)
bool Intermediate::Right()
{ 
    return false;
}
    