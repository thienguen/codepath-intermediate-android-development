/// @date 4/14/21
/// @note I pledge my word of honor that I have abided by the
/// the CSN Academic Integrity Policy while completing this assignment.

// include i/o libs
#include <iostream>
#include <iomanip>

using namespace std;

// Rock, paper, scissors function enumeration
enum objectType{ROCK, PAPER, SCISSORS};

/// -----------------------------------------------------------------------
/// Function Prototypes
/// -----------------------------------------------------------------------
// Rock Paper Scissors
void rockPaperScissors();
void displayRules();
objectType retrievePlay(char selection);
bool validSelection(char selection);
void convertEnum(objectType object);
objectType winningObject(objectType play1, objectType play2);
void gameResult(objectType play1, objectType play2, int& winner);
void displayResults(int gCount, int wCount1, int wCount2);

// Chapter 08
void scoresOne();
void scoresExample8_4();

/// -----------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -----------------------------------------------------------------------
int main() {

    // run the Rock, Paper, Scissors Game
    rockPaperScissors();

    // run the first scores example (no array)
    scoresOne();
    // run the second scores example (uses arrays)
    scoresExample8_4();
    return  EXIT_SUCCESS;
}

/// -----------------------------------------------------------------------
/// Function Implementations
/// -----------------------------------------------------------------------

/// @brief The function rockPaperScissors()
///        Runs the game of Rock, Paper, Scissors
///
/// @see page 478 of the text
void rockPaperScissors() {
    int gameCount;      // holds games played
    int winCount1;      // holds games won by player 1
    int winCount2;      // holds games won by player 2
    int gamewinner;     // holds who won the game
    char response;      // holds user response to play the game
    char selection1;    // holds player one's selection
    char selection2;    // holds player two's selection
    objectType play1;   // enumerated player1's selection
    objectType play2;   // enumerated player2's selection

    // Initialize variables
    gameCount = 0;
    winCount1 = 0;
    winCount2 = 0;

    // Let user see the rules
    displayRules();

    // Prompt to play game
    cout << "Enter Y/y to play the game: ";
    cin >> response;
    cout << endl;

    // Play game
    while (response == 'Y' ||  response == 'y')
    {
        // get player one's choice
        cout << "Player 1 enter your choice: ";
        cin >> selection1;
        cout << endl;

        // get player two's choice
        cout << "Player 2 enter your choice: ";
        cin >> selection2;
        cout << endl;

        // validate player selections and play if valid
        if (validSelection(selection1) && validSelection(selection2)) {
            play1 = retrievePlay(selection1);
            play2 = retrievePlay(selection2);

            // update the number of games played
            gameCount++;

            // get the results of the play
            gameResult(play1, play2, gamewinner);

            // update winner count
            if (gamewinner == 1) {
                winCount1++;
            } else {
                winCount2++;
            }
        }

        // ask user if they want to play the game again
        cout << "Enter Y/y to play the game: ";
        cin >> response;
        cout << endl;
    }

    // display the results of all the games played
    displayResults(gameCount, winCount1, winCount2);
}

/// @brief The function displayRules() is used by
///        rockPaperScissors to display the game rules
///
/// @see page 480 of the text
void displayRules() {
cout << "  Welcome to the game of Rock, Paper, "
    << "and Scissors." << endl;
    cout << "  This is a game for two players. For each "
    << "game, each" << endl;
    cout << " player selects one of the objects, Rock, "
    << "Paper or Scissors." << endl;
    cout << " The rules for winning the game are: " << endl;
    cout << "1. If both players selects the same object, it "
    << "is a tie." << endl;
    cout << "2. Rock breaks Scissors: So player who selects "
    << "Rock wins." << endl;
    cout << "3. Paper covers Rock: So player who selects "
    << "Paper wins." << endl;
    cout << "4. Scissors cuts Paper: So player who selects "
    << "Scissors wins." << endl << endl;
    cout << "Enter R or r to select Rock, P or p to select "
    << "Paper, and S or s to select Scissors." << endl;
}

/// @brief The function validSelection checks whether a player’s
/// selection is valid.
///
/// @param selection is the selection value to be tested
/// @return true if valid selection
///
/// @see page 480
bool validSelection(char selection)
{
    bool isValid = false;
    switch (selection)
    {
        case 'R':
        case 'r':
        case 'P':
        case 'p':
        case 'S':
        case 's':
            isValid = true;
            break;
        default:
            isValid = false;
            break;
    }
    return isValid;
}

/// @brief The function retrievePlay converts the
///        entered choice (R, r, P, p, S, or s) and returns
///        the appropriate object type.
///
/// @param selection is the value to be enumerated
/// @return enumerated equilivant to selected choice
///
/// @see page 481
objectType retrievePlay(char selection)
{
    objectType object = ROCK;

    switch (selection)
    {
        case 'R':
        case 'r':
            object = ROCK;
            break;
        case 'P':
        case 'p':
            object = PAPER;
            break;
        case 'S':
        case 's':
            object = SCISSORS;
            break;
        default:
            break;
    }

    return object;
}

