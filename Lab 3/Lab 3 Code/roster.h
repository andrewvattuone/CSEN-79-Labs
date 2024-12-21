/** 
 * CSEN 79 Lab Sample Code
 * Name: Andrew Vattuone
 * Email: avattuone@scu.edu
 * Partner: Jonathan Tsai
*/
#ifndef ROSTER_H
#define ROSTER_H

// Class declaration for roster
namespace lab3_andrewvattuone_jonathantsai {
	// base data for the roster
	class Student {
	public:
		using ID_t = unsigned int;	// really should be a 7-digit unsigned int
		Student();
		Student(ID_t n, std::string fn, std::string ln);
		ID_t getID() const { return n; };

	friend std::ostream& operator<<(std::ostream& os, const Student &);
	
	// stores the student's ID number, first name, and last name
	private:
		ID_t n;
		std::string fn;
		std::string ln;
	};

	class Roster {
	public:
		using T = Student;
		static const int CAPACITY=30;

		Roster();
		bool insert(T &);
		void erase(Student::ID_t);
		
		T* begin(void);
		T* end(void);
		T* next(void);
	
	private:
		T students[CAPACITY]; // stores all student objects in an array (maximum of 30 students)
		int currIndex; // stores the current index of the array (is used for iteration to track your location in the array)
		int insertIndex; // index where the next student should be inserted in the array (always is the location just after the final student in the array)
	};
}
#endif // ROSTER_H
