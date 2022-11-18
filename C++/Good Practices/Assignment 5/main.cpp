/// Assignment 5 : Virtual Aquarium Solution
/// Author: Thien Nguyen
/// @date 3/29/2022 

#include <iostream>
#include <vector>
#include <cstdlib>
#include "Tank.h"
#include "Fish.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <time.h>
#include <unistd.h>
#endif

using namespace std;

// Constants for the size of the tank
const int TANK_WIDTH = 60;
const int TANK_HEIGHT = 12;

// Constants for drawing / refresh rate
// Approximate number of seconds that the program should run for
const unsigned int PROGRAM_DURATION = 8; 
const unsigned int FPS = 15;
const unsigned long TOTAL_FRAMES = PROGRAM_DURATION * FPS;
const unsigned long SLEEP_TIME = 1000 / FPS;

// Initialize fish count to 0
int Fish::count = 0; 

void randomlyAddFish(Tank* tank, unsigned int, int fishCount = 10);

int main(int argc, char** argv)
{
    // Error check the command line arguments

    // Try to convert the seed to 
    // Default seed for the aquarium
    int fishSeed = 16407; 
    // If the user specified a seed
    if (argc == 2) 
    {
        try { fishSeed = atoi(argv[1]); }
        catch (exception& e)
        {
            cout << "Error, could not convert " << argv[1] << " to an int" << endl;
            return 1;
        }
    }
    else if (argc > 2)
    {
        cout << "ERROR: Usage is: ./virt_aqua [optional_seed]" << endl;
        return 1;
    }

    // Create the fish Tank
    Tank* tank = new Tank(TANK_WIDTH, TANK_HEIGHT); 

    // ***** Put all of the Fish into the Tank *****
    #ifndef _WIN32
        // int retVal;
        timespec sleepTime, remainingTime;
        sleepTime.tv_sec = 0;
        sleepTime.tv_nsec = 1000000 * SLEEP_TIME;
    #endif
    randomlyAddFish(tank, fishSeed);

    // DEBUG: You can add fish here to test if you'd like, just make sure to delete it when you're done

    // How many frames have passed
    unsigned long frameCounter = 0; 
    while (frameCounter < TOTAL_FRAMES)
    {
        // Update all of the Fish in the Tank
        tank->update(); 
        // Draw the new Tank
        tank->drawTank(); 

        #ifdef _WIN32
        Sleep(SLEEP_TIME);
        #else
        //sleep(1);
        nanosleep(&sleepTime, &remainingTime);
        #endif
        // Count this frame
        frameCounter++; 
    }

    // Deallocate the tank and all of the Fish in the Tank
    delete tank;

    return 0;
}

// Randomly fills the given tank with the amount of fish given and does not place fish on top of each other
void randomlyAddFish(Tank* tank, unsigned int seed, int fishCount)
{
    bool occupied[TANK_HEIGHT][TANK_WIDTH];
    int i, j;
    // Seed the random number generation
    srand(seed); 

    // Initialize to all false
    for (i = 0; i < TANK_HEIGHT; i++)
        for (j = 0; j < TANK_WIDTH; j++)
            occupied[i][j] = false;

    // Go through and generate all of the fish
    int numToGenerate = TANK_WIDTH * TANK_HEIGHT / 2;
    numToGenerate = numToGenerate < fishCount ? numToGenerate : fishCount;

    // Count of how many fish were generated
    int count = 0; 
    while (count < numToGenerate)
    {
        i = rand() % TANK_HEIGHT;
        j = rand() % TANK_WIDTH;

        // Generate a new space while the currently generated space is filled with a fish
        while (occupied[i][j]) 
        {
            i = rand() % TANK_HEIGHT;
            j = rand() % TANK_WIDTH;
        }

        // Mark that the generated space is occupied
        occupied[i][j] = true; 
        // Pick a random type of fish to generate
        switch (rand() % 3) 
        {
            case 0:
                tank->addFish(new WallFish(j, i));
                break;
            case 1:
                tank->addFish(new HorizontaFish(j, i, rand() % 2 == 0));
                break;
            case 2:
                tank->addFish(new VertiFish(j, i, rand() % 2 == 0));
                break;
            default:
                tank->addFish(new HorizontaFish(j, i, rand() % 2 == 0));
                break;
        }

        count++;
    }
}
