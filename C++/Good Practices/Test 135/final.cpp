/// @file final.cpp
/// @author Thien Nguyen thiennguyen@student.csn.edu
/// @date 12/15/21
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This assignment reads and print the report
///        of 10 students performance accordingly
///
/// @note People who helped: None
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.

// include libs
#include <cmath>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <cstdlib>
#include <limits>
#include <fstream>

// setting a namcespace scope
using namespace std;

// global constants
const int SIZE = 10;

// enum type for the score of each students
enum test_score {test1, test2, test3, test4, test5, test_count};

// structure student_t
struct student_t {
    string name = "";                     // obtained from the data.txt file
    double test[test_count] = { 0 };      // obtained from the data.txt file
    double average = 0;                   // calculate the average by / 5
    char grade = '\0';                    // the grade of each student
};

/// -----------------------------------------------------------------------
/// Function Prototypes
/// -----------------------------------------------------------------------


student_t getdata(ifstream& fin);

char calculateGrade(double grade);

double calculateAverage(student_t dataSet[]);

int findMinAve(student_t dataSet[]);

int findMaxAve(student_t dataSet[]);

void process_all_data(const string& fn, student_t dataSet[]);

void printReport(const string& fn, student_t dataSet[]);

void printline();

void printheader();

void printdata(const string& fn, student_t dataSet[]);

void print_class_ave(student_t dataSet[]);

void print_poorest(int index, student_t dataSet[]);

void print_best(int index, student_t dataSet[]);

/// -----------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -----------------------------------------------------------------------
int main(int argc, const char *argv[]) {
    // array hold elements declared in main
    student_t data_set[SIZE];

    // input argumetn
    if (argc == 2) {
        // if enough argument, process the data
        printReport(argv[1], data_set);
    } else {
        // if not enough argument
        cout << "Usage " << argv[0] << " dataFile.txt" << endl;
    }

    // return to the operating system
    return EXIT_SUCCESS;
}

/// -----------------------------------------------------------------------
/// Function Implementations
/// -----------------------------------------------------------------------

/// -----------------------------------------------------------------------
/// Reads the input of 1 exact student
///
/// @param fin is the file streaming input variable
/// -----------------------------------------------------------------------
student_t getdata(ifstream& fin) {
    const char DEL = ' ';       // delimeter to seperate field
    student_t record;           // hold all value in struct each student
    double total = 0;

    // get the name of the student and ignore the space
    getline(fin, record.name, DEL);

    // get the score for 5 tests
    for (int i = 0; i < test_count; i++) {
        fin >> record.test[i];
        total += record.test[i];
    }

    // ignore the white space and \n after that
    fin.ignore(1, '\n');

    // calculating the average of one student
    record.average = total / 5;

    // assigning the letter grade to that student
    record.grade = calculateGrade(record.average);

    // return the record contain all information we just stored
    return record;
}

/// -------------------------------------------------------------------------
/// Reads all the input from the data.txt file
///
/// @param fn is the name of the file input
/// @param dataSet 10 set of data each contain the record for each student
///                in short - Array hold elements
/// -------------------------------------------------------------------------
void process_all_data(const string& fn, student_t dataSet[]) {
    ifstream fin;           // streaming variable handler
    fin.open(fn);           // open the file

    // if the file is open
    if (fin.is_open()) {
        // repeat 10 times - 10 record
        for (int i = 0; i < SIZE; i++) {
            dataSet[i] = getdata(fin);
        }

        // if open the wrong file name
    } else {
        cout << "FILE is NOT OPEN!";
        fin.close();
    }

    // close the stream / flush the buffer
    // so we won't get garbage information
    fin.close();
}

/// -------------------------------------------------------------------------
/// calculating the class average
///
/// @param dataSet 10 set of data each contain the record for each student
///                in short - Array hold elements
/// @return class average
/// -------------------------------------------------------------------------
double calculateAverage(student_t dataSet[]) {
    // to hold the total of 10 students
    double class_total = 0;

    // adding through loop
    for (int i = 0; i < SIZE; i++) {
        class_total += dataSet[i].average;
    }

    // return the class average
    return class_total / 10;
}

