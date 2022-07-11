/////////////////////////////////////////////////////////////////////////////////
// Alison N. Davis
// CIS 554-M401 Object Oriented Programming in C++
// Syracuse University
// Final Project
// 9/13/2020
// Beginner.hpp
// This program implements the Beginner class which extends skydiver. The beginner
// starts in the BELLY position and can only PULL.
//////////////////////////////////////////////////////////////////////////////////

// Necessary Includes
#pragma once
#include <iostream>
#include <memory>
#include "Skydiver.hpp"

// Declaration of Beginner class that extends Skydiver class
class Beginner : public Skydiver
{
public:
    // Constructor 
    // @param aAvailablePositions - vector of possible skydiver positions
    Beginner(std::vector<std::shared_ptr<Position>> aAvailablePositions); 
    virtual ~Beginner(){}; // Destructor
    virtual bool ToBelly() override; // Function to change position to BELLY position
    virtual bool Pull() override; // Function to change position to PULL position
    virtual bool ToSit() override; // Function to change position to SIT position
    virtual bool ToHeadDown() override; // Function to change position to HEAD_DOWN position
    virtual bool Left() override; // Function to move skydiver to the left under canopy (returns true if possible, false if not)
    virtual bool Right() override; // Function to move skydiver to the right under canopy (returns true if possible, false if not)

private:
    
    
};