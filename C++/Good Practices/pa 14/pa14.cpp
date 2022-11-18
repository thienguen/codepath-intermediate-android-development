/// @file "pa14.cpp"
/// @author Thien Nguyen thiennguyen@.csn.edu
/// @date 3/11/22
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This assignment stimulate a lottery game
/// @note People who helped:
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.

/// include libs, I have everything within powa now
#include <iostream>
#include <ostream>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <iomanip>
#include "Container.hpp"
#include "ansi.hpp"

using namespace std;

// function protypes

void welcomeMessage();

void endGameMessage();

void getLotteryNumbers(Container<int>& lottery);

void getPlayerNumbers(Container<int>& player);

void compare(Container<int>& lottery, Container<int>& number);

void winningmessage(Container<int>& lottery, Container<int>& number);

void sortNumbers(Container<int>& array);

void soclose(int count);

void replayGame(string *replay);

int main()
{

    // set up srand;
    srand(time(0));
    
    // variable declartions(s)
    string replay_main;           // char variable initialize the gaem

    do
    {
        // declare our variable
        Container<int> lottery;   // array to store random lottery numbers
        Container<int>    user;   // array to store user numbers

        // welcome player to our game
        welcomeMessage();

        getLotteryNumbers(lottery);

        /// @paragraph if you want to
        /// see the winning meassaage
        /// ================
        // lottery.push_back(0);
        // lottery.push_back(1);
        // lottery.push_back(3);
        // lottery.push_back(4);
        // lottery.push_back(5);

        // user.push_back(0);
        // user.push_back(1);
        // user.push_back(3);
        // user.push_back(4);
        // user.push_back(5);
        /// =================

        getPlayerNumbers(user);

        compare(lottery, user);

        // ask if the user want to play again
        replayGame(&replay_main);

        // condition to play the game 1 more time
    } while (replay_main == "y" || replay_main == "Y");

    // gud-bye
    endGameMessage();

    // return to the operating system
    return 0;
}

        /// =============================================== ///
        /// @paragraph user-defined function(s) definition; ///
        /// =============================================== ///

/// @paragraph this function welcome the user to our mini game
void welcomeMessage() { cout << setw(50) << "Welcome to CS 202 Lottery!\n"; }

/// @paragraph This function say good bye to our player
void endGameMessage()
    { cout << setw(50) << "\nThanks for playing! been a long day\n" << endl; }

/// @paragraph this generated a random lottery ticket
/// @param lottery generated randomly by our computer lottery ticket
void getLotteryNumbers(Container<int>& lottery)
{
    // do it until we have a proper array
    while (lottery.size() < 5 )
    {
        // randomize our value
        int random = std::rand() % 10;

        // if not found any duplicate value, add it in
        if (lottery.find(random, lottery.begin()) == lottery.end())
                    { lottery.push_back(random); }
    }
}

/// @paragraph This function promtp the user for input bro
/// @param playerNumber[] We enter the intput to guess lottery
void getPlayerNumbers(Container<int>& player)
{
    // run 5 time to get 5 differnt input
    cout << "Enter 5 unique lottery numbers (0 - 9): ";
    int count = 0;
    while (player.size() < 5 && count != 5 ) 
    {
        // holding temporary
        int temp;
        // the input we do be check in
        cin  >> temp;
        // if not found ( --> end()), and within range, get it in
        if (player.find(temp, player.begin()) == player.end()
                     && temp >= 0 && temp <= 9)
        {
            player.push_back(static_cast<int>(temp));
            cout << "\nYour current input is " << player << " ";
            if (cin.fail()) 
            {
                // if user entered something not a character at all
                // you can use cin.good() but we can chill
                --count;
                player.erase(player.end() - 1);
                cin.clear();
                cin.ignore(256, '\n');
                cout << "\nYou entered something horrible didn't you"
                     << " please choose again: ";
            }
        }
                else 
                {
                    // they entered something inhuman
                    cout << "\nThat's an invalid number (duplicate or"
                        << " out of range bro), please choose again" << endl;
                    cout << "\nYour input so far is " << player
                        << " We need 5 valid argument tho: ";
                }
    }
        // make sure it's enough argument for our game
    

    // see if this clear the screen
    cout << "\033[2J\033[1;1H";
}

