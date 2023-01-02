/// @file bitwise.cpp
/// @author Thien Nguyen
/// @brief Performs bitwise operations on two binary numbers of length n

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

#define ul "\033[4m"  // terminal command to underline
#define ule "\033[0m" // terminal command to end underline

string bitwiseAND(string num1, string num2);
string bitwiseOR(string num1, string num2);
string bitwiseXOR(string num1, string num2);

int main()
{
    string num1{};      // first binary number
    string num2{};      // second binary number
    string result{};    // the resulting binary number
    size_t oper;        // operation being performed
    bool error = false; // error flag (for invalid operation)

    // string representation of operation being performed
    const string symbol[] = {" AND ", " OR ", " XOR "};

    cout << "Enter first binary number: " << endl;
    cin >> num1;
    cout << "Enter second binary number (of same length): " << endl;
    cin >> num2;
    cout << "Enter bitwise operation (AND = 0, OR = 1, XOR = 2): " << endl;
    cin >> oper;

    switch (oper)
    {
    case 0:
        result = bitwiseAND(num1, num2);
        break;

    case 1:
        result = bitwiseOR(num1, num2);
        break;

    case 2:
        result = bitwiseXOR(num1, num2);
        break;

    default:
        // if it is any value other than 0-2, there's been an error
        error = true;
    }

    // spruce up the output with some decorative dashes
    cout << setw(30) << setfill('-') << "" << endl;

    // if there was no error, output the results. If there was, output an
    // informative error message.
    if (!error)
    {
        cout << num1 << "\n"
             << ul << num2 << ule << symbol[oper] << "\n";
        cout << result << endl;
    }
    else
    {
        cout << "Enter a valid bitwise operation!" << endl;
    }

    return EXIT_SUCCESS; // cheers!
}

/// @brief bitwiseAND
/// Performs bitwise AND operation on two binary numbers
///
/// @param  num1    first binary number
/// @param  num2    second binary number
/// @return result  result of bitwise operation
string bitwiseAND(string num1, string num2)
{
    string result{};

    // walk through both numbers, writing a 1 to result if BOTH numbers contain
    // a 1 in the current position
    for (size_t i = 0; i < num1.length(); ++i)
    {
        if (num1.at(i) == '1' && num2.at(i) == '1')
        {
            result += '1';
        }
        else
        {
            result += '0';
        }
    }

    return result;
}

/// @brief bitwiseOR
/// Performs bitwise OR operation on two binary numbers
///
/// @param  num1    first binary number
/// @param  num2    second binary number
/// @return result  result of bitwise operation
string bitwiseOR(string num1, string num2)
{
    string result{};

    // walk through both numbers, writing a 1 to result if EITHER numbers
    // contain a 1 in the current position
    for (size_t i = 0; i < num1.length(); ++i)
    {
        if (num1.at(i) == '1' || num2.at(i) == '1')
        {
            result += '1';
        }
        else
        {
            result += '0';
        }
    }

    return result;
}

/// @brief bitwiseXOR
/// Performs bitwise XOR operation on two binary numbers
///
/// @param  num1    first binary number
/// @param  num2    second binary number
/// @return result  result of bitwise operation
string bitwiseXOR(string num1, string num2)
{
    string result{};

    // walk through both numbers, writing a 1 to result if ONLY ONE number
    // contain a 1 in the current position
    for (size_t i = 0; i < num1.length(); ++i)
    {
        if (num1.at(i) != num2.at(i))
        {
            result += '1';
        }
        else
        {
            result += '0';
        }
    }

    return result;
}
