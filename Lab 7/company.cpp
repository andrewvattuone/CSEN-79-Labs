/** 
 * CSEN 79 Lab Code
 * Name: Andrew Vattuone
 * Email: avattuone@scu.edu
*/

// FILE: company.cpp
// CLASS implemented: company (see company.h for documentation)


#include <cassert>
#include "company.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace lab7_avattuone
{
    // Default constructor for company class
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    // Constructor for company class
    company::company(const std::string& company_name) {
        assert(company_name.length() > 0);

        // initializes private member variables in copmany object by setting name to the inputted name and the head and tail pointer to null since there aren't any nodes yet
        this->company_name = company_name;
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    // Copy constructor for company class
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);

        // sets the company name equal to the source name and copies all the nodes from the source to the current company object's list
        this->company_name = src.company_name;
        list_copy(src.head_ptr, head_ptr, tail_ptr);
    }

    
    // Assignment operator for company class
    company& company::operator= (const company &src) 
    {
        Debug("Company assignemnt operator..." << std::endl);

        // prevents self-assignment
        if(this == &src) {
            return *this;
        }
        else {
            this->company_name = src.company_name;
            // deletes old data from the company object
            list_clear(head_ptr);
            // copies data from the inputted company into the current company object
            list_copy(src.head_ptr, head_ptr, tail_ptr);
            return *this;
        }
    }
    
    // Destructor for company class
    company::~company() {
        list_clear(head_ptr);
    }
    
    // Returns the company name
    std::string company::get_name() const {
        return company_name;
    }
    
    // Returns a constant pointer to the first product node in the company
    const node *company::get_head() const {
        return head_ptr;
    }
    
    // Returns a constant pointer to the final product node in the company
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    // Returns a pointer to the first product node in the company
    node* company::get_head() {
        return head_ptr;
    }
    
    // Returns a pointer to the final product node in the company
    node* company::get_tail() {
        return tail_ptr;
    }
    
    // Prints out all the items belonging to the company
    void company::print_items() {
        list_print(head_ptr);
    }
    
    
    // Adds a product to the company using the inputted product name and price
    //      Returns true if the product was successfully added
    //      Returns false if the copmany already has the product in its list of products
    bool company::insert(const std::string& product_name, const float& price) 
    {    
        assert(product_name.length() > 0);

        // if the company already has the inputted product, then return false
        if (list_contains_item(head_ptr, product_name)) {
            return false;
        }
        
        // if there's no head pointer, then the list is empty, so create a new list and make head pointer point to the inserted product
        if (head_ptr == NULL) {
            list_init(head_ptr, tail_ptr, product_name, price);
        }
        // the list is non-empty, so insert it at the end of the lsit
        else {
            list_tail_insert(tail_ptr, product_name, price);
        }
        
        return true;
    }

    // Removes the inputted product from the company
    //      Returns true if the product was successfully removed
    //      Returns false if the product wasn't found in the company's list of products
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);

        // searches for the location of the inputted product
        node* location = list_search(head_ptr, product_name);

        // if product isn't found then you can't erase it so return false
        if(location == NULL)
        {
            return false;
        }

        // swaps the data in the product node to be deleted with the product data in the head node (only if the node to be deleted ins't the head node)
        // this effectively erases the product node to be deleted
        if(location != head_ptr)
        {
            location->setName(head_ptr->getName());
            location->setPrice(head_ptr->getPrice());
        }
        // removes head since it was either moved to the location to be deleted or was the node to be deleted
        list_head_remove(head_ptr);
        return true;
    }
}