/// @paragraph This compare two array to get the exact result of our game
/// @param lottery the array of our generated function
/// @param number  the array of our user guessed
void compare(Container<int>& lottery, Container<int>& number)
{
    // count for how much we get in similarity
    int counter = 0;

    // if they are equal to each other, absolutely then you won the game
    if (lottery == number)
    {
        winningmessage(lottery, number);
        cout << "\n     Congratulations! You won the lottery,";
        cout << " your prize is $10,000\n";
    } else {
        // if you didn't get them all

        // find number exists? if they do be in the array
        for (int i = 0; i < 5; i++)
        {
            if (lottery.find(number[i], lottery.begin()) != lottery.end())
                                { counter++; }
        }

        // showing result
        cout << "The lottery ticket is: " << lottery << endl;
        cout << "Your guesses is:       " << number  << endl;
        cout << "\n The result after this will be sor";
        cout << "ted make it easier for programmer"  << endl;

        // functioon called to help our message deliver
        // std::sort(lottery.begin(), lottery.end());
        // std::sort(lottery.begin(), lottery.end());

        sortNumbers(lottery);
        sortNumbers(number);
        // deliver our message
        winningmessage(lottery, number);
        soclose(counter);
    }
}

/// @paragraph This function just format our end-game scenario
/// @param lottery take in our generated lottery ticket
/// @param number  take in our inputs/ guesses from the users
void winningmessage(Container<int>& lottery, Container<int>& number)
{
        string yes  = " YES ";
    //  string no   = " NO ";
    //  int counter = 0 ;

    cout << ansi::yellow << "\n   Lottery Number ----------  Your Number  ";
    cout << "----------    Results\n" << ansi::reset;

    // run through loop to see our value matched or not values
    for (int i = 0; i < 5; i++)
    {
        if (lottery.find(number[i], lottery.begin()) != lottery.end())
        {
            cout << setw(11) << number[i]
                 << setw(8)  << ansi::green << " ---------- " << ansi::reset
                 << setw(6)  << number[i]
                 << setw(9)  << ansi::green << " ---------- " << ansi::reset
                 << setw(7)  << ansi::green << yes << ansi::reset << endl;
                 // counter++;
        }
        // else
        // {
        //     cout << setw(11) << lottery[i]
        //          << setw(18) << " ---------- "
        //          << setw(6)  << number[i]
        //          << setw(19) << " ---------- "
        //          << setw(7)  << ansi::red << no << ansi::reset << endl;
        // }
    }
}

void soclose(int count)
{
    // if we have 5 similar number but not the same order
    if (count == 5)
    {
        cout << "\nCongratulations: You matched 5 un-order digits"
             << " your prize is $3,000\n";
    }
    // if we have 4 similar number but not the same order
    else if (count == 4)
    {
        cout << "\nCongratulations: You matched 4 un-order digits"
             << " your prize is $500\n";
    }
    // if we are unlucky, trials and errors
    else
    {
        cout << setw(23) << ansi::red << "You get " << count
             << " out of 5 numbers" << ansi::reset
             << "\n         but no worries, you still have infinite chances\n";
    }
}

void replayGame(string *replay)
{
    // prompt user if they want to play again
    cout << setw(53) << "Would you like to play again? (y/n): ";

    do {
        // get input
        cin >> *replay;

        // format-wise
        if (*replay != "y" && *replay != "Y" && *replay != "n"
                        && *replay != "N")
            { cout << "Pretty please enter y/n: "; }

        // clear screen to restart game
        if (*replay == "y" || *replay == "Y")
            { cout << "\033[2J\033[1;1H"; }

        // conditions to replay gaem
    } while (*replay != "y" && *replay != "Y" &&
             *replay != "n" && *replay != "N");
}

/// @paragraph   I use std::sort but I created this just in case
/// @param array take in the array we wanted to sort
void sortNumbers(Container<int>& array)
{
    // temp variable
    int temp;

    // this is a increasing order so this should be it
    for (int counter = array.size() - 1; counter > 0; counter--)
    {
        // the loop start from here
        for (int i = 0; i < array.size() - 1; i++)
        {
            // simple math
            if (array[i] > array[i + 1])
            {
                temp         = array[i + 1];
                array[i + 1] = array[i];
                array[i]     = temp;
            }
        }
    }
    // we should receive a sorted array, but I use std::sort
}

//// questions?

//// @paragraph user.find ask this memory allocation derivatao

///. @paragraph ask about why const put in function won't work in

///  chance of winning message
