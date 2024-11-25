/**
 * Name: Andrew Vattuone
 * Program Description:
 *      Takes a text file as input and reads every word. Only looks at alphabetical characters (ignores spaces, numbers, punctuation, etc)
 *      If a word has a length of 10 or greater after non-alphabetical characters are removed, then it's printed out with all uppercase letters
 *
 * School ID: 7700000354
 * Contact Info (Optional): avattuone@scu.edu
 */

#include <iostream>
#include <string>
#include <cassert>
#include <cctype>
#include <fstream>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[])
{
    // returns an error if no files or more than one files are inputted
    if (argc <= 1)
    {
        cout << "Error. Please input exactly one file.";
        return 0;
    }

    string filename = argv[1];
    // opens the file in read mode
    ifstream inputFile(filename);
    string word;

    // only executes while the file is open (if it doesn't open properly it prints an error)
    if (inputFile.is_open())
    {
        // reads the file word by word
        while (inputFile >> word)
        {
            // stores all the alphabetical characters in the word
            string onlyAlpha;

            // extracts all the alphabetical characters from a word (ignoring spaces, numbers, special characters, etc)
            for (int i = 0; i < word.length(); i++)
            {
                // only selects a character in a word if it's an alphabetical character
                if (isalpha(word[i]))
                {
                    // adds the character to the string that stores all the alphabetical characters in a word
                    onlyAlpha += word[i];
                }
            }

            // selects the word if it's length is 10 or greater
            if (onlyAlpha.length() >= 10)
            {
                // makes all the letters in the word uppercase before printing it out
                transform(onlyAlpha.begin(), onlyAlpha.end(), onlyAlpha.begin(), ::toupper);
                cout << onlyAlpha << endl;
            }
        }

        inputFile.close();
    }
    else
    {
        cout << "Error opening file." << endl;
    }

    return 0;
}