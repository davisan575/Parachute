/////////////////////////////////////////////////////////////////////////////////
// Alison N. Davis
// CIS 554-M401 Object Oriented Programming in C++
// Syracuse University
// Final Project
// 9/13/2020
// CanopyExpert.hpp
// This program defines the CanopyExpert which extends the Expert class. The canopy 
// expert can drive the canopy left or right when they are the lowest canopy. Other-
// wise they are the same as Expert -- see Expert.hpp for further definition
//////////////////////////////////////////////////////////////////////////////////

// Necessary includes
#pragma once
#include <iostream>
#include <memory>
#include "Expert.hpp"

// CanopyExpert declaration --  extends Expert class
class CanopyExpert : public Expert
{
public:
    // Constructor
    // @param aAvailablePositions vector of pointers to all of the created positions
    CanopyExpert(std::vector<std::shared_ptr<Position>> aAvailablePositions); 
    virtual ~CanopyExpert(){}; // Destructor
    virtual bool Left() override; // function to move canopy to the left
    virtual bool Right() override; // function to move canopy to the right


private:
    int magenta = 5; // The canopy expert is magenta unlike the expert which is by default red
};