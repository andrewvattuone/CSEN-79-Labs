/** 
 * CSEN 79 Lab Code
 * Name: Andrew Vattuone
 * Email: avattuone@scu.edu
*/
#include <string>
#include <iostream>
#include <stdexcept>
#include <new>
#include "roster.h"

namespace lab6_avattuone
{
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

	// Constructor for the student node. Initializes the student std stored in the node, as well as the pointer to the next student (next is never set on creation in this code, but it's still included for other possible uses)
	StdNode::StdNode(T std, StdNode* nextStd)
	{
		this->std = std;
		this->nextStd = nextStd;
	}

	// Default constructor for the roster class. Sets currIndex and insertIndex to 0
	Roster::Roster()
	{
		this->head = nullptr;
		this->tail = head;
		currStd = head;
	}

	// Destructor for the Roster class. 
	// Deallocates any memory allocated to the student nodes, and sets head, tail, and currStd to nullptr to prevent possible errors
	Roster::~Roster()
	{
		StdNode* st = begin();
		// deallocates memory allocated to the nodes in the list
		while (st != nullptr)
		{
			StdNode* temp = st;
			st = st->getNext();
			delete temp;
		}

		head = nullptr;
		tail = nullptr;
		currStd = nullptr;
	}

	// overloaded << operator 
	// Precondition: 
	//		t is an instantiated Student object
	// Postcondition: 
	//		outputs the ID, first name, and last name of the student on one line (in that order)
	std::ostream& operator<<(std::ostream& os, const Student &t) {
		std::cout << t.n << " " << t.fn << " " << t.ln << std::endl;
		return os;
	}

	// Precondition: 
	//		rec is an instantiated Student object
	// Postcondition: 
	//		Returns false if there is a bad alloc exception
	//		Returns true if the student is successfully added to the list
	bool Roster::insert(T &rec) 
	{
		try
		{
			// if the list is empty, then set head equal to the new node added to the list
			if(head == nullptr)
			{
				// allocates memory for the new student node and sets head and tail equal to it
				head = new StdNode(rec);
				tail = head;
				tail->setNext(nullptr);
				currStd = head;
			}
			else // list already has at least one element
			{
				// adds the new student node to the end of the list
				tail->setNext(new StdNode(rec)); // makes sure to change the value of next so that all nodes can be properly accessed in the list
				tail = tail->getNext();
				tail->setNext(nullptr);
			}
		}
		catch(std::bad_alloc& ba)
		{
			std::cerr << "bad_alloc caught: " << ba.what() << '\n';
			return false;
		}
		return true;
	}

	// Takes in an ID and deletes the student that has the same inputted ID
	// Precondition: 
	//		id is of type Student::ID_t
	// Postcondition: 
	//		If student with corresponding ID is found, then the student node is removed from the list and deallocated
	//  	If no student with the inputted ID is found, the list remains the same
	void Roster::erase(Student::ID_t id) 
	{
		// if the first student in the list has the inputted ID, then delete that student and change head to the next student in the list
		if(head->getStd().getID() == id)
		{
			StdNode* temp = head;
			// if there's only one student in the list, then set tail equal to nullptr since the list will be empty after deletion
			if(tail == head)
			{
				tail = nullptr;
			}
			head = head->getNext(); // change head to point to the next node in the list (will be nullptr if the list has only 1 element before deletion)
			delete temp;
			return;
		}

		// iterates through each node in the list looking for the ID, always looking at the next node after the current node so deletion is easier
		for(StdNode* st = begin(); st->getNext() != nullptr; st = next())
		{
			// if the student after the current student has the corresponding ID, then delete that next student
			if(st->getNext()->getStd().getID() == id)
			{
				StdNode* temp = st->getNext();
				// if the student to be deleted is the last student in the list, then move the tail pointer to the node before the final node
				if(tail == temp)
				{
					tail = st;
				}
				// changes the value of next for st to remove the node after st from the list, and then deallocates the node
				st->setNext(st->getNext()->getNext());
				delete temp;
				break;
			}
		}
	}

	// Precondition: 
	//		None
	// Postcondition: 
	//		returns a pointer to the first student in the list of student nodes in roster
	//		sets currIndex to head
	StdNode* Roster::begin(void) 
	{
		currStd = head;
		return head;
	}

	// Precondition:
	//		None
	// Postcondition: 
	//		Returns a pointer to the location after the final node in the list, which is always nullptr since there are no nodes after the final node
	StdNode* Roster::end(void) 
	{
		return nullptr;
	}

	// Precondition:
	//		None
	// Postcondition:
	//		Changes currStd to point to the next student in the list
	//		Returns a pointer to the next student in the list, which is at the updated value of currStd
	//		If currStd is equal to null, then that indicates all students in the list have been iterated over by a function
	StdNode* Roster::next(void) 
	{
		// if currStd is equal to nullptr (reached the end of the list), then return nullptr to avoid errors with trying to get currStd->getNext() when currStd is null
		if(currStd == nullptr)
		{
			return end();
		}
		currStd = currStd->getNext();
		return currStd;
	}
}
