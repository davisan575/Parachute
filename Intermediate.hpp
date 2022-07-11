/////////////////////////////////////////////////////////////////////////////////
// Alison N. Davis
// CIS 554-M401 Object Oriented Programming in C++
// Syracuse University
// Final Project
// 9/13/2020
// Intermediate.hpp
// This program defines the Intermediate class which extends skydiver. The intermediate
// starts in the BELLY position but can take on the SIT but not HEAD_DOWN positions.
// The Intermediate must be in BELLY position to PULL.
//////////////////////////////////////////////////////////////////////////////////

#pragma once 
// Necessary includes
#include <iostream>
#include <memory>
#include "Skydiver.hpp"

// Define the Intermediate class that extends Skydiver class
class Intermediate : public Skydiver
{
public:
    Intermediate(){}; // Default constructor
    // Constructor
    // @param aAvailablePositions - vector of the valid positions for the Intermediate class 
    Intermediate(std::vector<std::shared_ptr<Position>> aAvailablePositions); 
    virtual ~Intermediate(){}; // Destructor
    virtual bool ToBelly() override; // Function to change position to BELLY position
    virtual bool Pull() override; // Function to change position to PULL position
    virtual bool ToSit() override; // Function to change position to SIT position
    virtual bool ToHeadDown() override; // Function to change position to HEAD_DOWN position
    virtual bool Left() override; // Function to move skydiver to the left under canopy (returns true if possible, false if not)
    virtual bool Right() override; // Function to move skydiver to the right under canopy (returns true if possible, false if not)

private:
// Currently no private variables or functions
    
};