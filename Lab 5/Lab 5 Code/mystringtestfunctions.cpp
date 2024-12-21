/** 
 * CSEN 79 Lab Code
 * Name: Andrew Vattuone
 * Email: avattuone@scu.edu
*/

#include <iostream>
#include "mystring.h"

using namespace lab5_avattuone;
using std::cout;
using std::endl;

namespace lab5_avattuone
{
    // tests if creating a string using a c-string properly creates a string object
    void test1()
    {
        cout << "C-String constructor test:" << endl;
        char cstr[6] = "hello";
        string str(cstr);
        cout << str << endl;
        cout << endl;
    }

    // tests if creating a string without passing in any arguments to the constructor correctly creates an empty string
    void test2()
    {
        cout << "Default Constructor test:" << endl;
        string str;
        cout << str << endl;
        cout << endl;
    }
        
    // tests if creating a string using only a single character correctly creates a 1-character string
    void test3()
    {
        cout << "Single character constructor test:" << endl;
        char c = 'h';
        string str(c);
        cout << str << endl;
        cout << endl;
    }
        
    // tests if the copy constructor correctly creates a new string if you pass in a c-string as an argument and a string class as an argument
    void test4()
    {
        cout << "C-string and regular string copy constructor test:" << endl;
        char cstr2[8] = "Goodbye";
        string str4(cstr2); // c-string part
        string str5(str4); // actual string part
        cout << str4 << endl;
        cout << str5 << endl;
        cout << endl;
    }    

    // tests if the copy constructor correctly creates a new string when using the following notation for a c-string: string str1 = str2
    void test5()
    {
        cout << "string str1 = str2 copy constructor test:" << endl;
        char cstr[12] = "Santa Clara";
        string str1(cstr);
        string str2 = str1;
        cout << str2 << endl;
        cout << endl;
    }
        
    // tests if += operator works correctly when input parameter is a string object
    void test6()
    {
        cout << "+= string input test:" << endl;
        char cstr1[] = "Farokh ";
        char cstr2[] = "Eskafi";
        string str1(cstr1);
        string str2(cstr2);
        str1 += str2;
        cout << str1 << endl;
        cout << str2 << endl;
        cout << endl;
    }    
        
    // tests if the += operator works correctly when an empty string is the input
    void test7()
    {
        cout << "+= with empty string test:" << endl;
        char cstr[] = "SCDI";
        string str1(cstr);
        string str2;
        str1 += str2;
        cout << str1 << endl;
        cout << endl;
    }
        
    // tests if the += operator works correclty when the strings are the same
    void test8()
    {
        cout << "+= with same strings test:" << endl;
        char cstr1[] = "Heafey";
        char cstr2[] = "Heafey";
        string str1(cstr1);
        string str2(cstr2);
        str2 += str1;
        cout << str2 << endl;
        cout << str1 << endl;
        cout << endl;
    }   
        
    // tests if the += operator works when the input is a c-string
    void test9()
    {
        cout << "+= with c-string input test:" << endl;
        char cstr1[] = "Timothy ";
        char cstr2[] = "Cui";
        string str(cstr1);
        str += "Cui";
        cout << str << endl;
        cout << endl;
    }    

    // tests if the += operator works when the object that the += is called on (in this case str16) is an empty string
    void test10()
    {
        cout << "+= empty string object test:" << endl;
        char cstr[] = "CSEN79";
        string str1(cstr);
        string str2;
        str2 += str1;
        cout << str2 << endl;
        cout << endl;
    }

    // tests if the += operator works when the input is a single character
    void test11()
    {
        cout << "+= single char test:" << endl;
        string str("Andrew Vattuon");
        str += 'e';
        cout << str << endl;
        cout << endl;
    }

    // tests if the = operator works when the object = is called on is an empty string and the input is a string object
    void test12()
    {
        cout << "= operator empty string object and string object input test:" << endl;
        string str1("Jason Wu");
        string str2;
        str2 = str1;
        // should output "Jason Wu" both times
        cout << str2 << endl;
        cout << str1 << endl;
        cout << endl;
    }

    // tests if the = operator works when the object = is called on is already initialized, using another string object as input
    void test13()
    {
        cout << "= operator test when both objects are initialized" << endl;
        string str1("Jacob Rhodes");
        string str2("Nicholas Villegas-Kirchman");
        str1 = str2;
        // should output "Nicholas Villegas-Kirchman" both times
        cout << str1 << endl;
        cout << str2 << endl;
        cout << endl;
    }

    // tests if the = operator works then the object = is called on is set to an empty string
    void test14()
    {
        cout << "= operator test when object is set to an empty string" << endl;
        string str1("Jacob Rhodes");
        string str2;
        str1 = str2;
        cout << str1 << endl;
        cout << endl;
    }

