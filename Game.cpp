/////////////////////////////////////////////////////////////////////////////////
// Alison N. Davis
// CIS 554-M401 Object Oriented Programming in C++
// Syracuse University
// Final Project
// 9/13/2020
// Game.cpp
// This program implements the Game class that is used to generate the skydivers
// and game scenery, keep score, and call on the other objects to facilitate 
// the game Parachute
//////////////////////////////////////////////////////////////////////////////////

// Necessary Includes
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include "Game.hpp"
#include "Beginner.hpp"
#include "Intermediate.hpp"
#include "Expert.hpp"
#include "CanopyExpert.hpp"

// Enumeration to keep track of the types of skydivers(jumpers)
enum JumperTypes: int
{
  BEGINNER = 0,         // Identifies with a beginner skydiver
  INTERMEDIATE = 1,     // Identifies with an intermediate skydiver
  EXPERT = 2,           // Identifies with an expert skydiver (cannot steer under canopy)
  CANOPY_EXPERT = 3     // Identifies with an expert skydiver (can steer under canopy)
};

int Game::NUM_JUMPER_TYPES{4}; // Keeps track of the number of types of skydivers that can be randomly generated (increment when new class is added)
const int Game::TIME_INTERVAL{250}; // Millisecond wait time between when the game buffer that is printed can be updated
const int Game::ADD_JUMPER_INTERVAL{3000}; // milliseconds between when skydivers are generated

// Game Constructor
Game::Game() :
  landedMan{false},
  mScore{0}
{
  srand(time(NULL)); // seed random number

  // Populate stringstream used to print the game screen
  scene << "####################################################################\n";                     
  scene << "#          _ .                                                     #\n"; 
  scene << "#        (  _ )_                                                   #\n";
  scene << "#      (_  _(_ ,)                                                  #\n";
  scene << "#                                                             |    #\n";
  scene << "#               _  _                                        \\ _ /  # \n";
  scene << "#              ( `   )_                                   -= (_) =-#\n";
  scene << "#             (    )    `)                                  /   \\  # \n";
  scene << "#           (_   (_ .  _) _)                                  |    #\n";
  scene << "#10,000                                                            #\n";
  scene << "#-                                                                 #\n";
  scene << "#9,000                                                             #\n";
  scene << "#-                                                                 #\n";
  scene << "#8,000                                                             #\n";
  scene << "#-                                                                 #\n";
  scene << "#7,000                                                             #\n";
  scene << "#-                                                                 #\n";
  scene << "#6,000                                                             #\n";
  scene << "#-                                                                 #\n";
  scene << "#5,000                                                             #\n";
  scene << "#-                                                                 #\n";
  scene << "#4,000                                                             #\n";
  scene << "#-                                                                 #\n";
  scene << "#3,000                                                             #\n";
  scene << "#-                                                                 #\n";
  scene << "#2,000                                                             #\n";
  scene << "#-                                                                 #\n";
  scene << "#1,000                                                             #\n";
  scene << "#-                                                                 #\n";
  scene << "###########################\\/######################################\n";
  scene << "###########################/\\######################################\n";

  // Call to function to generate the positions that the skydivers can take on
  GeneratePositions();
} 

// Initialize function to clear out screen and print initial instructions
void Game::Initialize()
{
  //Clear screen
  printf("\033c");
  system("CLS");
  HANDLE hConsole;
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, 2);
  parachuteOpening << "                            _           _       \n";
  parachuteOpening << "                           | |         | |      \n";
  parachuteOpening << " _ __   __ _ _ __ __ _  ___| |__  _   _| |_ ___ \n";
  parachuteOpening << "| '_ \\ / _` | '__/ _` |/ __| '_ \\| | | | __/ _ \\\n";
  parachuteOpening << "| |_) | (_| | | | (_| | (__| | | | |_| | ||  __/\n";
  parachuteOpening << "| .__/ \\__,_|_|  \\__,_|\\___|_| |_|\\__,_|\\__\\___|\n";
  parachuteOpening << "| |                                             \n";
  parachuteOpening << "|_|                                             \n";
  std::cout << parachuteOpening.str();  
  SetConsoleTextAttribute(hConsole, 15);

  // Print instructions
  PrintInstructions();
  // Wait for the user to direct you to proceed
  system("pause");

  //Flush output stream and clear screen before generating game visuals
  std::cout << std::flush;
  system("CLS");
}

