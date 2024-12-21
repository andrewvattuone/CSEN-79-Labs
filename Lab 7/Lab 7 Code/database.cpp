/** 
 * CSEN 79 Lab Code
 * Name: Andrew Vattuone
 * Email: avattuone@scu.edu
*/

// FILE: database.cpp
// CLASS implemented: database (see database.h for documentation)

// INVARIANT for the database ADT:
//   1. The items in the database are stored in a dynamic array, where each entry of the array includes
//      a company name, a pointer to the head of the linked list of products, and a
//      a pointer to the tail of the linked list of products
//   2. The number of slots in the array of companies is stored in member varibale aloc_slots
//   3. The number of used slots of the array of companies is stored in member varibale used_slots


#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"
//#include <algorithm>


//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace lab7_avattuone
{
    // Constructor the database
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
    // Copy constructor fro the database
    database::database(const database &src) 
    {
        Debug("Copy constructor..." << std::endl);

        // allocates memory for the company array
        this->company_array = new company[src.aloc_slots];
        // sets every element in the company array equal to each company from the source array
        for(size_type i = 0; i < src.used_slots; i++) {
           this->company_array[i] = src.company_array[i];
        }
        // sets used_slots and alloc_slots equal to have the same values as in the source object
        this->aloc_slots = src.aloc_slots;
        this->used_slots = src.used_slots;
    }
    
    // assignment operator for the database
    database& database::operator= (const database &rhs) 
    {
        Debug("Assignment operator..." << std::endl);

        // prevents self-assignment
        if(this != &rhs) {
            // deletes the old information stored in the company array
            delete[] company_array;
            // allocates memory for the company array
            this->company_array = new company[rhs.aloc_slots];
             // sets every element in the company array equal to each company from the source array
            for(size_type i = 0; i < rhs.used_slots; i++) {
                company_array[i] = rhs.company_array[i];
            }
            // sets used_slots and alloc_slots equal to have the same values as in the source object
            this->used_slots = rhs.used_slots;
            this->aloc_slots = rhs.aloc_slots;
        }
        return *this;
    }
    
    // Destructor fot the database
    database::~database() {
        // deallocates all the memory in the company array and sets aloc_slots and used_slots to 0 to prevent errors
        delete[] company_array;
        aloc_slots = 0;
        used_slots = 0;
    }
    
    // Allocates the inputted amount of memory to the company_array
    void database::reserve(size_type new_capacity) {
        Debug("Reserve..." << std::endl);

        if (new_capacity == aloc_slots)
            return; // The allocated memory is already the right size.
        
        if (new_capacity < used_slots)
            new_capacity = used_slots; // Canít allocate less than we are using.
        
        // allocates memory to a new array and copies the data from company_array into it
        company* new_array = new company[new_capacity];
        for (size_type i = 0; i < used_slots; i++) {
            new_array[i] = company_array[i];
        }
        // deallocates old array
        delete[] company_array;
        // sets company_array equal to the newly allocated array
        company_array = new_array;
        aloc_slots = new_capacity;
    }
    
    // Inserts the inputted company into the company array
    //      Returns true for a successful insertion, and false if there's already a company with the same name in the database
    bool database::insert_company(const std::string &entry) {
        
        Debug("Insert company..." << std::endl);

        assert(entry.length() > 0);
        
        size_type pos = search_company(entry);
        
        // If you find a company that is false, because there are duplicates
        if (pos != COMPANY_NOT_FOUND) {
            return false;
        }

        // allocates more memory if needed (doulbes it to prevent frequent size reallocations)
        if (used_slots == aloc_slots)
        {
            reserve(used_slots*2);
        }
        
        // creates a new company object and puts it one after the last used index in company_array
        company_array[used_slots++] = company(entry);
        return true;
    }
    
    // Inserts the inputted item into the inputted company
    // Returns true if the item is successfully added to the company
    // Returns false if the company isn't in the database or if the company already has the inputted product in its list of products
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {
        Debug("Insert item..." << std::endl);

        assert(company.length() > 0 && product_name.length() > 0);

        // searches for the position of the inputted company
        size_type pos = search_company(company);
        
        // if the company isn't in the array return false
        if(pos == COMPANY_NOT_FOUND)
        {
            return false;
        }
        
        // inserts the inputted product into the inputted company
        // if the company already has the inputted product it won't insert it and it'll return false, otherwise it insserts it and returns true
        return company_array[pos].insert(product_name, price);
    }
    
    
    // Removes the inputted company from the array
    //      Returns true if the company is successfully removed
    //      Returns false if the company isn't found in the database
    bool database::erase_company(const std::string &company) {
        
        // finds the index of the inutted company
        size_type company_index = search_company(company);
        
        // if the company isn't in the array then return false
        if(company_index == COMPANY_NOT_FOUND)
        {
            return false;
        }

        // starting at the index of the company to be deleted, shift every element in company_array to the left by 1 to delete the old company and make sure there are no holes in the array
        for(size_type i = company_index; i < used_slots - 1; i++)
        {
            company_array[i] = company_array[i + 1];
        }
        
        used_slots--;
        return true;
    }
    
    // Erases the inputted item from the inputted company
    //      Returns true if the item is successfully erased
    //      Returns false if the company isn't found in the database or if the product isn't found in the company's list of products
    bool database::erase_item(const std::string& cName, const std::string& pName) {
        
        assert(cName.length() > 0 && pName.length() > 0);

        // finds the index of the inutted company
        size_type pos = search_company(cName);

        // if the company isn't in the array then return false
        if(pos == COMPANY_NOT_FOUND)
        {
            return false;
        }

        // erases the inputted product from the company
        // if the product isn't found in the company then it returns false and doesn't erase anything, otherwise it erases it and returns true
        return company_array[pos].erase(pName);
    }
    
    // Returns the index of the inputted company in company_array
    //      If the company isn't found in the database, returns COMPANY_NOT_FOUND
    database::size_type database::search_company(const std::string& company) {
        assert(company.length() > 0);

        // iterates through each element of the array and returns the index of the inputted company
        for(size_type i = 0; i < used_slots; i++)
        {
            if(company_array[i].get_name() == company)
            {
                return i;
            }
        }
        // returns COMPANY_NOT_FOUND constant (equal to -1) if comapny isn't found in the array
        return COMPANY_NOT_FOUND;
    }
    
    
    // Prints out all the products of an inputted company
    //      Returns true if the company is in the database
    //      Returns false if the company isn't found in the database
    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0);

        size_type c_index = search_company(cName);

        if (c_index == COMPANY_NOT_FOUND) {
            return false;
        }
        
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;
        
        return true;
    }
    
    
    // Prints the list of companies currently in the database 
    void database::print_companies() {
        
        std::cout << "Company List" << std::endl;
        for (int i = 0; i < used_slots; i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}

#endif
