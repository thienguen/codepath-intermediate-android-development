#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>

using namespace std;

// function prototypes

void welcomeMessage();

void endGameMessage();

void replayGame(char *replay);

void getLotteryNumbers(int lotteryNumbers[]);

void getPlayerNumbers(int playerNumber[]);

void sortNumbers(int SortNumbers[]);

void checkNumbers(int lotteryNumbers[], int playerNumbers[]);

void resultsMessage(int counter);



int main()
{
    int lotteryNumbers[5];   // array to store random lottery numbers
    int playerNumbers[5];    // array to store user numbers
    char replay_main;            // char variable to ask to replay game 

    welcomeMessage();       // Display what we wanted.

    do                      // do this while everything makes sense
    {
        // random numbers generated after this statement
        getLotteryNumbers(lotteryNumbers); 

        // get user input numbers
        getPlayerNumbers(playerNumbers);

        // sort out random lottery numbers
        sortNumbers(lotteryNumbers);

        // sort out user entered numbers
        sortNumbers(playerNumbers);

        // compare lottery numbers to users
        checkNumbers(lotteryNumbers, playerNumbers);

        // ask users if they want to play again
        replayGame(&replay_main);

        // while loop if they answer yes
    } while (replay_main == 'y' || replay_main == 'Y');

    // end game message if they answer no
    endGameMessage();

    return 0;
}

void welcomeMessage() 
{ cout << setw(45) << "Welcome to CS 202 Lottery!\n"; }

void endGameMessage() 
{ cout << setw(45) << "Thanks for playing!\n" << endl; }

/// @paragraph this function ask the user do you want to play again
void replayGame(char *replay)
{
    // prompt user if they want to play again
   cout << setw(51) << "Would you like to play again? (y/n) " << endl;   

   do   { cin >> *replay; cout << "Please enter yes or no: \n"; }
   while(*replay != 'y' && *replay != 'Y' && *replay != 'n' && *replay != 'N');
}

void getLotteryNumbers(int lotteryNumbers[]) 
{
    // set random numbers
    srand (time(0));    

    // store 5 numbers in the array
    for (int i = 0; i < 5; i++)
    {
        // random Number generator  
        lotteryNumbers[i] = (rand() % 10);

        // prevent duplicate numbers
        while (lotteryNumbers[i] == lotteryNumbers[i - 1])
               { lotteryNumbers[i] = (rand() % 10); }
    }
    
}

void getPlayerNumbers(int playerNumbers[]) 
{
    cout << "Enter 5 lottery numbers (0 - 9): " << endl;

    for (int i = 0; i < 5; i++) 
    {
        cin >> playerNumbers[i];

        while (playerNumbers[i] < 0 || playerNumbers[i] > 9)
            {
                cout << "Invalid number! " << endl;
                cout << "Please choose again ";
                cin  >> playerNumbers[i];
            }
    }
}


void sortNumbers(int sortNumbers[])
{
    int temp;

    for (int counter = 4; counter > 0; counter --)
    {
        for (int i = 0; i < 4; i++)
        {
            if (sortNumbers[i] > sortNumbers[i + 1])
                {
                    temp               = sortNumbers[i + 1];
                    sortNumbers[i + 1] = sortNumbers[i];
                    sortNumbers[i]     = temp;
                }
        }
    }
}

void checkNumbers(int lotteryNumbers[], int playerNumbers[])
{
    // Output Yes if found any match, no is opposite   
    string yes  = " YES ";
    string no   = " NO ";
    int counter = 0 ;

    // just a space 
    cout << endl;

    cout << "  Lottery Numbers ---------- Your Numbers ----------  Results" << endl;

    // run through loop compare 5 value 
    for (int i = 0; i < 5; i++)
    {
        if (lotteryNumbers[i] == playerNumbers[i] )
        {
            cout << setw(11) << lotteryNumbers[i] << setw(18)
                 << " ---------- " << setw(6) 
                 << playerNumbers[i] << setw(19) << " ---------- "
                 << setw(7) << yes << endl;
                 counter++;
        }
        else 
        {
            cout << setw(11) << lotteryNumbers[i] << setw(18)
                 << " ---------- " << setw(6) 
                 << playerNumbers[i] << setw(19) << " ---------- "
                 << setw(7) << no << endl;
        }
    }
    resultsMessage(counter);
}

void resultsMessage(int counter)
{
    cout << endl;
    if (counter == 5)
    {
        cout << setw(28) << "You got 5 numbers out of 5" << endl;
        cout << setw(41) << " YOU WIN (SORTA)!\n " << endl;
    }
    else 
    {
        cout << setw(28) << "You got " << counter << " numbers out of 5"
             << endl;
        cout << setw(41) << " YOU LOSE (SORTA)!\n " << endl;
    }
}