// Function to Run Game
void Game::RunGame()
{
  int timeToAddJumper = 0; // start the timer that keeps track of when to add jumper at zero
  mMutex.lock();
  AddJumper(); // Add the first jumper
  mMutex.unlock();
  mUserInputThread = std::thread(&Game::UserInputThread, this); // Generate a separate thread for accepting user input for how to control jumpers
  
  // Keep running game until mRunning is false
  while(mRunning)
  {
    mMutex.lock(); // Lock the mutex so that the other thread accepting user input cannot edit the skydivers while they are being printed
    if(timeToAddJumper == ADD_JUMPER_INTERVAL) // If it is time to add another jumper
    {
      AddJumper(); // Add a jumper function call
      timeToAddJumper = 0; // set the time to add jumper back to zero
    }
    timeToAddJumper += TIME_INTERVAL; // Increment the time to add jumper by the time interval

    // Set the print location back to the origin and print the game screen there
    COORD origin; 
    origin.X = 0;
    origin.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), origin);
    std::cout << scene.str(); // Print the game background scene
    std::cout << "Game Score: " << mScore << std::endl; // print the current game score


    // Handle operations for each jumper "under canopy (in the pulled position)"
    for(std::shared_ptr<Skydiver> csd : jumpersUnderCanopy)
    {
      // If a jumper is landed (hit the bottom of the game screen) handle differently
      if(csd->GetLandedStatus())
      {
        //still print the jumper so the landed jumper position shows once
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), csd->GetCoord());
        csd->PrintVecPosition();
        landedMan = true; // set the landedMan to true so the game knows a man is landed and has already printed
      }
      // if the current jumper under canopy is not yet landed, print them and perform the TickInTime function on them to keep them moving down
      else
      {
        // print the jumper
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), csd->GetCoord());
        csd->PrintVecPosition();
        // keep the jumper moving down using tickintime
        mScore += csd->TickInTime(Game::TIME_INTERVAL);
        // if the jumper has landed run this
        if(csd->CheckForLanding())
        {
          csd->AdjustPrintAltitude(1, 2); //adjust the print altitude becuase the landed man is smaller than the "pull" position
          csd->SetPosition((csd->GetValidPositions())[static_cast<int>(pos::ePosition::LAND)]); // set the posiition of this jumper to the LAND position
        }
      }
    }

    // Handle operations for each jumper in air but not under canopy (not yet pulled)
    for(std::shared_ptr<Skydiver> sd : jumpersInAir)
    {
      // Print the jumper's poistion
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), sd->GetCoord());
      sd->PrintVecPosition();
      // perform tick in time operation to keep jumper moving down screen
      mScore += sd->TickInTime(Game::TIME_INTERVAL);
      // Validate the altitude to see if the jumper should have pulled by now, if the pull altitude has passed then terminate the game
      if(!sd->ValidatePullAltitude())
      {
        mRunning = false; // missed pull altitude, mRunning is set to false
        mMutex.unlock(); // unlock the mutex
        mUserInputThread.join(); // join the user input thread
      }
    }

    // If there is a man that has landed and already printed, time to handle that case
    if(landedMan)
    {
      // Award bonus points if the landed man is close enough to the X on the ground
      if(jumpersUnderCanopy.front()->GetCoord().X >= 25 && jumpersUnderCanopy.front()->GetCoord().X <= 29)
      {
        mScore += 1000; //Big bonus for landing on target
      }
      // Remove the landed man from the jumpersUnderCanopyList
      jumpersUnderCanopy.pop_front();
      landedMan = false; // Set the landed man back to false because there is no longer a landed man
    }
    mMutex.unlock(); // unlock the mutex to give the user input thread a chance
    std::this_thread::sleep_for(std::chrono::milliseconds(Game::TIME_INTERVAL)); // Sleep for a preset time interval that also helps control how fast divers fall
    // clear out the screen before running again 
    std::cout << std::flush;
    system("CLS");
  }

  // Once pull altitude is missed for one of the jumpers inform the user what happened and what their final score was
  std::cout << "--------------------------------------" << std::endl;
  std::cout << "GAME OVER, FAILED TO PULL ON TIME!!!!!" << std::endl;
  std::cout << "Final Score: " << mScore << std::endl;
  std::cout << "--------------------------------------" << std::endl;

}

