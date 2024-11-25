/** 
 * CSEN 79 Lab Code
 * Name: Andrew Vattuone
 * Email: avattuone@scu.edu
 * Partner: Jonathan Tsai
*/
#include <cstddef>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "roster.h"

using namespace std;
using namespace lab4_avattuone_jtsai2;

// Test code for class roster
// Input file: <CMD> [ID] [FIRST LAST]
// CMD : A | X | L
// ID: 7-digit unsigned integer
// FIRST, LAST: string


int main() {
	Roster r;
	Student::ID_t id;
	string cmd, first, last;

	// Read cmd first, then branch accordingly
	while (cin >> cmd) {
		// inserts a student
		if (cmd == "A") 
		{
			// reads id, first name, and last name of student to file
			cin >> id;
			cin >> first;
			cin >> last;

			// creates a student from the inputted information and inserts it
			Student std(id,first,last);
			r.insert(std);
		} 
		// removes a student
		else if (cmd == "X") 
		{
			// reads the id of the student to be deleted and removes it from the roster
			cin >> id;
			r.erase(id);
		}
		// lists out all the students in the roster 
		else if (cmd == "L") {
			// this should just work, if you did your begin/end/next correctly
			int i = 1;
			for (auto st = r.begin(); st != r.end(); st = r.next(), i++)
				cout << i << ": " << *st << endl;
		} 
	}
	return EXIT_SUCCESS;
}

