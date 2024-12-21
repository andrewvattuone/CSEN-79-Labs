/** 
 * CSEN 79 Lab Code
 * Name: Andrew Vattuone
 * Email: avattuone@scu.edu
*/
#ifndef ROSTER_H
#define ROSTER_H

// Class declaration for roster
namespace lab6_avattuone 
{
	// base data for the roster
	class Student 
	{
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

	// node that stores a student and a pointer to the next student node, which is used for creating a linked list of students
	class StdNode
	{
		public:
			using T = Student;

			StdNode(T std, StdNode* nextStd = nullptr);
			T getStd() const { return std; } // returns the student stored inside the node
			StdNode* getNext() { return nextStd; } // returns a pointer to the next student node in the list
			void setNext(StdNode* newNext) { nextStd = newNext; } // changes the value of next
		
		private:
			T std; // stores a student object inside the student node
			StdNode* nextStd; // pointer to the next student node in the list
	};

	class Roster 
	{
		public:
			using T = Student;

			Roster();
			~Roster();
			bool insert(T &);
			void erase(Student::ID_t);
			
			StdNode* begin(void);
			StdNode* end(void);
			StdNode* next(void);
		
		private:
			StdNode* head; // points to the first student node in the list
			StdNode* tail; // points to the final student node in the list
			StdNode* currStd; // points to the current student node in the list (is used for iterating through the list and keeping track of where you are)
		
	};
}
#endif // ROSTER_H
