/// @note Revision on 3/18/2022, Thien Nguyen
/*
    Description: The program is a rendition of a Battle Royale that has 25
                    players. The center of the storm is randomly generated, and
                    the storm will progressively get closer to that center
                    through each round, until one, or no players are left alive.
    Input: The only expected input of the program is the user pressing 'enter'
            to start the next round.
    Output: The expected output of the program is to constantly a constantly
            refreshed terminal of the storm and the characters, until one
            player, or none, is left alive.
*/

#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<cmath>

using namespace std;

/*
    function_identifier: This function generates the map, and randomly
                         places 25 players on different locations on the
                         map.
    parameters: The lengths of the X and Y grid, the players, and
                the 2D array of the whole map.
    return value: None
*/

void generateMap(int gridY, int gridX, char player, char brMap[][50]) {
    int randX = rand() % gridX;       // randomly picks an X coordinate
    int randY = rand() % gridY;       // randomly picks a Y coordinate

    for (int i = 0; i < 25; i++) 
    {
        while (brMap[randY][randX] >= 65 && brMap[randY][randX] <= 90) 
        {
            randX = rand() % gridX;       // if player already exists on that coordinate
            randY = rand() % gridY;       // it'll choose a new set of coordinates
        }
        brMap[randY][randX] = player;     // if it doesnt exist it'll put a plyer there
        player++;
    }
    for (int i = 0; i < gridY; i++) 
    {
        //prints out whole map w/ all the players
        for (int j = 0; j < gridX; j++) { cout << brMap[i][j]; }
                            cout << endl;
    }
}

/*
    function_identifier: This function handles all direction of the storm,
                         as well as player status. It progresses each round
                         when the user presses enter, and will keep track
                         of a player's status each round.

            parameters: The lengths of the X and Y grid, the coordinates of the
                        randomly generated center, the players and their statuses,
                        alive and dead so we can use them as player statuses, and
                        the 2D array of the map.
    return value: None
*/
void storm(int gridY, int gridX, int centerY, int centerX, char player,
           bool playerStatus[], bool alive, bool dead, char brMap[][50]) 
{
    // variable declaration(s)
    int  aliveCount = 0;
    int  round      = 0;
    int  firstX     = 0;
    int  upStorm;
    int  downStorm;
    int  leftStorm;
    int  rightStorm;
    char player1;
    char player2;

    cout << "Round " << round + 1 << " Complete. Press Enter To Continue ";
    round++;

    // Program only reads in enter, otherwise it'll exit
    while (cin.get() != '\n') { cout << "Error! Only Press Enter." << endl; exit(0); }
    
    for (int i = 50; i >= 0; i--) 
    {
        //need variables to handle storms from all directions
        upStorm    = centerY - i;  
        downStorm  = centerY + i;
        leftStorm  = centerX - i;
        rightStorm = centerX + i;

        for (int j = 0; j < leftStorm; j++) 
        {
            for (int k = 0; k < 14; k++) { brMap[k][j] = 'l'; } 
        }

        for (int j = 49; j >= rightStorm; j--) 
        {
            for (int k = 0; k < 14; k++) { brMap[k][j] = 'r'; }
        }

        for (int j = 0; j < upStorm; j++) 
        {
            for (int k=0; k<50; k++) { brMap[j][k] = 'u'; }
        }

        for (int j = 13; j >= downStorm; j--) 
        {
            for (int k = 0; k < 50; k++) { brMap[j][k] = 'd'; }
        }

        // To erase output we have printed between
        for (int j = 0; j <= gridY; j++) { cout << "\033[A\33[2K\r"; }
                                //rounds
                              cout << flush;
        
        for (int j = 0; j < 14; j++) 
        {
            for (int k = 0; k < 50; k++) { cout << brMap[j][k]; }
                                cout << endl;
        }

        cout << "Round " << round + 1 << " Complete. Press Enter To Continue ";
                                  round++;

        while (cin.get()!= '\n') { cout << "Error! Only Press Enter." << endl; exit(0); }


        // needs to break out of loop
        // when it finds a player so it
        // can start looking for the next player
        // it ensures that when you find
        // the player, it doesn't announce it dead again
        for (int j = 0; j < 25; j++) 
        {
            for (int k = 0; k < gridY; k++) 
            {
                for (int l = 0; l < gridX; l++) 
                {
                    if (brMap[k][l] != player) { playerStatus[j] = dead; }
                        else if (brMap[k][l] == player) { playerStatus[j] = alive; break; }
                }                                   
                    if (playerStatus[j] == alive) { break; }
            }
            player++;
        }

        for (int j = 0; j < 25; j++) 
        {
            if (playerStatus[j] == alive) { aliveCount++; }
        }

        // checks the last 2 players alive
        if (aliveCount == 2)
        {
            for (int j = 0; j < gridY; j++) 
            {
                for (int k = 0; k < gridX; k++) 
                {
                    if (brMap[j][k] != ' ' && brMap[j][k] != 's') 
                    {
                        if(firstX == 0) { firstX = k; player1 = brMap[j][k]; }
                            else { player2 = brMap[j][k]; }
                    }
                }
            }
        }
        
        // for a solo winner
        if (aliveCount == 1) 
        { 
            for (int j = 0; j < gridY; j++) 
            {
                for (int k = 0; k < gridX; k++) 
                {
                    if (brMap[j][k] != ' ' && brMap[j][k] != 's') { player = brMap[j][k]; }
                }
            }
                // deliver our message
                cout << "Victory Royale!\n"
                    << "Player '" << player << "' wins!\n"
                    << "Game Over!" << endl;
            break;
        } 
        // randomly chooses between the 2 winners
        else if (aliveCount == 0) 
        {
            if (rand() % 10 % 2 == 1) { player = player1; }
                else { player = player2; }

            // wtf...
            cout << "Player '" << player << "' nearly took the L, but won!\n"
                 << "Game Over!" << endl;
            break;
        }
            aliveCount = 0;
            player = 'A';
    }
}

int main(int argc, char* argv[]) {

    srand(time(NULL));

    // variable declaration(s)
    const int   gridX     = 50;
    const int   gridY     = 14;
    const int   playerCnt = 25;
    const bool  alive     = true;
    const bool  dead      = false;
          char  player    = 'A';
          int   centerX   = rand()%gridX;
          int   centerY   = rand()%gridY;

          char  brMap[gridY][gridX];
          bool  playerStatus[playerCnt] = {alive};
    // clear the screen, see through
    cout << "\033[A\33[2K\r";
    cout << "Center: (" << centerX << "," << centerY << ")" << endl;
    cout << "Thien Nguyen's Battle Royale!\n";

    for (int i = 0; i < gridY; i++) 
    {
        for (int j = 0; j < gridX; j++) { brMap[i][j] = ' '; }
    }

    generateMap(gridY, gridX, player, brMap);
    storm(gridY, gridX, centerY, centerX, player, playerStatus,
          alive, dead, brMap);

    // return to the OS
    return 0;
}