/// -------------------------------------------------------------------------
/// assigning the letter grade through each student grade
///
/// @param grade the average grade of each student
/// @return letter grade from A, B, C, D, to F.
/// -------------------------------------------------------------------------
char calculateGrade(double grade) {
    char letter_grade;

    // if else statements that distribute the letter grade
    // A grade from 90% to 100%
    if (grade <= 100 && grade >= 90) {
        letter_grade = 'A';
        
        // B grade from 80% to 89.99%
    } else if (grade < 90 && grade >= 80) {
        letter_grade = 'B';

        // C grade from 70% to 79.99%
    } else if (grade < 80 && grade >= 70) {
        letter_grade = 'C';

        // D grade from 60% to 69.99%
    } else if (grade < 70 && grade >= 60) {
        letter_grade = 'D';

        // F grade from 0% to 59.99%
    } else if (grade < 60 && grade >= 0) {
        letter_grade = 'F';

        // in case they witdrawal or false input
    } else {
        letter_grade = 'W';
    }

    // return the letter_grade
    return letter_grade;
}

/// -------------------------------------------------------------------------
/// print the line with 69 dashes
/// -------------------------------------------------------------------------
void printline() {
    // print 69 dashes
    cout << string(69, '-') << endl;
}

/// -------------------------------------------------------------------------
/// print the header of the ouput contain the heading the --- line
/// -------------------------------------------------------------------------
void printheader() {
    // print the straight line
    printline();
    // set to the left for Name
    cout << left << setw(10) << "Name";
    // set to the right for the rest of the information
    cout << right;
    cout
            << setw(8)  << "Test 1"
            << setw(8)  << "Test 2"
            << setw(8)  << "Test 3"
            << setw(8)  << "Test 4"
            << setw(8)  << "Test 5"
            << setw(10) << "Average"
            << setw(8)  << "Grade"
            << endl;

    // print the ---- line below of the header
    // set left for the name --- line
    cout << left << setw(10) << "-------";
    // set right for the rest
    cout << right;
    cout
            << setw(8)  << "------"
            << setw(8)  << "------"
            << setw(8)  << "------"
            << setw(8)  << "------"
            << setw(8)  << "------"
            << setw(10) << "-------"
            << setw(8)  << "-----"
            << endl;
}

/// -------------------------------------------------------------------------
/// print the data report after getting the input and calculating the average
/// and grade
/// @param fn the input file name
/// @param dataSet 10 set of data each contain the record for each student
///                in short - Array hold elements
/// -------------------------------------------------------------------------
void printdata(const string& fn, student_t dataSet[]) {
    ifstream fin;               // streaming variable
    fin.open(fn);               // open the file

    // if file is open
    if (fin.is_open()) {
        // repeat 10 time for 10 students
        for (int i = 0; i < SIZE; i++) {
            // print the name
            cout << left << setw(10) << dataSet[i].name;
            // the data of 5 test
            cout << right << setprecision(0) << fixed;
            cout
                    << setw(8)  << dataSet[i].test[0]
                    << setw(8)  << dataSet[i].test[1]
                    << setw(8)  << dataSet[i].test[2]
                    << setw(8)  << dataSet[i].test[3]
                    << setw(8)  << dataSet[i].test[4];
            // the average and the letter grade
            cout
                    << setprecision(2) << fixed
                    << setw(10) << dataSet[i].average
                    << setw(6)  << dataSet[i].grade << endl;
        }

        // if given the worng file
    } else {
        cout << "FILE IS NOT OPEN!" << endl;
        fin.close();
    }

    // data is already in the data set so we close the stream
    // flush the buffer
    fin.close();
}

/// -------------------------------------------------------------------------
/// print the class average and the 2 ---- line that made it look like a box
/// @param dataSet 10 set of data each contain the record for each student
///                in short - Array hold elements
/// -------------------------------------------------------------------------
void print_class_ave(student_t dataSet[]) {
    // hold value of the class_average
    double class_average;
    // print the ---- line
    printline();
    // calculating the class_average
    class_average = calculateAverage(dataSet);
    // print the result
    cout << "Class Average: "
         << setw(7) << class_average << endl;
    // print the ---- line again
    printline();
}