// Function to generate the position options for the skydivers
void Game::GeneratePositions()
{
    //Generate belly position 
    std::vector<std::string> tempPullerString;
    std::shared_ptr<Position> belly = std::make_shared<Position>(10);
    std::string bellyString;
    bellyString = "`\\__\\o_\n";
    tempPullerString.push_back(bellyString);
    belly->SetAsciiVecPrint(tempPullerString);
    belly->SetPositionReference(pos::ePosition::BELLY);
    tempPullerString.clear();

  //Generate landed position 
  std::shared_ptr<Position> land = std::make_shared<Position>(0);
  tempPullerString.push_back(std::string("  o  \n"));  
  tempPullerString.push_back(std::string(" /|\\ \n")); 
  tempPullerString.push_back(std::string(" / \\ \n"));  
  land->SetAsciiVecPrint(tempPullerString);
  land->SetPositionReference(pos::ePosition::LAND);
  tempPullerString.clear();

  // Generate pull position
  std::shared_ptr<Position> pull = std::make_shared<Position>(0);
  tempPullerString.push_back( std::string("   .--.  \n")); 
  tempPullerString.push_back( std::string("  (____) \n"));     
  tempPullerString.push_back( std::string("  _\\o/_  \n"));        
  tempPullerString.push_back( std::string("   //    \n"));      
  tempPullerString.push_back( std::string("  ( )    \n"));
  pull->SetAsciiVecPrint(tempPullerString);
  pull->SetPositionReference(pos::ePosition::PULL);
  tempPullerString.clear();

  // Generate sit position
  std::shared_ptr<Position> sit = std::make_shared<Position>(25);
  tempPullerString.push_back( std::string ("o_, \n")); 
  tempPullerString.push_back( std::string ("|_  \n"));
  tempPullerString.push_back( std::string ("  \\ \n"));
  sit->SetAsciiVecPrint(tempPullerString);
  sit->SetPositionReference(pos::ePosition::SIT);
  tempPullerString.clear();

  // Generate head down position
  std::shared_ptr<Position> headDown = std::make_shared<Position>(50);
  tempPullerString.push_back( std::string (" \\/  \n"));
  tempPullerString.push_back( std::string ("  \\o \n"));
  tempPullerString.push_back( std::string ("  ( \\ \n"));  
  headDown->SetAsciiVecPrint(tempPullerString);
  headDown->SetPositionReference(pos::HEAD_DOWN);
  tempPullerString.clear();


  // Push all of the positions that were just created into one vector -- note put positions in in accordance with the order 
  // for the ePosition enumeration defined in Position.hpp. This keeps everything aligned and accurate.
  mAvailablePositions.push_back(land);
  mAvailablePositions.push_back(pull);
  mAvailablePositions.push_back(belly);
  mAvailablePositions.push_back(sit);
  mAvailablePositions.push_back(headDown);
    
} 

