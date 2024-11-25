/** 
 * CSEN 79 Lab Code
 * Name: Andrew Vattuone
 * Email: avattuone@scu.edu
*/


#ifndef ITEM_CPP
#define ITEM_CPP

#include "node.h"

namespace lab7_avattuone
{
    // Constructor for node class
    node::node(const std::string &itemName, const float &newPrice, node *nextNode) {
        name = itemName;
        price = newPrice;
        link = nextNode;
    }
    
    // Sets the name equal to the inputted name
    void node::setName(const std::string &newName) {
        name = newName;
    }
    
    // Sets the price equal to the inputted price
    void node::setPrice(const float &newPrice) {
        price = newPrice;
    }
    
    // Sets the pointer to the next node equal to the inputted pointer
    void node::setLink(node *new_next) {
        link = new_next;
    }
    
    // returns the pointer to the next node
    node* node::getLink() {
        return link;
    }
    
    // Returns a constant pointer to the next node
    const node* node::getLink() const {
        return link;
    }
    
    // Returns the product name stored in the node
    std::string node::getName() const{
        return name;
    }
    
    // Returns the product price stored in the node
    float node::getPrice() const {
        return price;
    }
    
    // Creates a new lsit and adds a node to it using the inputted name and price
    void list_init(node*& head, node*& tail, const std::string& newName, const float& newPrice) {
        // everywhere there's a new do a bad alloc
        head = new node(newName, newPrice, NULL);
        tail = head;
    }
    
    
    // Inserts a product node at the end of the list
    void list_tail_insert(node*& tail, const std::string &newName, const float &newPrice) 
    {
        // creates a new node and makes the tail point to it
        node* newProduct = new node(newName, newPrice, nullptr);
        tail->setLink(newProduct);
        tail = newProduct; 
    }
    
    // Deallocates all the memory in the list and sets head to null
    void list_clear(node*& head) 
    {
        // itearates through each element in the list and deallocates its memory
        while(head != nullptr)
        {
            node* temp = head;
            head = head->getLink();
            delete temp;
        }
    }
    
    
    // copies the elements from one list to another list
    void list_copy(const node *old_head, node* &new_head, node* &new_tail) {
        new_head = NULL;
        new_tail = new_head;
        
        const node *cur = old_head;
        while (cur != NULL) {
            if (new_head == NULL) {
                new_head = new node(cur->getName(), cur->getPrice());
                new_tail = new_head;
            }
            else {
                new_tail->setLink(new node(cur->getName(), cur->getPrice()));
                new_tail = new_tail->getLink();
            }
            cur=cur->getLink();
        }
    }
    
    // Removes the head node from a list and sets the new head node to point to the node after the old head node
    void list_head_remove(node*& head) {
        // removes the head node and sets head equal to the next node after the previous head node
        node* temp = head;
        head = head->getLink();
        delete temp;
    }
    
    // Prints out the name and price of every product in the list
    void list_print(node *head) {
        node *cur = head;
        while (cur != NULL) {
            std::cout << "- " << cur->getName() << ", where the price is $" << cur->getPrice() << std::endl;
            cur = cur->getLink();
        }
    }
    
    // Returns true if the item is found in the list, and false if it isn't found
    bool list_contains_item(node *head_ptr, const std::string& newName) {
        return (list_search(head_ptr, newName) != NULL);
    }
    
    // Returns a pointer to the location of the inputted item
    //      If the item isn't found it returns NULL
    node* list_search(node* head_ptr, const std::string& target)
    {
        node *cursor;
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->getLink( ))
            if (target == cursor->getName( ))
                return cursor;
        return NULL;
    }
    
    // Returns a constant pointer to the location of the inputted item
    // If the item isn't found it returns NULL
    const node* list_search(const node* head_ptr, const std::string & target)
    {
        const node *cursor;
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->getLink( ))
            if (target == cursor->getName( ))
                return cursor;
        return NULL;
    }
    
}

#endif
