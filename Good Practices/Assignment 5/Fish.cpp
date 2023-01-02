/*
   Description: This program will utilize the fish header file to detect whether a fish is facing up or down, and will correspond accordingly.
   Input: Char of the fish
   Output: A real-time update of the fish location
*/

#include "Fish.h"

//******************* VertiFish function implementations *******************
// Flips direction on collision with a wall and changes drawing char
void VertiFish::onWallCollision() 
{ 
    if(facingUp){
        facingUp = false;
        drawChar = 'v';
    }
    else{
        facingUp = true;
        drawChar = '^';
    }
}

// Moves the fish either up or down every frame, depending on which direction it is facing
void VertiFish::swim(Tank* tank) 
{ 
    if (facingUp){
        tank -> moveFish(this, 0, -1);
    }
    else{
        tank -> moveFish(this, 0, 1);
    }
}

//******************* HorizontaFish function implementations *******************
// Turns around on collision with a wall and changes drawing char
void HorizontaFish::onWallCollision() 
{
	if(facingRight){
        facingRight = false;
        drawChar = '<';
    }
    else{
        facingRight = true;
        drawChar = '>';
    }
}

// Moves the fish either right or left every frame depending on the direction it is facing
void HorizontaFish::swim(Tank* tank) 
{
	if (facingRight){
        tank -> moveFish(this, 1, 0);
    }
    else{
        tank -> moveFish(this, -1, 0);
    }
}

//******************* WallFish function implementations *******************
void WallFish::onWallCollision() {  /*Do nothing. This needs to exist for WallFish to not be abstract */ }
void WallFish::swim(Tank*)       {  /*Do nothing. This needs to exist for WallFish to not be abstract */ }