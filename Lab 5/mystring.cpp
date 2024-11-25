/** 
 * CSEN 79 Lab Code
 * Name: Andrew Vattuone
 * Email: avattuone@scu.edu
*/
#include <cassert>
#include "mystring.h"

namespace lab5_avattuone
{
    // Constructor for string class when input is a c-string. Default value when no string is passed in is an empty string
	string::string(const char str[ ])
    {
        current_length = strlen(str);
        // allocates memory to the string, making sure to include space for null terminator
        allocated = current_length + 1;
        characters = new char[allocated];
        std::strncpy(characters, str, allocated);
        characters[current_length] = '\0';
    }

    // Constructor for string class when input is a single character
    string::string(char c)
    {
        // allocates memory to the string, making sure to include space for null terminator
        characters = new char[2];
        characters[0] = c;
        characters[1] = '\0';
        current_length = 1;
        allocated = 2;
    }

    // Copy constructor for string class
    string::string(const string& source)
    {
        current_length = source.current_length;
        // allocates memory to the string
        allocated = source.allocated;
        characters = new char[source.allocated];
        std::strncpy(characters, source.characters, source.allocated);
        characters[current_length] = '\0';
    }

    // Destructor for string class
    string::~string()
    {
        delete[] characters;
    }

    // += operator when input is a string object
    void string::operator +=(const string& addend)
    {
        reserve(current_length + addend.current_length + 1);
        std::strncat(characters, addend.characters, addend.current_length);
        current_length += addend.current_length;
        characters[current_length] = '\0';
    }

    // += operator when input is a c-string
    void string::operator +=(const char addend[ ])
    {
        size_t addend_length = strlen(addend);
        reserve(current_length + addend_length + 1);
        std::strncat(characters, addend, addend_length + 1);
        current_length += addend_length;
        characters[current_length] = '\0';
    }

    // += operator when input is a single character
    void string::operator +=(char addend)
    {
        reserve(current_length + 2);
        characters[current_length++] = addend;
        characters[current_length] = '\0';
    }

    // Allocates the inputted amount of memory to the string
    void string::reserve(size_t n)
    {
        // if the inputted size is equal to the current number of allocated chars or if it's less than the number of chars in the string, then don't reserve memory
        if(n == allocated || n < current_length + 1)
        {
            return;
        }

        // reserves new memory by allocating a new char array, copying the data to that, and freeing the memory from the old array
        char *newChars = new char[n];
        std::strncpy(newChars, characters, current_length);
        delete[] characters;
        characters = newChars;
        allocated = n;
        characters[current_length] = '\0';
    }

    // Assignment operator for string class. Input is another string object
    string& string::operator =(const string& source)
    {
        // doesn't run if the object calls = on itself since that would be a waste
        if (this != &source) 
        {
            // allocates correct amount of memory to string
            current_length = source.current_length;
            reserve(source.current_length + 1);
            // uses the source data to set the current object equal to the source
            std::strncpy(characters, source.characters, current_length);
            characters[current_length] = '\0';
        }
        return *this;
    }

    // Inserts the inputted string at the inputted position
    void string::insert(const string& source, unsigned int position)
    {
        assert(position <= current_length);

        // if needed reserve more memory
        if(current_length + source.current_length + 1 > allocated)
        {
            reserve(current_length + source.current_length + 1);
        }
        
        // array that holds the characters that are shifted by the insertion of the source string
        char pushChars[current_length - position + 1];
        std::strncpy(pushChars, characters + position, current_length - position);

        // inserts the source string into the desired position
        std::strncpy(characters + position, source.characters, source.current_length);

        // inserts the pushed characters at the end of the string after the inserted source characters
        std::strncpy(characters + position + source.current_length, pushChars, current_length - position);

        current_length += source.current_length;
    }

    // Deletes the inputted number of elements starting at the inputted position in the string
    void string::dlt(unsigned int position, unsigned int num)
    {
        assert((position + num) <= current_length);
        // deletes the characters by copying the part of the array after the deleted characters to the deletion position, thus overwriting them
        std::strncpy(characters + position, characters + position + num, current_length - position - num + 1);
        current_length -= num;
        characters[current_length] = '\0';
    }

    // Replaces one character in the string with the inputted character
    void string::replace(char c, unsigned int position)
    {
        assert(position < current_length);
        characters[position] = c;
    }

    // Replaces a part of the string starting at position with the inputted source string
    void string::replace(const string& source, unsigned int position)
    {
        assert(position + source.current_length <= current_length);
        // Replaces the part of the string by copying the source string to the desired location
        std::strncpy(characters + position, source.characters, source.current_length);
        characters[current_length] = '\0';
    }

