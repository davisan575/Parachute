/////////////////////////////////////////////////////////////////////////////////
// Alison N. Davis
// CIS 554-M401 Object Oriented Programming in C++
// Syracuse University
// Final Project
// 9/13/2020
// Game.hpp
// This program defines the Game class that is used to generate the skydivers
// and game scenery, keep score, and call on the other objects to facilitate 
// the game Parachute
//////////////////////////////////////////////////////////////////////////////////

// Necessary includes
#pragma once
#include <iostream>
#include<list>
#include <sstream>
#include "Position.hpp"
#include "Skydiver.hpp"
#include <memory>
#include <atomic>
#include <mutex>
#include <windows.h>

// Declaration of Game class
class Game{

public: 
    Game(); // Constructor
    void Initialize(); // Function to initialize game and print instructions
    void RunGame(); // Function that begins the running of the game and continues running until game terminates
    void AddJumper(); // Function to randomly add a skydiver to the game (it is random which of the classes that extend skydiver is generated)
    void UserInputThread(); // A function that is created as a thread to continuously accept user input for how to move skydivers over time
    void PrintInstructions(); // A function to print instructions to the game "Parachute"

private:
    static int NUM_JUMPER_TYPES; // Number of jumper types (number of classes that extend Skydiver to choose between)
    static const int TIME_INTERVAL; // Time interval at which the game updates
    static const int ADD_JUMPER_INTERVAL; // Time interval at which to add the next skydiver to the game

    void GeneratePositions(); // Function to populate the mAvailablePositions vector
    std::vector<std::shared_ptr<Position>> mAvailablePositions; // vector of all of the positions that have been created as options for the classes that extend skydiver class
    std::stringstream scene; // Stringstream used to store the scene that prints in the background
    std::list<std::shared_ptr<Skydiver>> jumpersInAir; // std::list of Skydivers currently in the game (skydivers in free fall) -- all instances of polymorphism
    std::list<std::shared_ptr<Skydiver>> jumpersUnderCanopy; // std::list of Skydivers currently in the game (skydivers under canopy) -- all instances of polymorphism
    std::atomic<bool> mRunning {true}; // Bool to track if game still running
    std::thread mUserInputThread; // separate thread for taking user input
    std::mutex mMutex; // mutex to keep from making changes to instances of Skydivers at the same time that they are being printed
    std::stringstream parachuteOpening; // Opening statement of the game title
    bool landedMan; // bool to keep track whether or not a man has landed
    int mScore; // current score for the game

};