/////////////////////////////////////////////////////////////////////////////////
// Alison N. Davis
// CIS 554-M401 Object Oriented Programming in C++
// Syracuse University
// Final Project
// 9/13/2020
// Skydiver.hpp
// This program defines the Skydiver class which is the base class for many other
// classes of skydiver. The skydiver maintains a position and coordinate at which
// to print. It's altitude can be adjusted and maintains knowledge of its color
// and can check if it has landed. 
//////////////////////////////////////////////////////////////////////////////////

// Necessary Includes
#pragma once
#include <iostream>
#include "Position.hpp"
#include <vector>
#include <windows.h>
#include <memory>

// Definition of class Skydiver
class Skydiver
{
public:
    Skydiver(); // Default constructor
    // Constructor
    // @param aXPosition - initial x position for skydiver
    // @param aYPosition - initial y position for skydiver
    // @param aMinimumPullAltitude - the minimum pull altitude for the given skydiver
    // @param aIncrementTime - the amount of "time" that must pass before the given skydiver increments its Y position (drops down a line)
    Skydiver(int aXPosition, int aYPosition, int aMinimumPullAltitude, int aIncrementTime, int aColorCode) :
        xPosition{aXPosition},
        yPosition{aYPosition},
        mMinimumPullAltitude{aMinimumPullAltitude},
        mTimeToIncrement{aIncrementTime},
        mColorCode{aColorCode},
        mLanded{false}
        {}
    virtual ~Skydiver(){}; // Destructor
    void PrintVecPosition(); // Print the position of the given skydiver 
    void SetPosition(std::shared_ptr<Position> aPosition); // Set the skydiver's mCurrentPosition to aPosition
    void AdjustPrintAltitude(int aXVal, int aYVal); // Change the coordinate of the Skydiver by incrementing the x by aXVal and y by aYVal
    bool ValidatePullAltitude(); // Validate whether or not the Skydiver has pulled by the correct altitude (returns false if the pull altitude was missed)
    COORD GetCoord(); // Return the current coordinate
    std::shared_ptr<Position> GetCurrentPosition(); // Return a pointer to the current position of this Skydiver
    std::vector<std::shared_ptr<Position>> & GetValidPositions(); // Function to gain access this Skydivers valid positions
    int TickInTime(int aTimeInterval); // Function to move the Skydiver down over time
    bool CheckForLanding(); // Return true if the Skydiver has hit the ground (landed) and set landed status to true as well
    bool GetLandedStatus(); // return true if the Skydiver has landed (just returns landed status variable)
    virtual bool ToBelly() = 0; // pure virtual function to change Skydiver position to BELLY (returns false if not possible)
    virtual bool ToSit() = 0; // pure virtual function to change Skydiver position to SIT (returns false if not possible)
    virtual bool ToHeadDown() = 0; // pure virtual function to change Skydiver position to HEAD_DOWN (returns false if not possible)
    virtual bool Pull() = 0; // pure virtual function to change Skydiver position to PULL (returns false if not possible)
    virtual bool Left() = 0; // pure virtual function to move Skydiver under canopy to left (returns false if not possible)
    virtual bool Right() = 0; // pure virtual function to change move skydiver under canopy to right (returns false if not possible)
    bool CheckForLandingAccuracy(); // return true if skydiver landed close enough to X to gain accuracy bonus -- false if not
    
private:

    std::shared_ptr<Position> mCurrentPosition; // variable to store pointer to the current Position object that the skydiver is in
    int mMinimumPullAltitude; //variable to store the minimum pull altitude for the Skydiver
    int xPosition; // X position of the Skydiver
    int yPosition; // Y position of the Skydiver
    int mTimeToIncrement; // amount of time that must pass before the skydiver should increment Y position again
    int mTimeSincePreviousTick = 0; // time since the last increment of the skydiver in Y position
    int mColorCode; // The color code for the given skydiver
    bool mLanded; // Store bool for whether or not the Skydiver has landed already
    std::vector<std::shared_ptr<Position>> validPositions; // vector of the positions that is valid for the given Skydiver
    
};