// Function to add a new jumper
void Game::AddJumper()
{
  // Generate a randum number that corresponds with a jumper type that extends the base class Skydiver (there are currently 4: Beginner, Intermediate, Expert, and CanopyExpert)
  int randomJumperGenerator = rand() % Game::NUM_JUMPER_TYPES;
  // Depending on the random number that was generated, create the jumper type accordingly and push it into the jumpersInAir std::list
  JumperTypes randomJumperGeneratorCast = static_cast<JumperTypes>(randomJumperGenerator);
  switch (randomJumperGeneratorCast)
  {
    case JumperTypes::BEGINNER: {
      std::shared_ptr<Skydiver> skydiverBase = std::make_shared<Beginner>(mAvailablePositions);
      jumpersInAir.push_back(skydiverBase);
      break;}
    case JumperTypes::INTERMEDIATE: {
      std::shared_ptr<Skydiver> skydiverBase = std::make_shared<Intermediate>(mAvailablePositions);
      jumpersInAir.push_back(skydiverBase);
      break;}
    case JumperTypes::EXPERT: {
      std::shared_ptr<Skydiver> skydiverBase = std::make_shared<Expert>(mAvailablePositions);
      jumpersInAir.push_back(skydiverBase);
      break;}
    case JumperTypes::CANOPY_EXPERT:{
      std::shared_ptr<Skydiver> skydiverBase = std::make_shared<CanopyExpert>(mAvailablePositions);
      jumpersInAir.push_back(skydiverBase);
      break;}
    default:
      break;
  }
}

// Separate thread to accept user input for the Skydivers 
void Game::UserInputThread()
{
  // clear from initial key press and do nothing with call (make sure you check for the critical keys following the "press any key")
  GetAsyncKeyState(VK_SPACE); 
  GetAsyncKeyState(0x42);
  GetAsyncKeyState(0x53);
  GetAsyncKeyState(0x48);
  GetAsyncKeyState(VK_LEFT);
  GetAsyncKeyState(VK_RIGHT);
  while(mRunning)
  {
    // If the spacebar was pressed since the last call to GetAsyncKeyState 
    if(GetAsyncKeyState(VK_SPACE) && !(jumpersInAir.empty()))
    {
        mMutex.lock(); //lock the mutex
        if(jumpersInAir.front()->Pull()) // run the pull function for the lowest skydiver that is still not pulled
        {
          jumpersUnderCanopy.push_back(jumpersInAir.front()); //if the lowest skydiver pulled, put him in the jumpersUnderCanopy list
          jumpersInAir.pop_front(); // remove the skydiver that just pulled from the jumpersInAir list
        }
        //else nothing (if the jumper could not pull)
        mMutex.unlock(); //unlock the mutex
        std::this_thread::sleep_for(std::chrono::milliseconds(400)); //sleep this thread for a brief time
    }

    // If the B key was pressed since the last call to GetAsyncKeyState 
    else if(GetAsyncKeyState(0x42) && !(jumpersInAir.empty()))
    {
        mMutex.lock(); // lock the mutex
        jumpersInAir.front()->ToBelly(); // call the ToBelly function on the lowest jumper in the air
        mMutex.unlock(); // unclock the mutex
        std::this_thread::sleep_for(std::chrono::milliseconds(400)); // sleep this thread for a brief time
    }

    // If the S key was pressed since the last call to GetAsyncKeyState 
    else if(GetAsyncKeyState(0x53) && !(jumpersInAir.empty())) 
    {
        mMutex.lock(); // lock the mutex
        jumpersInAir.front()->ToSit(); // call the ToSit function on the lowest jumper in the air
        mMutex.unlock(); // unclock the mutex
        std::this_thread::sleep_for(std::chrono::milliseconds(400)); // sleep this thread for a brief time
    }
    
    // If the H key was pressed since the last call to GetAsyncKeyState 
    else if(GetAsyncKeyState(0x48) && !(jumpersInAir.empty()))
    {
        mMutex.lock(); // lock the mutex
        jumpersInAir.front()->ToHeadDown(); // call the ToHeadDown function on the lowest jumper in the air
        mMutex.unlock(); // unclock the mutex
        std::this_thread::sleep_for(std::chrono::milliseconds(400)); // sleep this thread for a brief time
    }

    // If the Left key was pressed since the last call to GetAsyncKeyState 
    else if(GetAsyncKeyState(VK_LEFT) && !(jumpersUnderCanopy.empty()))
    {
      mMutex.lock(); // lock the mutex
      jumpersUnderCanopy.front()->Left(); // call the Left function on the lowest jumper under canopy
      mMutex.unlock(); // unclock the mutex
      std::this_thread::sleep_for(std::chrono::milliseconds(400)); // sleep this thread for a brief time
    }

    // If the Right key was pressed since the last call to GetAsyncKeyState 
    else if(GetAsyncKeyState(VK_RIGHT) && !(jumpersUnderCanopy.empty()))
    {
      mMutex.lock(); // lock the mutex
      jumpersUnderCanopy.front()->Right(); // call the Right function on the lowest jumper under canopy
      mMutex.unlock(); // unclock the mutex
      std::this_thread::sleep_for(std::chrono::milliseconds(400)); // sleep this thread for a brief time
    }
  }
}

