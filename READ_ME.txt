Alison Davis - Final Project
Parachute Game Read_Me

Parachute game was tested and compiled using Windows with Visual Studio Code terminal.
The following commands were tested for compilation/running:

g++ Skydiver.cpp Beginner.cpp Intermediate.cpp Expert.cpp CanopyExpert.cpp Position.cpp Game.cpp Main.cpp -o theGame

./theGame


If the terminal window is not maximized, gameplay will not work correctly. Parachute simulates skydivers that have different levels
and are capable of different positions that real skydivers often perform. The following instructions will be available at the beginning
 of the game but are provided here for preview. Please read them carefully :) Enjoy.

----------------------------------------------------------------------------       
Welcome to Parachute. Please MAXIMIZE TERMINAL WINDOW and READ ALL INSTRUCTIONS.   
All skydivers fall at a constant rate. You can only control the lowest skydiver    
whose canopy is not open. You can change between valid positions for that level    
skydiver and pull at any altitude above the minimum pull altitude. IF YOU DO NOT   
PULL ON TIME YOU WILL LOSE. Sometimes you can steer the lowest canopy (see skydiver
controls below). Beware, you can only make one motion per drop (steering canopies  
or changing positions) so be careful. SKYDIVERS MUST PULL FROM THE BELLY POSITION.        
Accuracy points are awarded if the canopy lands on the X but this is not always possible. 
More advanced positions are worth more points -- these are awarded for each altitude step 
the skydiver drops in this position. See values belows. Skydiver levels
are classified by the colors below so look carefully and good luck!!!
-----------------------------------------------------------------------------
Position Point Values:
-----------------------------------------------------------------------------
Under Canopy: 0pts
Belly:        10pts
Sit Fly:      25pts
Head Down:    50pts
Land on X:    1000pts
-----------------------------------------------------------------------------
Skydiver Controls (Min Pull Alt.):
-----------------------------------------------------------------------------
Beginner(pull by 7000'): SPACE to pull
Intermediate(pull by 5000'): SPACE to pull, B to Belly, S to Sit
Expert(pull by 4000'): SPACE to pull, B to Belly, S to Sit, H to Head Down
Canopy Expert(4000'): SPACE to pull, B to Belly, S to Sit, H to Head Down
LEFT ARROW and RIGHT ARROW to steer canopy (only possible as lowest canopy)
-------------------------------------------------------------------------