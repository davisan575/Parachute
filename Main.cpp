/////////////////////////////////////////////////////////////////////////////////
// Alison N. Davis
// CIS 554-M401 Object Oriented Programming in C++
// Syracuse University
// Final Project
// 9/13/2020
// Main.cpp
// This program launches the Parachute game using the Game class
//////////////////////////////////////////////////////////////////////////////////

//Necessary includes
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <sstream>
#include <windows.h>
#include "Game.hpp"

int main()
{
    Game game; // create instance of Game class
    game.Initialize(); // call initialize function to print opening and instructions
    game.RunGame(); // function to run the game until losing

}