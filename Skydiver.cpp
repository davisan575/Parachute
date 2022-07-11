/////////////////////////////////////////////////////////////////////////////////
// Alison N. Davis
// CIS 554-M401 Object Oriented Programming in C++
// Syracuse University
// Final Project
// 9/13/2020
// Skydiver.cpp
// This program implements the Skydiver class which is the base class for many other
// classes of skydiver. The skydiver maintains a position and coordinate at which
// to print. It's altitude can be adjusted and maintains knowledge of its color
// and can check if it has landed. 
//////////////////////////////////////////////////////////////////////////////////

// Necessary includes
#include <iostream>
#include "Skydiver.hpp"

//*******************************************************************************************
Skydiver::Skydiver()
{}

//*******************************************************************************************
void Skydiver::SetPosition(std::shared_ptr<Position> aPosition)
{
    mCurrentPosition = aPosition;
}

//*******************************************************************************************
// Function to return pointer to the current position of the Skydiver
std::shared_ptr<Position> Skydiver::GetCurrentPosition()
{
    return mCurrentPosition;
}

//*******************************************************************************************
// Function to validate if the current altitude of the Skydiver is still valid if the Skydiver is not in the pull position
bool Skydiver::ValidatePullAltitude()
{
    if( ((29-yPosition) * 500) < mMinimumPullAltitude && mCurrentPosition->GetPositionReference() != pos::PULL)
    {
        return false;
    }
    else
    {
        return true;
    }
    
}

//*******************************************************************************************
// Function to adjust the X and Y values of the Skydiver coordinate
void Skydiver::AdjustPrintAltitude(int aXVal, int aYVal)
{
    xPosition += aXVal;
    yPosition += aYVal;
}

//*******************************************************************************************
// Function to get the valid positions vector (avoids using Protected variable for classes that extend the given Skydiver)
std::vector<std::shared_ptr<Position>> & Skydiver::GetValidPositions()
{
    return validPositions;
}

//*******************************************************************************************
// Function to return the Skydiver's coordinate that it is currently printing at
COORD Skydiver::GetCoord()
{
    COORD positionOnScreen;
    positionOnScreen.X = xPosition;
    positionOnScreen.Y = yPosition;
    return positionOnScreen;
}

//*******************************************************************************************
// Function to simulate a "tick in time" of the length of the aTimeInterval
int Skydiver:: TickInTime(int aTimeInterval)
{
    mTimeSincePreviousTick += aTimeInterval; // increment the time since the previous tick by the time interval
    if (mTimeSincePreviousTick >= mTimeToIncrement) // if the time since the Skydiver last moved down has exceeded or met the required time interval
    {
        yPosition++; // increment the Y position
        mTimeSincePreviousTick = 0; // reset the time since previous tick variable
        return mCurrentPosition->GetPositionPoints(); // return the position points to increment the score for the skydiver moving down
    }
    return 0; // don't add to score if skydiver didn't move down
}

//*******************************************************************************************
// Functio to check if the skydiver has landed
bool Skydiver::CheckForLanding()
{
    // Check if the skydiver has reached the bottom of the "scene"
    if(((29-(yPosition + 5)) * 500) == 0)
    {
        // If the skydiver reached the bottom, set mLanded to true and return true
        mLanded = true;
        return true; 
    }
    // If the Skydiver has not yet landed return false
    return false;
}

//*******************************************************************************************
// Print the Skydiver in its current position
void Skydiver::PrintVecPosition()
{
    mCurrentPosition->PrintPositionVec(xPosition, yPosition, mColorCode); 
}

//*******************************************************************************************
// Return the mLanded variable
bool Skydiver::GetLandedStatus()
{
    return mLanded;
}