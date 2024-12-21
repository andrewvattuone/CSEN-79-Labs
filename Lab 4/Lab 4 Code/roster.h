/** 
 * CSEN 79 LabCode
 * Name: Andrew Vattuone
 * Email: avattuone@scu.edu
 * Partner: Johnathan Tsai
*/
#ifndef ROSTER_H
#define ROSTER_H

// Class declaration for roster
namespace lab4_avattuone_jtsai2 {
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

		Roster();
		bool insert(T &);
		void erase(Student::ID_t);
		
		T* begin(void);
		T* end(void);
		T* next(void);

		~Roster();
	
	private:
		T* students; // pointer that's used as a dynamic array for all students
		int capacity; // stores the maximum capacity of the array. Increases by 10 if max capacity is reached and user tries to insert another student
		int currIndex; // stores the current index of the array (is used for iteration to track your location in the array)
		int count; // stores the total number of students inputted into the array
	};
}
#endif // ROSTER_H