    // tests if the == operator works correctly for two equal strings
    void test15()
    {
        cout << "== operator test when the two strings are equal" << endl;
        string str1("hello");
        string str2("hello");
        cout << (str1 == str2) << endl;
        cout << endl;
    }

    // tests if the == operator works correctly for two unequal strings
    void test16()
    {
        cout << "== operator test when the two strings aren\'t equal" << endl;
        string str1("hello");
        string str2("hello!");
        cout << (str1 == str2) << endl;
        cout << endl;
    }

    // tests if the != operator works correctly for two unequal strings
    void test17()
    {
        cout << "!= operator test when the two strings aren\'t equal" << endl;
        string str1("goodbye");
        string str2("goodbye!");
        cout << (str1 != str2) << endl;
        cout << endl;
    }

    // tests if the != operator works correctly for two equal strings
    void test18()
    {
        cout << "!= operator test when the two strings aren\'t equal" << endl;
        string str1("goodbye");
        string str2("goodbye");
        cout << (str1 != str2) << endl;
        cout << endl;
    }

    // tests if the > operator works correctly when str1 > str2
    void test19()
    {
        cout << "> operator test when str1 > str2" << endl;
        string str1("hello");
        string str2("goodbye");
        cout << (str1 > str2) << endl;
        cout << endl;
    }

    // tests if the > operator works correctly when str1 < str2
    void test20()
    {
        cout << "> operator test when str1 < str2" << endl;
        string str1("goodbye");
        string str2("hello");
        cout << (str1 > str2) << endl;
        cout << endl;
    }


    // tests if the < operator works correctly when str1 < str2
    void test21()
    {
        cout << "< operator test when str1 < str2" << endl;
        string str1("goodbye");
        string str2("hello");
        cout << (str1 < str2) << endl;
        cout << endl;
    }

    // tests if the < operator works correctly when str1 > str2
    void test22()
    {
        cout << "< operator test when str1 > str2" << endl;
        string str1("hello");
        string str2("goodbye");
        cout << (str1 < str2) << endl;
        cout << endl;
    }

    // tests if the >= operator works correctly when str1 > str2
    void test23()
    {
        cout << ">= operator test when str1 > str2" << endl;
        string str1("hello");
        string str2("goodbye");
        cout << (str1 >= str2) << endl;
        cout << endl;
    }

    // tests if the >= operator works correctly when str1 == str2
    void test24()
    {
        cout << ">= operator test when str1 == str2" << endl;
        string str1("hello");
        string str2("hello");
        cout << (str1 >= str2) << endl;
        cout << endl;
    }

    // tests if the >= operator works correctly when str1 < str2
    void test25()
    {
        cout << ">= operator test when str1 < str2" << endl;
        string str1("goodbye");
        string str2("hello");
        cout << (str1 >= str2) << endl;
        cout << endl;
    }

    // tests if the <= operator works correctly when str1 < str2
    void test26()
    {
        cout << "<= operator test when str1 < str2" << endl;
        string str1("goodbye");
        string str2("hello");
        cout << (str1 <= str2) << endl;
        cout << endl;
    }

    // tests if the <= operator works correctly when str1 == str2
    void test27()
    {
        cout << "<= operator test when str1 == str2" << endl;
        string str1("goodbye");
        string str2("goodbye");
        cout << (str1 <= str2) << endl;
        cout << endl;
    }

    // tests if the <= operator works correctly when str1 > str2
    void test28()
    {
        cout << "<= operator test when str1 > str2" << endl;
        string str1("hello");
        string str2("goodbye");
        cout << (str1 <= str2) << endl;
        cout << endl;
    }

    // tests if the count method works when the inputted char is in the string
    void test29()
    {
        cout << "count test when the inputted char is present in the string" << endl;
        string str1("hello");
        cout << str1.count('l') << endl;
        cout << endl;
    }

    // tests if the count method works when the inputted char isn't in the string
    void test30()
    {
        cout << "count test when the inputted char is not in the string" << endl;
        string str1("hello");
        cout << str1.count('a') << endl;
        cout << endl;
    }

    // tests if the [ ] operator returns the correct character based on the inputted index
    void test31()
    {
        cout << "[ ] operator test" << endl;
        string str1("hello");
        cout << str1[1] << endl;
        cout << endl;
    }

    // tests if the search method for a character present in the string works correclty
    void test32()
    {
        cout << "search method test for a character when the character is present in the string" << endl;
        string str1("hello");
        cout << str1.search('l') << endl;
        cout << endl;
    }

    // tests if the search method for a character not present in the string works correclty
    void test33()
    {
        cout << "search method test for a character when the character is not present in the string" << endl;
        string str1("hello");
        cout << str1.search('a') << endl;
        cout << endl;
    }

