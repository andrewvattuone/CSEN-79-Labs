/** 
 * CSEN 79 Lab Code
 * Name: Andrew Vattuone
 * Email: avattuone@scu.edu
*/

#include <iostream>
#include "deque.h"
using namespace lab8_avattuone;
using std::cout;
using std::endl;


int main()
{
    // testing if the constructor works with default arguments
    cout << "Testing if deque constructor works with default arguments" << endl;
    deque<int>* d1 = new deque<int>;

    cout << "Testing if iterator constructor works" << endl;
    deque<int>::iterator i1;
    
    cout << "Testing if push_front works when there are no elements in the deque" << endl;
    d1->push_front(1);
    i1 = d1->begin();
    cout << *i1 << endl; // should print out 1 since that's the only element in the deque

    cout << "Testing if pop_front() works when there's only one element in the deque" << endl;
    d1->pop_front();
    cout << d1->isEmpty() << endl; // should print out 0 since the list is empty

    cout << "Testing if push_back works when there are no elements in the deque" << endl;
    d1->push_back(7);
    i1 = d1->begin();
    cout << *i1 << endl; // should print out 7 since it's the only element in the list

    cout << "Testing if push_front works correctly when a new block needs to be allocated to the front" << endl;
    d1->push_front(2); // this line causes the program to allocate memory for a new block
    d1->print(); // should print out the list correclty

    cout << "Testing if push_front works correctly for multiple elements" << endl;
    d1->push_front(4);
    d1->push_front(7);
    d1->print(); // should print out the list correclty

    cout << "Testing if push_front works correctly when more memory needs to be reserved for the deque" << endl;
    d1->push_front(11);
    d1->push_front(8);
    d1->push_front(9); // this line allocates more memory to the deque
    d1->print(); // should print out the list correctly

    cout << "Testing if push_back works correctly for multiple elements" << endl;
    d1->push_back(6);
    d1->push_back(7);
    d1->print(); // should print out the list correclty

    cout << "Testing if push_back works correctly when a new block needs to be allocated to the back" << endl;
    d1->push_back(3);
    d1->push_back(9);
    d1->push_back(11); // this line will cause the program to allocate memory for a new block
    d1->print(); // should print out the list correclty

    cout << "Testing if push_back works correctly when more memory needs to be reserved for the deque" << endl;
    for(int i = 0; i < 65; i++)
    {
        d1->push_back(i);
    }
    d1->print(); // should print out the list correclty

    cout << "Testing if pop_front works correclty when the front element is the last element in the front block (needs to delete the block)" << endl;
    d1->pop_front();
    d1->print(); // should print out the deque except the first element will be removed

    cout << "Testing if pop_front works correclty when front element is neither the last element in the deque nor the last element in its block" << endl;
    d1->pop_front();
    d1->print(); // should print out the deque except the first element will be removed

    cout << "testing if pop_back works correctly when the back element is the first element in the last block (needs to delete the block)" << endl;
    d1->pop_back();
    d1->print(); // should print out the deque except the last element will be removed

    cout << "Testing if pop_back works correctly when the back element is neither the first element in the last block nor the only element in the deque" << endl;
    d1->pop_back();
    d1->print(); // should print out the deque except the last element will be removed

    cout << "Testing if front function correctly returns the item at the front of the deque" << endl;
    cout << d1->front() << endl; // should return the element at the front of the deque

    cout << "Testing if back function correctly returns the item at the back of the deque" << endl;
    cout << d1->back() << endl; // should return the element at the back of the deque

    cout << "Testing if clear works correctly" << endl;
    d1->clear();
    d1->print(); // shouldn't print out anything since every element was deleted

    cout << "Testing if pop_front works correctly when there's only one element in the deque" << endl;
    d1->push_front(1);
    d1->print(); // should print out 1 since it's the only element in the deque
    d1->pop_front();
    cout << "list after deletion:" << endl;
    d1->print(); // shouldn't print out anything since every element was deleted

    cout << "Testing if pop_back works correclty when there's only one element in the deque" << endl;
    d1->push_front(1);
    d1->print(); // should print out 1 since it's the only element in the deque
    d1->pop_back();
    cout << "list after deletion:" << endl;
    d1->print(); // shouldn't print out anything since every element was deleted

    cout << "Testing if copy constructor works correclty" << endl;
    d1->push_front(1);
    d1->push_front(5);
    d1->push_front(8);
    d1->push_back(7);
    d1->push_back(3);
    d1->push_back(4);
    deque<int>* d2 = new deque(*d1); // copy constructor call
    cout << "D1 elements:" << endl;
    d1->print();
    cout << "D2 elements:" << endl;
    d2->print();

    cout << "Testing if changing one deque doesn't affect the other if one was created with the copy constructor" << endl;
    d1->pop_front();
    d1->pop_front();
    d1->pop_back();
    d1->push_front(9);
    d1->push_back(3);
    d1->push_back(7);
    d1->push_back(4);

    d2->push_front(9);
    d2->push_front(14);
    d2->pop_back();
    d2->pop_back();
    d2->pop_back();
    d2->pop_back();

    // elements printed out should be different for each deque
    cout << "D1 elements:" << endl;
    d1->print();
    cout << "D2 elements:" << endl;
    d2->print();

    cout << "Testing if deleting one deque doesn't delete the other if one was created with the copy constructor" << endl;
    delete d1;
    cout << "D1 elements:" << endl;
    d1->print(); // should print out nothing
    cout << "D2 elements:" << endl;
    d2->print(); // should print out all elements in D2

    cout << "Testing if assignment operator works correctly" << endl;
    d1 = new deque<int>;
    d1->push_back(6); 
    d1->push_back(7);
    d1->push_front(5);
    d1->push_front(3);
    d1->push_front(4);
    d1->push_front(8);
    d1->push_back(9);

    cout << "D1 elements" << endl;
    d1->print();

    deque<int>* d3 = new deque<int>;
    d3->push_front(6);
    d3->push_back(1);
    d3->push_back(14);
    d3->push_front(17);
    d3->push_front(11);
    d3->push_back(13);

    cout << "D3 elements" << endl;
    d3->print();

    *d3 = *d1; // assignemnt operator call

    // elements in D3 and D1 should be the same
    cout << "D1 elements after assignment operator call" << endl;
    d1->print();
    cout << "D3 elements after assignment operator call" << endl;
    d3->print();

    cout << "Testing if changing one deque doesn't change the other if one was created through the assignment operator" << endl;
    d1->pop_front();
    d1->pop_back();
    d1->pop_back();
    d1->pop_back();
    d1->push_front(36);
    d1->push_back(29);

    d3->pop_front();
    d3->pop_front();
    d3->pop_front();
    d3->pop_back();
    d3->push_front(27);
    d3->push_back(58);
    d3->push_back(42);

    // elements in D1 and D3 should be different
    cout << "D1 elements:" << endl;
    d1->print();
    cout << "D3 elements:" << endl;
    d3->print();

    cout << "Testing if deleting one deque doesn't delete the other if one was created with the assignment operator" << endl;
    delete d1;
    cout << "D1 elements:" << endl;
    d1->print(); // shouldn't print out anything
    cout << "D3 elements:" << endl;
    d3->print(); // should print out all the D3 elements
    
    cout << "Testing if adding an element to a deque with push_front after all its elements have been popped works correctly" << endl;
    deque<int>* d4 = new deque<int>;
    d4->push_front(5);
    d4->push_front(7);
    d4->push_front(8);
    d4->push_back(11);
    d4->push_back(9);
    
    cout << "Original D4 elements:" << endl;
    d4->print();

    for(int i = 0; i < 5; i++)
    {
        d4->pop_front();
    }

    d4->push_front(23);
    cout << "D4 elements after popping all of them and then adding one with push_front:" << endl;
    d4->print(); // should just print out 23 and nothing else

    cout << "Testing if adding an element to a deque with push_back after all its elements have been popped works correctly" << endl;
    deque<int>* d5 = new deque<int>;
    d5->push_front(12);
    d5->push_front(19);
    d5->push_front(81);
    d5->push_back(15);
    d5->push_back(49);
    
    cout << "Original D5 elements:" << endl;
    d5->print();

    for(int i = 0; i < 5; i++)
    {
        d5->pop_front();
    }

    d5->push_back(73); 
    cout << "D5 elements after popping all of them and then adding one with push_front:" << endl;
    d5->print(); // should just print out 73 and nothing else

    cout << "Testing if constructor for a deque works when the default arguments aren't used" << endl;
    deque<int>* d6 = new deque<int>(2, 3);
    d6->push_front(5);
    d6->push_back(6);
    d6->push_back(11);
    d6->push_back(41); // will cause a new block to be allocated
    d6->push_front(15); // will cause more memory to be reserved for the whole deque
    d6->print(); // should print out correctly
    
    
    cout << "Testing if prefix ++ works correctly for the deque iterator (uses above deque)" << endl;
    deque<int>::iterator i2 = d6->begin();
    cout << "Original iterator value: " << endl;
    cout << *i2 << endl; // should print out the first element in the deque (15)
    cout << "Iterator value after using prefix: " << endl;
    cout << *(++i2) << endl; // should print out the second element in the deque (5)

    cout << "Testing if postfix ++ works correclty for the deque iterator (uses same deque as above)" << endl;
    deque<int>::iterator i3 = d6->begin();
    cout << "Original iterator value: " << endl;
    cout << *i3 << endl; // should print out the first element in the deque (15)
    cout << "Iterator value when postfix is called (should be exactly the same value since the postfix occurs on the same line as the print statement):" << endl;
    cout << *(i3++) << endl; // should print out the first element in the deque (15)
    cout << "Iterator value after postfix (this one should be different since the print is on the line after the postfix)" << endl;
    cout << *i3 << endl; // should print out the second element in the deque (5)

    cout << "== operator test for deque iterator when the iterators are equal to each other" << endl;
    deque<int>::iterator i4 = (++d6->begin());
    deque<int>::iterator i5 = (++d6->begin());
    cout << (i4 == i5) << endl; // should print out 1 since it's true
    
    cout << "== operator test for deque iterator when the iterators are equal to each other" << endl;
    deque<int>::iterator i6 = (++d6->begin());
    deque<int>::iterator i7 = d6->begin();
    cout << (i6 == i7) << endl; // should print out 0 since it's false

    cout << "!= operator test for deque iterator when the iterators aren't equal to each other" << endl;
    deque<int>::iterator i8 = (++d6->begin());
    deque<int>::iterator i9 = d6->begin();
    cout << (i8 != i9) << endl; // should print out 1 since it's true

    cout << "!= operator test for deque iterator when the iterators aren't equal to each other" << endl;
    deque<int>::iterator i10 = (++d6->begin());
    deque<int>::iterator i11 = (++d6->begin());
    cout << (i10 != i11) << endl; // should print out 0 since it's false
}