    // overloaded [ ] operator that resturns the character at the inputted index in the string
    char string::operator [ ](size_t position) const
    {
        assert(position < allocated);
        return characters[position];
    }

    // Searches for and returns the index of the first occurrence of an inputted char. Returns -1 otherwise
    int string::search(char c) const
    {
        // iterates throuch each character in the string looking for the inputted char c
        for(int i = 0; i < current_length; i++)
        {
            if(characters[i] == c)
            {
                return i;
            }
        }
        return -1; // c wasn't found in string
    }

    // Searches for and returns the index of the first occurrence of the inputted string substring. Returns -1 otherwise
    int string::search(const string& substring) const
    {
        bool startFound = false; // indicates whether the first char of the substring has been found in the string
        int startIndex; // records the index of the start of the substring found in the string
        int numMatches = 0; // stores how many chars of the string and the substring match
        for(int i = 0; i < current_length; i++)
        {
            // if the first character of the substring is found in the string, then it starts checking if the other elements of the substring match the string
            if(characters[i] == substring[0])
            {
               startFound = true;
               startIndex = i;
               ++numMatches;
            }
            // if a char in the string matches a char in the substring after the first character of the substring was found, then numMatches should increase since it's a match
            else if(startFound && characters[i] == substring[numMatches])
            {
                ++numMatches;
            }
            // if the first char in the substring was found in the string, but a char in the string doesn't match its corresponding char in the substring, then the substring wasn't found so reset the variables and keep searching
            else if(startFound && characters[i] != substring[numMatches])
            {
                startFound = false;
                startIndex = 0;
                numMatches = 0;
            }

            // if numMatches equals the string length, then all the characters in the substring have been consecutively found after the first char of the substring was found, so the substring has been found
            if(numMatches == substring.current_length)
            {
                return startIndex; // return the index where the first char of the substring appears int he string
            }
        }
        return -1; // substring wasn't found so return -1
    }

    // Returns the number of times the inputtec character c appears in the string
    unsigned int string::count(char c) const
    {
        int numInstances = 0;
        // iterates through each char in the string looking for the inputted char c
        for(int i = 0; i < current_length; i++)
        {
            if(characters[i] == c)
            {
                numInstances++;
            }
        }
        return numInstances;
    }

    // Overloaded << operator that prints out the characters in the string
    std::ostream& operator <<(std::ostream& outs, const string& source)
    {
        outs << source.characters;
        return outs;
    }

    // overloaded == operator that returns true if the chars in s1 are exactly the same as the chars in s2
    bool operator ==(const string& s1, const string& s2)
    {
        return !strcmp(s1.characters, s2.characters);
    }

    // overloaded != operator that returns true if the chars in s1 are not the same as the chars in s2
    bool operator !=(const string& s1, const string& s2)
    {
        return strcmp(s1.characters, s2.characters);
    }

    // overloaded > operator that returns true if s1 comes after s2 alphabetically
    bool operator > (const string& s1, const string& s2)
    {
        return strcmp(s1.characters, s2.characters) > 0;
    }

    // overloaded < operator that returns true if s1 comes before s2 alphabetically
    bool operator < (const string& s1, const string& s2)
    {
        return strcmp(s1.characters, s2.characters) < 0;
    }

    // overloaded >= operator that returns true if s1 comes after s2 alphabetically or if the characters in s1 are exaclty the same as s2
    bool operator >=(const string& s1, const string& s2)
    {
        return s1 > s2 || s1 == s2;
    }

    // overloaded <= operator that returns true if s1 comes before s2 alphabetically or if the characters in s1 are exaclty the same as s2
    bool operator <=(const string& s1, const string& s2)
    {
        return s1 < s2 || s1 == s2;
    }

    // Overloaded + operator that returns s1 concatenated with s2. In this case both s1 and s2 are string objects
    string operator +(const string& s1, const string& s2)
    {
        string newStr = s1;
        newStr += s2;
        return newStr;
    }

    // Overloaded + operator that returns s1 concatenated with s2. In this case s1 is a string object but s2 is a c-string
    string operator +(const string& s1, const char addend[ ])
    {
        string newStr = s1;
        newStr += addend;
        return newStr;
    }

    // Overloaded >> operator that takes in an input string from the terminal and stores it in the target string
    std::istream& operator >> (std::istream& ins, string& target)
    {
        char c;
        string str;
        // keeps reading characters until it finds a whitespace character
        while(ins.get(c))
        {
            // if a whitespace character is found, break out of the loop
            if(isspace(c))
            {
                break;
            }
            // if it's not whitespace add it to the string
            str += c;
        }
        // set target equal to the inputted string
        target = str;
        return ins;
    }
}