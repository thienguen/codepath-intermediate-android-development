/*
    This program gives the user the option to choose between using a
    calculator that works given 2 numbers, or taking an anime quiz.

    The expected input of this program is different characters depending
    on how the user wants to answer the questions being asked, and for
    the calculator potion, the user must also input 2 number values
    to be ran through the different operations the calcuator provides.

    The expected output of the program is either the calculations of the
    2 numbers and their operation you assign them to run through, or the
    result of your acceptance into the weeb anime club.
*/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main() {
    char userInput;

    cout << "Enter Which Program You Wish To Run:\n"
         "A: Calculator\n"       // prompts user to type in these characters
         "Q: Quiz\n";            // in order to choose between the Calculator
    cout << "What will be yor choice? ";
    cin  >> userInput;            // or the Quiz

    if (userInput == 'A') {       // calculator portion of the program
        float num1;
        float num2;
        char calcInput;          // declared a separate variable for calculator
        // input specifically
        cout << "\nRunning Calculator\n" << "Enter First Number: ";
        cin  >> num1;
        cout << "Enter Second Number: ";
        cin  >> num2;

        // after input this tell us ay 
        cout << "Enter operation to perform from list:\n"
             << "A: Addition\n"
             << "S: Subtratction\n"
             << "M: Multiplication\n"
             << "D: Division\n"
             << "P: Power\n"
             << "C: Comparison\n"
             << "O: Modulus\n\n";

        // user options
        cin  >> calcInput;

        // simple math
        if (calcInput == 'A') { cout << num1 << " + " << num2 << " = " << (num1 + num2) << endl; }
        
            else if (calcInput == 'S') { cout << num1 << " - " << num2 << " = " << (num1 - num2) << endl; }

            else if (calcInput == 'M') { cout << num1 << " x " << num2 << " = " << (num1 * num2) << endl; }

            else if (calcInput == 'D') 
            {
                if (num2 == 0) { cout << "Division by Zero Detected. Aborting!" << endl; return -1; }
                    else { cout << num1 << " / " << num2 << " = " << (num1 / num2) << endl; }
            }
                //if 2nd number is 0, it'll terminate the program bc anything divded by 0 is und

            else if (calcInput == 'P') 
            {
                if ((num1 == 0) && (num2 < 0)) { cout << "Division by Zero Detected. Aborting!" << endl; return -1; }
                    else { cout << num1 << " ^ " << num2 << " = " << (pow(num1,num2)) << endl; }
            }
                            // 0 to the power of a negative number is also UB
                            //pow function takes the second number as the exponent

            else if (calcInput == 'C') 
            {
                if (num1 > num2)          { cout << num1 << " is greater than " << num2 << endl; }
                    else if (num1 < num2) { cout << num1 << " is less than "    << num2 << endl; }
                        else              { cout << num1 << " is equal to "     << num2 << endl; }
            }

            else if (calcInput == 'O') 
                { cout << num1 << " mod " << num2 << " = " << (static_cast<int>(num1)) % (static_cast<int>(num2)) << endl; } 
                    else { cout << "The inverse of " << num1 << " is " << -num1 << endl; }       

                        // we use static_cast to type cast num1 and num2 out of their
                        // float data types, and convert them into integers so modulus can work
                        // putting a negative(-) in front of a value will inverse it
    }
        else if (userInput == 'Q') 
        {
            char quizInput;    //specific variable for quiz input
            int  quizScore = 0; //keeps track of the user's score on the quiz

            cout << "Running Quiz\n"
                << "Hello there, Welcome to the Automated Anime Club Test,\n"
                << "Please Answer each Question with a Y for Yes, and N for No.\n\n"
                << "Do you agree that Japanese animation are nothing more than "
                << "cartoons?\n";
                                cin  >> quizInput;

            if (quizInput == 'Y') { quizScore = quizScore - 5; }
                else if (quizInput == 'N') { quizScore = quizScore + 5; }

            cout << "Can you tell when people are speaking Japanese? ";
                                cin  >> quizInput;

            if (quizInput == 'Y') {quizScore = quizScore + 5; }
                else if (quizInput == 'N') { quizScore = quizScore - 5; }

            cout << "Do you hate body pillows? ";
                                cin >> quizInput;
            if (quizInput == 'Y') { quizScore = quizScore - 5; }
                else if (quizInput == 'N') { quizScore = quizScore + 5; }

            cout << "Have you seen the toothbrush scene? ";
                                cin >> quizInput;
            if (quizInput == 'Y') { quizScore = quizScore + 5; }
                else if (quizInput == 'N') { quizScore = quizScore - 5; }

            cout << "Did you ever hear the tragedy of Darth Plagueis The Wise? ";
                                cin >> quizInput;

            cout << "\n\"I thought not. It's not a story the Jedi would tell you. It's a Sith\n"
                << "legend. Darth Plagueis was a Dark Lord of the Sith, so powerful and\n"
                << "so wise he could use the Force to influence the midichlorians to\n"
                << "create life... He had such a knowledge of the dark side that he could\n"
                << "even keep the ones he cared about from dying. The dark side of the\n"
                << "Force is a pathway to many abilities some consider to be unnatural.\n"
                << "He became so powerful... the only thing he was afraid of was losing\n"
                << "his power, which eventually, of course, he did. Unfortunately, he\n"
                << "taught his apprentice everything he knew, then his apprentice killed\n"
                << "him in his sleep. It's ironic he could save others from death, but\n"
                << "not himself.\"\n\n"
                << "Is it possible to learn this power? ";
                                cin >> quizInput;

            cout << "Do you own anything imported from Japan excluding Cameras and\n" << "watches? ";
                                cin >> quizInput;
                                
            if (quizInput == 'Y') { quizScore = quizScore + 5; }
                else if (quizInput == 'N') { quizScore = quizScore - 5; }

            cout << "Do you use or watch \"bleach\"? Answer U for use, W for watch)\n ";
                                cin >> quizInput;

            if (quizInput == 'U') { quizScore = quizScore - 5; }
                else if (quizInput == 'W') { quizScore = quizScore + 5; }

            // To show the score is positive but not a perfect score
            if (quizScore > 0 && quizScore < 30) { cout << "Congratulations. You are in this council, but we do not grant you the\n" << "rank of Master.\n"; }
                else if(quizScore <= 0) { cout << "You are a traitor and spy, begone!\n"; }
                    else if(quizScore == 30) { cout << "Oni Chan? You are hereby granted Club President!\n"; }
        }
            else { cout << "Invalid Entry, Goodbye!" << endl; }
    return 0;
}