// Function to print all game unstructions
void Game::PrintInstructions()
{
  HANDLE hConsole;
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, 15); // print instructions in white
  std::cout << "----------------------------------------------------------------------------" << std::endl;
  std::cout << "Welcome to Parachute. Please MAXIMIZE TERMINAL WINDOW and READ ALL INSTRUCTIONS." << std::endl;
  std::cout << "All skydivers fall at a constant rate. You can only control the lowest skydiver " << std::endl;
  std::cout << "whose canopy is not open. You can change between valid positions for that level " << std::endl;
  std::cout << "skydiver and pull at any altitude above the minimum pull altitude. IF YOU DO NOT" << std::endl;
  std::cout << "PULL ON TIME YOU WILL LOSE. Sometimes you can steer the lowest canopy (see skydiver" << std::endl;
  std::cout << "controls below). Beware, you can only make one motion per drop (steering canopies " << std::endl;
  std::cout << "or changing positions) so be careful. SKYDIVERS MUST PULL FROM THE BELLY POSITION." << std::endl;
  std::cout << "Accuracy points are awarded if the canopy lands on the X but this is not always possible. " << std::endl;
  std::cout << "More advanced positions are worth more points -- these are awarded for each altitude step " << std::endl;
  std::cout << "the skydiver drops in this position. See values belows. Skydiver levels" << std::endl;
  std::cout << "are classified by the colors below so look carefully and good luck!!!" << std::endl;
  std::cout << "-----------------------------------------------------------------------------" << std::endl;
  std::cout << "Position Point Values:" << std::endl;
  std::cout << "-----------------------------------------------------------------------------" << std::endl;
  std::cout << "Under Canopy: 0pts " << std::endl;
  std::cout << "Belly:        10pts" << std::endl;
  std::cout << "Sit Fly:      25pts" << std::endl;
  std::cout << "Head Down:    50pts" << std::endl;
  std::cout << "Land on X:    1000pts" << std::endl;
  std::cout << "-----------------------------------------------------------------------------" << std::endl;
  std::cout << "Skydiver Controls (Min Pull Alt.):          " << std::endl;
  std::cout << "-----------------------------------------------------------------------------" << std::endl;
  SetConsoleTextAttribute(hConsole, 1);
  std::cout << "Beginner(pull by 7000'): SPACE to pull     " << std::endl;
  SetConsoleTextAttribute(hConsole, 14);
  std::cout << "Intermediate(pull by 5000'): SPACE to pull, B to Belly, S to Sit" << std::endl;
  SetConsoleTextAttribute(hConsole, 4);
  std::cout << "Expert(pull by 4000'): SPACE to pull, B to Belly, S to Sit, H to Head Down" << std::endl;
  SetConsoleTextAttribute(hConsole, 5);
  std::cout << "Canopy Expert(4000'): SPACE to pull, B to Belly, S to Sit, H to Head Down" << std::endl;
  std::cout << "LEFT ARROW and RIGHT ARROW to steer canopy (only possible as lowest canopy)  " << std::endl;
  SetConsoleTextAttribute(hConsole, 15);
  std::cout << "-------------------------------------------------------------------------" << std::endl;
  std::cout << std::flush;
}