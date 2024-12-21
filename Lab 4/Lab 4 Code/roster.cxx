/** 
 * CSEN 79 Lab Code
 * Name: Andrew Vattuone
 * Email: avattuone@scu.edu
 * Partner: Johnathan Tsai
*/
#include <string>
#include <iostream>
#include <stdexcept>
#include <new>
#include "roster.h"


/**
 * Invariance:
 * 		count represents the number of students inputted into the array
 * 		count >= 0
 * 		count < capacity (but if it's greater than capacity and insert is called, then capacity will increase)
 * 		capacity >= 0
 * 		elements 0 through count-1 in the array represents the students on the roster
 * 		we don't care what the values of elements count through capacity-1 are - we ignore those since we don't consider them to be part of the roster 
 * 
 * Value semantics:
 * 		Default copy constructor and assignment operators for Roster may NOT be used, as Roster uses dynamic memory allocation
 * 		Default copy constructor and assignment operators can be used for the Student class, as it doesn't use any dynamic memory allocation
 */

namespace lab4_avattuone_jtsai2 {
	
	// Default constructor for Student. Sets ID number to 0, and first and last name to empty strings
	Student::Student()
	{
		n = 0;
		fn = "";
		ln = "";
	}
	
	// Constructor for Student class. Initializes the ID number (of type ID_t), and strings that store the first and last name of the student
	Student::Student(Student::ID_t n, std::string fn, std::string ln) 
	{
		this->n = n;
		this->fn = fn;
		this->ln = ln;
	}

	// Default constructor for the roster class. Sets students to nullptr, and capacity, currIndex, and count to 0
	Roster::Roster()
	{
		students = nullptr;
		capacity = 0;
		currIndex = 0;
		count = 0;
	}

	// overloaded << operator 
	// Precondition: t is an instantiated Student object
	// Postcondition: outputs the ID, first name, and last name of the student on one line (in that order)
	std::ostream& operator<<(std::ostream& os, const Student &t) {
		std::cout << t.n << " " << t.fn << " " << t.ln << std::endl;
		return os;
	}

	// Inserts a student into the roster
	// Precondition: rec is an instantiated Student object
	// Postcondition: 
	//		If the array reaches max capacity, then the capacity of the array is increased by 10
	//		The array students in the roster object stores the inputted student object at count (the next array index after the final student in the array) in the array and returns true. Count also increases by 1
	//		If there's a bac_alloc error then it return false, otherwise true is returned
	bool Roster::insert(T &rec) {
		// increases array size if count reaches max capacity
		if(count >= capacity)
		{
			try
			{
				// increases capacity by 10
				capacity += 10;
				// creats a new array with the correct size
				T* biggerRoster = new T[capacity];
				std::copy(students, students + count, biggerRoster);
				// deletes the old array and sets students equal to the new array
				delete [] students;
				students = biggerRoster;
			}
			// catches any bac_alloc exceptions, displays a message about the error, and returns false
			catch(std::bad_alloc& ba)
			{
				std::cerr << "bad_alloc caught: " << ba.what() << '\n';
				return false;
			}
		}
		students[count++] = rec;
		return true;
	}

	// Takes in an ID and deletes the student that has the same inputted ID
	// Precondition: id is of type Student::ID_t
	// Postcondition: 
	//		if the student is found, then the erased student is replaced with the student at the end of the array, and count is decreased by 1
	//  	if student isn't found then nothing changes
	//      if the number of students left in the array is less than capacity*0.5, then the capacity of the array will be divided by 2
	void Roster::erase(Student::ID_t id) {
		for(int i = 0; i < capacity; i++)
		{
			// runs if the desired student is found
			if(students[i].getID() == id)
			{
				// replaces the student to be deleted with the student at the end of the array, effectively deleting the student to be deleted
				students[i] = students[--count];
				// if the number of students left is less than half the total capacity, then halve the capacity
				if(count < capacity*0.5)
				{
					// divides the capacity by 2
					capacity /= 2;
					// creats a new array with the correct size
					T* smallerRoster = new T[capacity];
					std::copy(students, students + count, smallerRoster);
					// deletes the old array and sets students equal to the new array
					delete [] students;
					students = smallerRoster;
				}
				break;
			}
		}
	}

	// Destructor for roster class. Deallocates all the memory allocated to the students array
	Roster::~Roster()
	{
		delete [] students;
		students = nullptr;
	}

	// Precondition: 
	//		students is an instantiated array
	// Postcondition: 
	//		returns a pointer to the first student in the students array in Roster
	//		sets currIndex to 0
	Roster::T* Roster::begin(void) {
		currIndex = 0;
		return students;
	}

	// Precondition:
	//		students is an instantiated array
	// 		count >= 0
	// Postcondition: 
	//		Returns a pointer to the end of the student array, which is the location right after the final student located in the array
	Roster::T* Roster::end(void) {
		return students + count;
	}

	// Precondition:
	//		students is an instantiated array
	//		currIndex >= 0
	// Postcondition:
	//		Returns a pointer to the next element in the student array
	//		Increases currIndex by 1
	Roster::T* Roster::next(void) {
		return students + (++currIndex);
	}
}
