#include <iostream>   // cin and cout (keyboard input / screen output)
#include <iomanip>    // setprecision (formatting decimals)
#include <string>     // the string data type (text)
using namespace std;  // lets us write cout instead of std::cout
 
// ---------- CONSTANTS ----------
// "const" means the value can never change while the program runs.
const double BASIC_FEE = 220.00;       // Membership code 1
const double ACTIVE_FEE = 350.00;      // Membership code 2
const double COMPLETE_FEE = 480.00;    // Membership code 3
const double ASSESSMENT_FEE = 180.00;  // Once-off optional fitness assessment
const int MIN_MONTHS = 1;              // Fewest months allowed
const int MAX_MONTHS = 6;              // Most months allowed
 
int main()
{
    // ---------- 1. DECLARE ALL VARIABLES ----------
    // Student details
    string studentNumber;      
    string studentName;        
 
    // Membership choice
    int code = 0;              // Membership code typed by the user (1, 2 or 3)
    string membershipName;     // Name printed on the quotation
    double monthlyFee = 0.0;   // Fee for the chosen membership
 
    // Registration details
    int months = 0;            // Number of months (1 to 6)
    char answer = ' ';         // Y or N for the fitness assessment
    double assessment = 0.0;   // Assessment charge added (R180 or R0)
 
    // Calculation results
    int discountPercent = 0;   // Whole-number discount percentage (12, 7 or 0)
    double subtotal = 0.0;     // Monthly fee x months
    double discount = 0.0;     // Rand value of the discount
    double finalAmount = 0.0;  // Amount the student must pay
 
    // ---------- 2. CAPTURE STUDENT DETAILS ----------
    cout << "Student number: ";
    getline(cin, studentNumber);   // getline reads the WHOLE line (including spaces)
    cout << "Student name: ";
    getline(cin, studentName);     // needed because names contain spaces
 
    // Validation: .empty() is true if nothing was typed.
    // || means OR: error if EITHER field is empty.
    if (studentNumber.empty() || studentName.empty())
    {
        cout << "ERROR: Student number and name cannot be empty." << endl;
        return 1;   // Stop the program. 1 means "ended with an error"
    }
 
    // ---------- 3. DISPLAY MENU AND ACCEPT SELECTION ----------
    cout << endl;
    cout << "1. Basic Access - R220" << endl;
    cout << "2. Active Plus - R350" << endl;
    cout << "3. Complete Wellness - R480" << endl;
    cout << "Select membership: ";
 
    // If the user types letters, cin >> code fails. ! means NOT,
    // so the error shows when the read did not succeed.
    if (!(cin >> code))
    {
        cout << "ERROR: Membership code must be a number (1, 2 or 3)." << endl;
        return 1;
    }
 
    // ---------- 4. DETERMINE MONTHLY FEE (control structure) ----------
    // if / else if checks the code against each membership in turn.
    // The first condition that is true runs; the rest are skipped.
    if (code == 1)                  // == means "is equal to" (a single = would assign!)
    {
        membershipName = "Basic Access";
        monthlyFee = BASIC_FEE;     // R220.00
    }
    else if (code == 2)
    {
        membershipName = "Active Plus";
        monthlyFee = ACTIVE_FEE;    // R350.00
    }
    else if (code == 3)
    {
        membershipName = "Complete Wellness";
        monthlyFee = COMPLETE_FEE;  // R480.00
    }
    else                            // none of 1, 2 or 3 matched = invalid code
    {
        cout << "ERROR: Invalid membership code. Choose 1, 2 or 3." << endl;
        return 1;                   // Do not continue with an invalid quotation
    }
 
    // ---------- 5. CAPTURE AND VALIDATE MONTHS ----------
    cout << "Number of months (1-6): ";
 
    // First check: was a number typed at all?
    if (!(cin >> months))
    {
        cout << "ERROR: Months must be a whole number between 1 and 6." << endl;
        return 1;
    }
    // Second check: is the number inside the allowed range?
    if (months < MIN_MONTHS || months > MAX_MONTHS)
    {
        cout << "ERROR: Months must be between 1 and 6." << endl;
        return 1;
    }
 
    // ---------- 6. CAPTURE AND VALIDATE FITNESS ASSESSMENT ----------
    cout << "Add fitness assessment? (Y/N): ";
    cin >> answer;
    answer = toupper(answer);   //
 
    if (answer == 'Y')          // Yes: charge the R180 fee
    {
        assessment = ASSESSMENT_FEE;
    }
    else if (answer == 'N')     // No: add nothing (R0 keeps the final formula simple)
    {
        assessment = 0.00;
    }
    else                        // Anything else is invalid input
    {
        cout << "ERROR: Please answer Y or N for the fitness assessment." << endl;
        return 1;
    }
 
    // ---------- 7. DISCOUNT PERCENTAGE ----------
    // ORDER MATTERS: 6 months is checked first, otherwise it would
    // match "months >= 3" and wrongly receive only 7%.
    if (months == 6)
    {
        discountPercent = 12;   // Exactly 6 months = 12%
    }
    else if (months >= 3)
    {
        discountPercent = 7;    // 3, 4 or 5 months = 7%
    }
    else
    {
        discountPercent = 0;    // 1 or 2 months = no discount
    }
 
    // ---------- 8. CALCULATIONS (required formulae) ----------
    // Subtotal = Monthly Fee x Number of Months
    subtotal = monthlyFee * months;
 
    // Discount = Subtotal x discount percentage
    // (100.0 with a decimal point forces decimal, not whole-number, division)
    discount = subtotal * discountPercent / 100.0;
 
    // Final Amount = Subtotal - Discount + Optional Assessment Fee
    finalAmount = subtotal - discount + assessment;
 
    // ---------- 9. DISPLAY THE QUOTATION ----------
    // fixed + setprecision(2) = always show exactly 2 decimal places
    cout << fixed << setprecision(2);
    cout << endl;
    cout << "========== VUKAFIT MEMBERSHIP QUOTATION ==========" << endl;
    cout << "Student     : " << studentNumber << " - " << studentName << endl;
    cout << "Membership  : " << membershipName << endl;
    cout << "Months      : " << months << endl;
    cout << "Monthly Fee : R" << monthlyFee << endl;
    cout << "Subtotal    : R" << subtotal << endl;
    cout << "Discount    : R" << discount << " (" << discountPercent << "%)" << endl;
    cout << "Assessment  : R" << assessment << endl;
    cout << "FINAL AMOUNT: R" << finalAmount << endl;
 
    return 0;  
}
 