/**
 * Name: Andrew Vattuone
 * Program Description:
 *      User inputs a 10-digit number. Number must be exaclty 10 digits or it will return an error.
 *      A reversed number is created, and using the original number and the reversed number, a pattern of 5 rows with the original and reversed number is displayed.
 *      Each successive row is 2 spaces to the right of the original row (which is 10 spaces to the right of the left edge of the terminal output window)
 *
 * School ID: 7700000354
 * Contact Info (Optional): avattuone@scu.edu
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
using namespace std;

int main()
{
    cout << "Enter 10 digits (no whitespace):" << endl;
    string inputNum;
    cin >> inputNum;
    // returns an error if the inputted number doesn't have exaclty 10 digits
    assert(inputNum.length() == 10);
    // reversedNum declared as a string so it can be reversed easier
    string reversedNum;

    // creates the reversed number by starting at the end of inputNum and adding each of its digits to the end of reversedNum
    for (int i = 0; i < inputNum.length(); i++)
    {
        // adds a digit of inputNum to the end of reversed num, starting at the end of inputNum and working towards the starting digit
        reversedNum += inputNum[9 - i];
    }

    // creates the 5-row pattern containing the original number and the reversed number
    // the numbers in each successive row are 2 spaces to the right of the previous row, which is why i increases by 2 each iteration
    for (int i = 0; i < 10; i += 2)
    {
        // creates one row of the pattern (starting spaces, then original number, then 10 spaces, then reversed number)
        // starting space increases by 2 for each iteration of the loop
        cout << setw(15 + i) << inputNum << setw(20) << reversedNum << endl;
    }
    return 0;
}