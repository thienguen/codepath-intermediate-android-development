/*
   Description: This program will keep track of all the fish in the tank, and update their locations and if they hit a wall.
   Input: Inherited fish class
   Output: A real-time update of the fish location
*/
#include "Fish.h"
#include <iomanip>  // For drawing the Tank
#include <cstdlib>  // Used to flush the Tank
#include <iostream>

using namespace std;

// Updates the Tank by updating all of the Fish in it in the order that they entered the Tank. This function is implemented for you already.
void Tank::update()
{
	// Update all the fish in the Tank (Make them swim)
	for (Fish* fish : fishList) { fish->swim(this); } // Let it swim }
}

// Adds a fish to the Tank
void Tank::addFish(Fish* fish)
{
	/*
	YOUR CODE HERE 
	*/
	
	// TODO: Add the fish to the tankArr using the fish's x and y positions
	// Add the Fish to the fishList vector
	// You can assume that the person using this function will not place any fish on top of each other, but error checking is fine
	tankArr[fish->getYPos()] [fish->getXPos()] = fish; 
	
	// loads vector Fish with current fish
	fishList.push_back(fish);
}

// Attempts to move the fish by the given amount in the x and y directions
void Tank::moveFish(Fish* fish, int xMove, int yMove)
{
	// Find the positions that the fish wants to move to and it's current positions
	int oldXPos = fish->getXPos();   // Previous x position of the fish
	int oldYPos = fish->getYPos();   // Previous y position of the fish
	int newXPos = oldXPos + xMove;   // Desired  x position to move the fish to
	int newYPos = oldYPos + yMove;   // Desired  y position to move the fish to

	/* 
	YOUR CODE HERE 
	*/

	// TODO: Check if the object can move to the desired location (Order of the checks matters!!!)

	/*
	You will need to check a few things:
	Check if the fish would go out of bounds of the tank (left of 0, right of width, above 0, or below height) 
		If so, don't move it at all, but do call the Fish's onWallCollision() function and return
			Else if the space is free (i.e. the space is null and has no fish)
			Set the Fish's old (x, y) position in the tankArr to null (In other words, make it empty)
			Move the fish to the new (x, y) position in the tankArr
			Update the Fish's position using setPosition to its new position 
			#Remember that since arrays are row, column that the order of access is arr[y][x], not x, y 
			Else if the space contains a WallFish, then also call onWallCollision() (Check if the object's char is a 'W')
			Also call onWallCollision
	*/

	if (newXPos < 0 || newXPos >= width || newYPos < 0 || newYPos >= height) { fish->onWallCollision(); }
	else if (tankArr[newYPos][newXPos] == nullptr) 
	{
		tankArr[oldYPos][oldXPos] = nullptr;
		tankArr[newYPos][newXPos] = fish; 						// updates fish position
		fish -> setPosition(newXPos, newYPos);
	}
	else if (tankArr[newYPos][newXPos] -> getDrawChar() == 'W')
	{   // checks if char is a 'W' for wall collision
		fish->onWallCollision();
	}
}

// Draws the tank and all of the fish inside of it. This is a helper function implemented for you.
void Tank::drawTank()
{
	//Clear the screen
	#ifdef _WIN32
	system("CLS");
	#else
	cout << "\033[2J\033[1;1H";
	#endif

	int i, j;
	// Draw the top of the tank
	cout << "|" << setfill('^') << setw(width + 1) << "|" << endl; 
	for (i = 0; i < height; i++)
	{
		// Draw the left wall of the tank
		cout << "|"; 
		for (j = 0; j < width; j++)
		{
			// If the space is not empty, draw the fish there
			if (tankArr[i][j] != nullptr) 
				cout << tankArr[i][j]->getDrawChar();
			// Else if the space is empty, draw a blank space
			else 
				cout << " ";
		}
		// Draw the right wall of the tank
		cout << "|" << endl; 
	}
	// Draw the bottom of the tank
	cout << "|" << setfill('_') << setw(width + 1) << "|" << endl; 
}

// Constructor for the Tank
Tank::Tank(int width, int height)
{
	// Set the width and height members
	this->width = width;
	this->height = height;

	//Allocate the 2D array based on the width and height
	//TODO: Allocate all of the rows first
	//TODO: Allocate the columns in each row next and initialize all the pointers to nullptr
	tankArr = new TankObject**[height];
	for (int i = 0; i < height; i++)
	{
		tankArr[i] = new TankObject*[width];
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			tankArr[i][j] = nullptr;
		}
	}
}

// Destructor for the Tank
Tank::~Tank()
{
	//TODO: Go through and deallocate all of the fish in the fishList. Then deallocate the 2D tankArr array
		//Deallocate each fish from the fishList
		//Deallocate each of the rows
		//Deallocate the column that held all of the rows
	
	for (int i = 0; i < height; i++)
	{
		delete[] tankArr[i];
	}
		
	delete[] tankArr;

	for (int i = fishList.size(); i < 0; i--)
	{
		delete fishList.back();
	}
}