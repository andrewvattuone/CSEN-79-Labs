/**
 * Name: Andrew Vattuone
 * Program Description:
 *      Counts and returns the number of alphanumeric and non-alphanumeric characters using a string inputted with cin.
 *      Spaces don't count toward either of the two character types.
 *
 * School ID: 7700000354
 * Contact Info (Optional): avattuone@scu.edu
 */

#include <iostream>
using namespace std;

int main()
{
    cout << "Enter a sentence:" << endl;
    string inputString;
    // takes the whole line as an input so it can read a string that has multiple words separated by spaces
    getline(cin, inputString);

    int numAlphanumeric = 0; // stores number of alphanumeric characters
    int nonSpaceChars = 0;   // stores number of non-whitespace characters in the string

    // goes through the string and counts the number of alphanumeric characters and non-whitespace characters
    for (int i = 0; i < inputString.length(); i++)
    {
        // checks whether the character is alphanumeric, and if so it increases numAlphanumeric by 1
        if (isalnum(inputString[i]))
        {
            numAlphanumeric++;
        }
        // if a space is found then it will prevent nonSpaceChars++ from being executed so only non-space chars are counted
        else if (inputString[i] == ' ')
        {
            continue;
        }
        // only increases if the current char is not a space
        nonSpaceChars++;
    }

    // nonSpaceChars - numAlphanumeric is equivalent to the sum of non-alphanumeric characters (excluding spaces)
    // prints out the total # of alphanumeric and non-alphanumeric characters (excluding spaces)
    cout << "\"" << inputString << "\"" << " has " << numAlphanumeric << " alphanumeric charactes and "
         << nonSpaceChars - numAlphanumeric << " non-alphanumeric characters." << endl;
    return 0;
}