/// -------------------------------------------------------------------------
/// find the index lead to the person has the worse performance
/// @param dataSet 10 set of data each contain the record for each student
///                in short - Array hold elements
/// @return the index in the dataSet lead to the person has the lowest
///         average grade
/// -------------------------------------------------------------------------
int findMinAve(student_t dataSet[]) {
    int index = 0;              // iterator index
    double current;             // value 1
    double compare;             // value 2

    // loop through all the dataset member average to find the smallest
    for (int i = 0; i < SIZE; i++) {
        current = dataSet[index].average;
        compare = dataSet[i].average;

        // comparision
        if (compare < current) {
            index = i;
        }
    }

    // the index of the smallest average
    return index;
}

/// -------------------------------------------------------------------------
/// find the index lead to the person has the best performance
/// @param dataSet 10 set of data each contain the record for each student
///                in short - Array hold elements
/// @return the index in the dataSet lead to the person has the highest
///         average grade
/// -------------------------------------------------------------------------
int findMaxAve(student_t dataSet[]) {
    int index = 0;              // iterator index
    double current;             // value 1
    double compare;             // value 2

    // loop through all the dataset member average to find the smallest
    for (int i = 0; i < SIZE; i++) {
        current = dataSet[index].average;
        compare = dataSet[i].average;
        
        // comparision
        if (compare > current) {
            index = i;
        }
    }

    // the index of the highest average
    return index;
}

/// -------------------------------------------------------------------------
/// print the poorest performance
/// @param index the index of where the worst performance is
/// @param dataSet 10 set of data each contain the record for each student
///                in short - Array hold elements
/// -------------------------------------------------------------------------
void print_poorest(int index, student_t dataSet[]) {
    // print the result
    cout << "\nPoorest Performance:" << endl;
    printheader();

    // print the name
    cout << left << setw(10) << dataSet[index].name;
    // the data of 5 test
    cout << right << setprecision(0) << fixed;
    cout
            << setw(8)  << dataSet[index].test[0]
            << setw(8)  << dataSet[index].test[1]
            << setw(8)  << dataSet[index].test[2]
            << setw(8)  << dataSet[index].test[3]
            << setw(8)  << dataSet[index].test[4];
    // the average and the letter grade
    cout
            << setprecision(2) << fixed
            << setw(10) << dataSet[index].average
            << setw(6)  << dataSet[index].grade << endl;
    // print the ----- line
    printline();
    // the end of the output
    cout << endl;
}

/// -----------------------------------------------------------------------
/// print the best performance
/// @param index the index of where the best performance is
/// @param dataSet 10 set of data each contain the record for each student
///                in short - Array hold elements
/// -----------------------------------------------------------------------
void print_best(int index, student_t dataSet[]) {
    // print the result
    cout << "\nBest Performance:" << endl;
    printheader();
    // print the name
    cout << left << setw(10) << dataSet[index].name;
    // the data of 5 test
    cout << right << setprecision(0) << fixed;
    cout
            << setw(8)  << dataSet[index].test[0]
            << setw(8)  << dataSet[index].test[1]
            << setw(8)  << dataSet[index].test[2]
            << setw(8)  << dataSet[index].test[3]
            << setw(8)  << dataSet[index].test[4];
    // the average and the letter grade
    cout
            << setprecision(2) << fixed
            << setw(10) << dataSet[index].average
            << setw(6)  << dataSet[index].grade << endl;
    // print the ----- line
    printline();
}

/// -------------------------------------------------------------------------
/// print the full picture of the report
/// @param fn the name of the file
/// @param dataSet 10 set of data each contain the record for each student
///                in short - Array hold elements
/// -------------------------------------------------------------------------
void printReport(const string& fn, student_t dataSet[]) {
    // get all the data in the dataset
    process_all_data(fn, dataSet);

    // find the index of the worst and the best performance
    int worst;
    int best;
    worst = findMinAve(dataSet);
    best  = findMaxAve(dataSet);

    // print the Student Grade Report
    cout << "\nStudent Grade Report" << endl;
    printheader();
    printdata(fn, dataSet);
    print_class_ave(dataSet);
    print_best(best, dataSet);
    print_poorest(worst, dataSet);
}
