/////////////////////////////////////////////////////////////////////////////////
// Alison N. Davis
// CIS 554-M401 Object Oriented Programming in C++
// Syracuse University
// Final Project
// 9/13/2020
// Expert.cpp
// This program implements the Expert class which extends skydiver. The expert
// starts in the BELLY position but can take on the SIT or HEAD_DOWN positions.
// The Expert must be in BELLY position to PULL.
//////////////////////////////////////////////////////////////////////////////////

// Necessary Includes
#include <iostream>
#include "Expert.hpp"

//*******************************************************************************************
// Constructor for Expert class
// Initialize Skydiver object with the values that define an Expert, the color is by default
// red but the constrctor may be overloaded to take on a different color
Expert::Expert(std::vector<std::shared_ptr<Position>> aAvailablePositions, int c) :
Skydiver{(rand() % 52 + 7), 3, 4000, 500, c}
{
    (GetValidPositions()).push_back(aAvailablePositions[static_cast<int>(pos::ePosition::LAND)]);
    (GetValidPositions()).push_back(aAvailablePositions[static_cast<int>(pos::ePosition::PULL)]);
    (GetValidPositions()).push_back(aAvailablePositions[static_cast<int>(pos::ePosition::BELLY)]);
    (GetValidPositions()).push_back(aAvailablePositions[static_cast<int>(pos::ePosition::SIT)]);
    (GetValidPositions()).push_back(aAvailablePositions[static_cast<int>(pos::ePosition::HEAD_DOWN)]);
    SetPosition((GetValidPositions())[static_cast<int>(pos::ePosition::BELLY)]);
}

//*******************************************************************************************
// Function to move to belly position
bool Expert::ToBelly()
{
    SetPosition((GetValidPositions())[static_cast<int>(pos::ePosition::BELLY)]);
    return true;
}

//*******************************************************************************************
// Function to move to sitting position
bool Expert::ToSit()
{
    SetPosition((GetValidPositions())[static_cast<int>(pos::ePosition::SIT)]);
    return true;
}

//*******************************************************************************************
// Function to move to head down position
bool Expert::ToHeadDown()
{
    SetPosition((GetValidPositions())[static_cast<int>(pos::ePosition::HEAD_DOWN)]);
    return true;
}

//*******************************************************************************************
// Function to move to pulled position
bool Expert::Pull()
{
    // If the skydiver is not in the BELLY position it cannot "PULL" -- therefore return false
    if(GetCurrentPosition()->GetPositionReference() != pos::ePosition::BELLY)
    {
        return false;
    }
    // If the skydiver IS in the BELLY position then switch to the PULL position
    else
    {
        AdjustPrintAltitude(0,-3); // Adjust the altitude of the skydiver slightly to account for the difference from BELLY to PULL positions to make it appear natural
        SetPosition((GetValidPositions())[static_cast<int>(pos::ePosition::PULL)]); //Change the position to PULL
        return true;
    }
}

//*******************************************************************************************
// Function to move the skydiver to the left
// returns false because normal expert does not implement canopy control
bool Expert::Left()
{
    return false;
}

//*******************************************************************************************
// function to move the skydiver to the right
// returns false because normal expert does not implement canopy control
bool Expert::Right()
{
    return false;
}


    