/// @brief The function convertEnum outputs the text version of
/// the enumeration value.
///
/// @param object is the enumerated value to be converted to text output
///
/// @see page 483
void convertEnum(objectType object)
{
    switch (object)
    {
        case ROCK:
            cout << "Rock";
            break;
        case PAPER:
            cout << "Paper";
            break;
        case SCISSORS:
            cout << "Scissors";
            break;
        default:
            break;
    }
}

/// @brief The function winningObject determines the winning object.
///
/// @param play1 is the player one selected object
/// @param play2 is the player two selected object
///
/// @return the winning object
///
/// @see page 484
objectType winningObject(objectType play1, objectType play2) {

    objectType win = ROCK;                              // holds winning object

    if ((play1 == ROCK && play2 == SCISSORS)            // test for ROCK winner
        || (play2 == ROCK && play1 == SCISSORS)) {
        win = ROCK;
    } else if ((play1 == ROCK && play2 == PAPER)        // test for PAPER winner
             || (play2 == ROCK && play1 == PAPER)) {
        win = PAPER;
    } else {
        win = SCISSORS;                                // SCISSORS winner
    }
    return win;
}

/// @brief The function gameResult outputs the results of a game.
///
/// @param play1 is the player one selected object
/// @param play2 is the player two selected object
/// @param [out] winner is the player win counter
///
/// @see page 482
void gameResult(objectType play1, objectType play2, int& winner) {
    objectType winnerObject;

    // test for tie and print results
    if (play1 == play2) {
        winner = 0;
        cout << "Both players selected ";
        convertEnum(play1);
        cout << ". This game is a tie." << endl;
    } else {
        winnerObject = winningObject(play1, play2);

        // Output each player's choice
        cout << "Player 1 selected ";
        convertEnum(play1);
        cout << " and player 2 selected ";
        convertEnum(play2);
        cout << ". ";

        // Decide the winner
        if (play1 == winnerObject) {
            winner = 1;
        } else {
            winner = 2;
        }

        // Output the winner
        cout << "Player " << winner << " wins this game."
        << endl;
    }
}

/// @brief The function displayResults outputs the results of all games.
///
/// @param gCount is the number of games played
/// @param wCount1 is the number of wins: player one
/// @param wCount2 is the number of wins: player two
///
/// @see page 484
void displayResults(int gCount, int wCount1, int wCount2) {
    cout << "The total number of plays: " << gCount << endl;
    cout << "The number of plays won by player 1: " << wCount1 << endl;
    cout << "The number of plays won by player 2: " << wCount2 << endl;
}

/// @brief The function scoresOne()
///        Text implementation: Accepts 5 integer scores, finds their average
///        and prints the relationship between the average and each
///        score.
///
/// @see page 522 of the text
void scoresOne() {

    // variables to hold scores inputted by user
    int test0;
    int test1;
    int test2;
    int test3;
    int test4;
    double average;         // calculated average of test scores

    /* Input Phase */

    // gather input from user
    cout << "Enter five test scores: ";
    cin >> test0 >> test1 >> test2 >> test3 >> test4;
    cout << endl;

    /* Processing Phase */

    // calculate the average of the scores
    average = static_cast<double>(test0 + test1 + test2 + test3 + test4) / 5.0;

    /* Output Phase */

    // set output formatting
    cout << fixed << showpoint << setprecision(2);

    // print report
    cout << "The average test score = " << average << endl;
    if (test0 < average) {
        cout << test0 << " is less than the average "
        << "test score." << endl;}
    if (test1 < average) {
        cout << test1 << " is less than the average "
        << "test score." << endl;}
    if (test2 < average) {
        cout << test2 << " is less than the average "
        << "test score." << endl;}
    if (test3 < average) {
        cout << test3 << " is less than the average "
        << "test score." << endl;}
    if (test4 < average) {
        cout << test4 << " is less than the average "
        << "test score." << endl;}
}

/// @brief The function scoresExample8_4()
///        Array version:
///        Accepts 5 integer scores, finds their average
///        and prints the relationship between the average and each
///        score.
void scoresExample8_4() {
    int test[5];                // scores inputted by user
    int sum = 0;                // accumulator
    double average;             // calculated average of scores
    int index;                  // tracks location in array

    /* Input Phase */

    // gather input from user and accumulate total
    cout << "Enter five test scores: ";
    for (index = 0; index < 5; index++) {
        cin >> test[index];
    }
    cout << endl;

    /* Processing Phase */

    // find the total accumulated score
    for (index = 0; index < 5; index++) {
        sum += test[index];
    }

    // calculate the average
    average = sum / 5.0;

    /* Output Phase */

    // set output formatting
    cout << fixed << showpoint << setprecision(2);

    // print report
    for (index = 0; index < 5; index++) {
        if (test[index] < average) {
            cout << test[index] << " is less than the average " << "test score."
            << endl;
        }
    }
}
