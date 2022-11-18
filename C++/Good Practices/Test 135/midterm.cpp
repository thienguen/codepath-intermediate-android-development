/// @file midterm.cpp
/// @author Thien Nguyen THIEN.NGUYEN@csn.edu
/// @date 10/21/2021
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This program accept input as loan amount, interest rate
///        and the monthly payment to calculate how long it would 
///        take to repay the loan.
///
/// @note People who helped me: None


// include i/p libs
#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>

// setting up the namespace scope
using namespace std;

/// -----------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for valid date, else 1.
/// -----------------------------------------------------------------------

int main() { 
    
    // variables declaration(s)
    bool  valid = false;            // return 1 or 0
                                    // when program excecute   
    float interest_rate;            // interest rate per year
    float monthly_interest;         // interest rate per month        
    float monthly_interest_pay;     // interest we pay each month
    float monthly_payment;          // how much we pay each month
    float loan_amount;              // the principle loan
    float origin_loan;              // hold the value of the principle
    float actual_payment;           // after deduction 
                                    // of the monthly interest
    float total_interest;           // accumulated interest
    int total_month;                // months count


    /* ******* input phase ********************************************** */
    // Get input - loan amount, interest rate, and monthly payment
     cout << "Enter the loan amount: ";
     cin >> loan_amount;
     origin_loan = loan_amount;

     cout << "Enter the interest rate per year: ";
     cin >> interest_rate;
     monthly_interest = ((interest_rate / 12) / 100);

     cout << "Enter the monthly payment: ";
     cin >> monthly_payment;
     cout << endl;

     /* ******* processing phase ***************************************** */
     // assign the value for month count and accumulated interest
     total_month = 0;
     total_interest = 0;

    // precal monthly interest pay to compare with monthly payment
    monthly_interest_pay = loan_amount * monthly_interest;

    // set up the conditions
     if (monthly_payment < monthly_interest_pay) {
          cout << "Sorry, you have to have a minimum payment of: " 
          << setprecision(2) << fixed << monthly_interest_pay << " per month."
          << '\n';
          valid = true;
     } else {
          while (loan_amount > 0) {
          // repeat the calculating process until we paid off the loan
          actual_payment = monthly_payment - monthly_interest_pay;
          loan_amount -= actual_payment;
          total_month++;
          total_interest += monthly_interest_pay;
          monthly_interest_pay = loan_amount * monthly_interest;
          }

     /* ******* output phase *************************************************/
          // Success input first row
          cout << setw(25) << right << "Original Loan Amount: ";
          cout << setw(10) << right << setprecision(2) << fixed 
               << origin_loan 
               << '\n';

          // Success input second row
          cout << setw(25) << right << "Yearly Interest: ";
          cout << setw(10) << right << setprecision(2) << fixed << interest_rate 
               << setw(2)  << right  << "%" 
               << '\n';

          // Success input third row
          cout << setw(25) << right << "Payment: ";
          cout << setw(10) << right << setprecision(2) << fixed 
               << monthly_payment 
               << '\n' << endl;;

          // Success input fourth row
          cout << setw(25) << right << "Total interest paid: ";
          cout << setw(10) << right << setprecision(2) << fixed 
               << total_interest 
               << '\n' << endl;

          // Final row
          // years and no months
          if (total_month % 12 == 0) {
               cout << "The loan will be paid off in: " << total_month 
                    << " months,"
                    << '\n';
               cout << "which is " << (total_month / 12) <<  " years.";
          // years with remaining months
          } else {
               cout << "The loan will be paid off in: " << total_month 
                    << " month," 
                    << '\n';
               cout << "which is " << (total_month / 12) << " years and "
                    << (total_month % 12) << " months."
                    << '\n'; 
          }
     }
cout << monthly_interest;
    // return to the OS
    return static_cast<int>((valid) ? 0 : 1);
}
