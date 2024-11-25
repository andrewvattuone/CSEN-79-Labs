/** 
 * CSEN 79 Lab Sample Code
 * Name: Andrew Vattuone
 * Email: avattuone@scu.edu
 * Partner: Johnathan Tsai
*/
#include <string>
#include <iostream>
#include <stdexcept>
#include "roster.h"

namespace lab2_andrewvattuone_jonathantsai {
	
	// Default constructor for Student. Sets ID number to 0, and first and last name to empty strings
	Student::Student()
	{
		this->n = 0;
		this->fn = "";
		this->ln = "";
	}
	
	// Constructor for Student class. Initializes the ID number (of type ID_t), and strings that store the first and last name of the student
	Student::Student(Student::ID_t n, std::string fn, std::string ln) 
	{
		this->n = n;
		this->fn = fn;
		this->ln = ln;
	}

	// Default constructor for the roster class. Sets currIndex and insertIndex to 0
	Roster::Roster()
	{
		this->currIndex = 0;
		this->insertIndex = 0;
	}

	// overloaded << operator 
	// Precondition: t is an instantiated Student object
	// Postcondition: outputs the ID, first name, and last name of the student on one line (in that order)
	std::ostream& operator<<(std::ostream& os, const Student &t) {
		std::cout << t.n << " " << t.fn << " " << t.ln << std::endl;
		return os;
	}

	// Precondition: rec is an instantiated Student object
	// Postcondition: 
	//		Returns false if the array is full
	//		if it isn't full, the array students in the roster object stores the inputted student object at insertIndex in the array and returns true. Insert index also increases by 1
	bool Roster::insert(T &rec) {
		if(insertIndex >= Roster::CAPACITY)
		{
			return false;
		}
		else
		{
			students[insertIndex] = rec;
			insertIndex++;
			return true;
		}
	}

	// Takes in an ID and deletes the student that has the same inputted ID
	// Precondition: id is of type Student::ID_t
	// Postcondition: 
	//		if the student is found, then the erased student is replaced with the student at the end of the array, and insertIndex is decreased by 1
	//  	if student isn't found then nothing changes
	void Roster::erase(Student::ID_t id) {
		for(int i = 0; i < Roster::CAPACITY; i++)
		{
			// runs if the desired student is found
			if(students[i].getID() == id)
			{
				// replaces the student to be deleted with the student at the end of the array, effectively deleting the student to be deleted
				students[i] = students[--insertIndex];
				break;
			}
		}
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
	// 		insertIndex >= 0
	// Postcondition: 
	//		Returns a pointer to the end of the student array, which is the location right after the final student located in the array
	Roster::T* Roster::end(void) {
		return students + insertIndex;
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