    // tests if the search method for a substring present in the string works correctly
    void test34()
    {
        cout << "search method test for a substring when the substring is present in the string" << endl;
        string str1("hello");
        string str2("he");
        cout << str1.search(str2) << endl;
        cout << endl;
    }

    // tests if the search method for a substring not present in the array works correclty
    void test35()
    {
        cout << "search method test for a substring when the substring isn't present in the string" << endl;
        string str1("hello");
        string str2("help");
        cout << str1.search(str2) << endl;
        cout << endl;
    }

    // tests if the + method works correclty for two initialized strings
    void test36()
    {
        cout << "+ test for two initialized strings" << endl;
        string str1("hello");
        string str2("help");
        cout << (str1 + str2) << endl;
        cout << endl;
    }

    // tests if the + operator works correclty for two uninitialized strings
    void test37()
    {
        cout << "+ operator test for two uninitialized strings" << endl;
        string str1;
        string str2;
        cout << (str1 + str2) << endl;
        cout << endl;
    }

    // tests if the + operator works correctly for an initialized string object and a c-string
    void test38()
    {
        cout << "+ operator test for an initialized string object and a c-string:" << endl;
        string str1("hello");
        char cstr[] = "goodbye";
        cout << (str1 + cstr) << endl;
        cout << endl;
    }

    // tests if the + operator works correclty for an initialized string object and an empty c-string
    void test39()
    {
        cout << "+ operator test for an initialized string object and an empty c-string" << endl;
        string str1("hello");
        char cstr[] = "";
        cout << (str1 + cstr) << endl;
        cout << endl;
    }

    // tests if the + operator works correclty for an uninitialized string object and an empty c-string
    void test40() 
    {
        cout << "+ operator test for an uninitialized string object and an empty c-string" << endl;
        string str1;
        char cstr[] = "";
        cout << (str1 + cstr) << endl;
        cout << endl;
    }

    // tests if the dlt method works correctly for multiple characters at start of string
    void test41()
    {
        cout << "dlt method test when multiple characters are deleted at start of string" << endl;
        string str1("hello");
        str1.dlt(0,2);
        cout << str1 << endl;
        cout << endl;
    }

    // tests if the dlt method works correclty for mutliple characters at a position not at the start of the string 
    void test42()
    {
        cout << "dlt method test when multiple characters are deleted at position other than the start of string" << endl;
        string str1("hello");
        str1.dlt(1,2);
        cout << str1 << endl;
        cout << endl;
    }

    // tests if the dlt method works correclty for mutliple characters at the end of the string
    void test43()
    {
        cout << "dlt method test when multiple characters are deleted the end of the string" << endl;
        string str1("hello");
        str1.dlt(3,2);
        cout << str1 << endl;
        cout << endl;
    }

    // tests if the dlt method works correclty when 0 characters are deleted
    void test44()
    {
        cout << "dlt method test when 0 characters are deleted" << endl;
        string str1("hello");
        str1.dlt(0,0);
        cout << str1 << endl;
        cout << endl;
    }

    // tests if the replace method works for a single character
    void test45()
    {
        cout << "replace method test for a single character" << endl;
        string str1("hello");
        str1.replace('a',1);
        cout << str1 << endl;
        cout << endl;
    }

    // tests if the replace method works for an inputted string
    void test46()
    {
        cout << "replace method test for an inputted string " << endl;
        string str1("hello");
        string str2("bye");
        str1.replace(str2, 1);
        cout << str1 << endl;
        cout << endl;
    }

    // tests if the insert method works when inserting into a non-empty string
    void test47()
    {
        cout << "insert method test when inserting a string into a non-empty string" << endl;
        string str1("hi");
        string str2("hello");
        str1.insert("hello", 1);
        cout << str1 << endl;
        cout << endl;
    }

    // tests if the insert method works when inserting into an empty string
    void test48()
    {
        cout << "insert method test when inserting a string into a non-empty string" << endl;
        string str1;
        string str2("hello");
        str1.insert("hello", 0);
        cout << str1 << endl;
        cout << endl;
    }

    //tests if the + operator works correclty for an unitialized string object an a non-empty c-string
    void test49()
    {
        cout << "+ operator test for an uninitialized string object and a non-empty c-string" << endl;
        string str1;
        char cstr[] = "hi";
        cout << (str1 + cstr) << endl;
        cout << endl;
    }

    // tests if the + operator works correclty for one initialized and one uninitialized string
    void test50()
    {
        cout << "+ operator test for one initialized and one uninitialized string" << endl;
        string str1;
        string str2("hello");
        cout << (str1 + str2) << endl;
        cout << endl;
    }

    // tests if the >> operator correctly stores the input from cin into the target string
    void test51()
    {
        cout << ">> operator test" << endl;
        string str1;
        std::cin >> str1;
        cout << str1 << endl;
        cout << endl;
    }
}
    

    
















    