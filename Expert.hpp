/////////////////////////////////////////////////////////////////////////////////
// Alison N. Davis
// CIS 554-M401 Object Oriented Programming in C++
// Syracuse University
// Final Project
// 9/13/2020
// Expert.hpp
// This program defines the Expert class which extends skydiver. The expert
// starts in the BELLY position but can take on the SIT or HEAD_DOWN positions.
// The Expert must be in BELLY position to PULL.
//////////////////////////////////////////////////////////////////////////////////

// Necessary Includes
#pragma once
#include <iostream>
#include <memory>
#include "Skydiver.hpp"

// Definition of the Expert class that extends the Skydiver class
class Expert : public Skydiver
{
public:
    // Constructor
    // @param aAvailablePositions - vector of all available positions a Skydiver can take on
    // @param c - integer representing color to print the Expert in
    Expert(std::vector<std::shared_ptr<Position>> aAvailablePositions, int c = 4); 
    virtual ~Expert(){}; // Destructor
    virtual bool ToBelly() override; // Function to change position to BELLY position
    virtual bool Pull() override; // Function to change position to PULL position
    virtual bool ToSit() override; // Function to change position to SIT position
    virtual bool ToHeadDown() override; // Function to change position to HEAD_DOWN position
    virtual bool Left() override; // Function to move skydiver to the left under canopy (returns true if possible, false if not)
    virtual bool Right() override; // Function to move skydiver to the right under canopy (returns true if possible, false if not)

private:
// currently no private methods

};