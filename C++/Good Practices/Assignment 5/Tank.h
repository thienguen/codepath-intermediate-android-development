#ifndef TANK_H
#define TANK_H

#include <vector>

using namespace std;

// Forward declaration of Fish class
class Fish;

// Abstract class for all objects that will be in the Tank
// X,Y coordinates in Tank
class TankObject
{
	int xPos, yPos;
	// Character used to draw the object in the tank
	
	protected:
		char drawChar; 
		TankObject(int x, int y, char drawChar) { this->xPos = x; this->yPos = y; this->drawChar = drawChar; }
	public:
		// Default constructor is needed for allocation of Tank array
		TankObject() 							{ drawChar = ' '; } 
		void setPosition(int newX, int newY) { xPos = newX; yPos = newY; }
		int  getXPos() 						 { return xPos; }
		int  getYPos() 						 { return yPos; }
		char getDrawChar() 					 { return drawChar; }
};

//Tank class which will hold all the Fish and water.
class Tank
	// 2D-Array representing the Tank. 
{
	// This is a 2D array of TankObject pointers (Hence the ***). The first two ** are for the dimensions of the 2D array and the 
	int width, height;
	
	// List of references to all the fish in the tank
	vector<Fish*> fishList;
	
	// third * is for the actual TankObject itself
	TankObject*** tankArr; 

	// Helper functions if the x and y being reversed seems annoying
	void setTankSpace(int x, int y, TankObject* obj) { tankArr[y][x] = obj; }
	
	TankObject* getTankObject(int x, int y) { return tankArr[y][x]; }

	public:
		void update();
		void addFish(Fish* fish);
		void moveFish(Fish* fish, int xMove, int yMove);
		
		// Constructor / Destructor
		void drawTank();

		Tank(int width, int height);
		~Tank();
};

#endif