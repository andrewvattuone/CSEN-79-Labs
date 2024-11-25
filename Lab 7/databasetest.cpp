/** 
 * CSEN 79 Lab Code
 * Name: Andrew Vattuone
 * Email: avattuone@scu.edu
*/



#include <iostream>
#include "database.h"
#include <string>

using namespace lab7_avattuone;

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    // Constructor test
    cout << "Testing constructor" << endl << endl;
    database* database1 = new database;


    // Company insertion tests and printing tests
    cout << "Testing if insertion works correclty" << endl;
    database1->insert_company("Intel");
    database1->insert_company("Nvidia");
    cout << endl;

    cout << "Testing if printing database works correclty" << endl;
    database1->print_companies(); // Intel and Nvidia should be in the list
    cout << endl;

    cout << "Inserting companies to invoke reserve" << endl;
    database1->insert_company("Cypress");
    cout << "Printing database1" << endl;
    database1->print_companies(); // Cypress should be added to list
    cout << endl;

    cout << "Inserting duplicate company name (no company should be added)" << endl;
    database1->insert_company("Cypress");
    cout << "Printing database1" << endl;
    database1->print_companies(); // List should remain unchanged from previous test
    cout << endl;


    // Product insertion and product printing tests
    cout << "Testing product insertion and product printing" << endl;
    database1->insert_item("Intel", "Core i7", 300);
    database1->insert_item("Intel", "Core i5", 200);
    database1->print_items_by_company("Intel");

    cout << "Testing duplicate product insertion (no item should be added)" << endl;
    database1->insert_item("Intel", "Core i7", 300);
    database1->print_items_by_company("Intel"); // Product list should remain unchanged from previous test

    cout << "Testing if printing out the items of 2 different companies works correctly" << endl;
    database1->insert_company("Apple");
    cout << "Inserting product names" << endl;
    database1->insert_item("Apple", "iPhone 6", 400);
    database1->insert_item("Apple", "iPhone X", 900);

    cout << "Printing out the poducts of Intel and Apple" << endl;
    // items should be printed correclty with no errors
    database1->print_items_by_company("Apple");
    database1->print_items_by_company("Intel");

    cout << "Testing if printing out a company with no products works correclty" << endl;
    database1->print_items_by_company("Cypress"); // Nothing should be printed
    cout << endl;

    cout << "Testing if inserting an item into a nonexistent company works correctly" << endl;
    cout << database1->insert_item("McDonalds", "burger", 1) << endl; // should print out 0 since  the company doesn't exist
    database1->print_companies(); // List should remain unchanged from previous test
    cout << endl;

    cout << "Testing if printing out the items of a nonexistent company works correctly" << endl;
    cout << database1->print_items_by_company("McDonalds") << endl; // should print out 0 since the company doesn't exist
    cout << endl;


    // Product deletion tests
    cout << "Testing if erasing one product in a company works correctly" << endl;
    database1->erase_item("Intel", "Core i5");
    database1->print_items_by_company("Intel"); // Core i5 should be missing from the list

    cout << "Testing if erasing a previously erased product in a company works correctly" << endl;
    database1->erase_item("Intel", "Core i5");
    database1->print_items_by_company("Intel"); // List should remain unchanged from previous test

    cout << "Testing if erasing a nonexistent product in a company works correctly" << endl;
    cout << database1->erase_item("Intel", "Banana") << endl; // should print out 0 since Banana isn't one of Intel's products
    database1->print_items_by_company("Intel"); // Product list should emain unchanged from preivous test

    cout << "Testing if erasing all items in a company works correctly" << endl;
    database1->erase_item("Intel", "Core i7");
    database1->print_items_by_company("Intel"); // Nothing should be printed out

    cout << "Testing if adding an item to a company where all items were erased works correclty" << endl;
    database1->insert_item("Intel", "Orange", 1);
    database1->print_items_by_company("Intel"); // Apple should be added to the product list

    cout << "Testing if erasing an item belonging to a different company works correctly" << endl;
    cout << database1->erase_item("Intel", "iPhone 6") << endl;
    database1->print_items_by_company("Apple"); // Apple should still have iPhone 6 as one of it's products


    // Company deletion tests
    cout << "Testing if erasing a nonexistent company works correctly" << endl;
    cout << database1->erase_company("McDonalds") << endl; // should print 0 since McDonalds isn't a company in the list
    database1->print_companies(); // No companies should be deleted from the list
    cout << endl;

    cout << "Testing if erasing a company with no items works correctly" << endl;
    database1->erase_company("Cypress");
    database1->print_companies(); // Cypress should be removed from the list
    cout << endl;

    cout << "Testing if erasing a previously deleted company with no items works correclty" << endl;
    database1->erase_company("Cypress");
    database1->print_companies(); // List should remain unchanged from previous test
    cout << endl;

    cout << "Testing if erasing a company with products works correclty" << endl;
    database1->erase_company("Apple");
    database1->print_companies(); // Apple should be removed from the list
    cout << database1->print_items_by_company("Apple") << endl; // should print out 0 since the company doesn't exist anymore
    cout << endl;

    cout << "Testing if erasing a previously deleted company containg multiple items works correclty" << endl;
    database1->erase_company("Apple");
    database1->print_companies(); // List should remain unchanged from previous test
    cout << database1->print_items_by_company("Apple") << endl; // should print out 0 since the company doesn't exist anymore
    cout << endl;

    cout << "Testing if deleting all companies in a database works correclty" << endl;
    database1->erase_company("Intel");
    database1->erase_company("Nvidia");
    // nothing should be printed out
    database1->print_companies();
    cout << endl;

    cout << "Testing if adding a company to a databse where all companies were deleted works correclty" << endl;
    // Should be correclty added to the database with no issues
    database1->insert_company("Mcdonalds");
    database1->print_companies();
    database1->insert_item("Mcdonalds", "Hamburger", 1);
    database1->insert_item("Mcdonalds", "Fries", 10);
    database1->print_items_by_company("Mcdonalds");


    // Database deletion test
    cout << "Testing if deleting a database works correclty" << endl;
    delete database1;
    // nothing should be printed out
    database1->print_companies();
    cout << endl;


    // Copy constructor tests
    cout << "Testing if copy constructor for database works correctly" << endl;
    database* database2 = new database;
    database2->insert_company("Google");
    database2->insert_item("Google", "glass", 1000);
    database2->insert_item("Google", "Android", 0);
    database2->insert_item("Google", "TensorFlow", 0);
    database* database3 = new database(*database2); // calls the copy constructor
    
    // Info printed in both databases should be exactly the same
    database2->print_companies();
    database2->print_items_by_company("Google");
    database3->print_companies();
    database3->print_items_by_company("Google");
    cout << endl;

    cout << "Testing if changing one database doesn't change the other made with the copy constructor" << endl;
    // erases items, adds companies, and adds items in database2 and database3 so data is different
    database2->erase_item("Google", "glass");
    database2->insert_company("Uber");
    database3->insert_company("Boeing");
    database3->insert_item("Google", "banana", 2);
    // Prints out the info in each database to make sure they're different
    cout << "database2 info" << endl; 
    database2->print_companies();
    database2->print_items_by_company("Google");
    database2->print_items_by_company("Uber");
    database2->print_items_by_company("Boeing");
    cout << "database3 info" << endl;
    database3->print_companies();
    database3->print_items_by_company("Google");
    database3->print_items_by_company("Uber");

    cout << "Testing if deleting one database doesn't delete the other" << endl;
    delete database2;
    cout << "database3 after deleting database2" << endl;
    database3->print_companies();
    database3->print_items_by_company("Google");
    database3->print_items_by_company("Uber");
    database2->print_companies(); // makes sure that nothing is printed out when it's deleted


    // Assignment operator tests
    cout << "Testing if assignment operator for database works correclty" << endl;
    database* database4 = new database;
    database4->insert_company("Google");
    database4->insert_item("Google", "glass", 1000);
    database4->insert_item("Google", "Android", 0);
    database4->insert_item("Google", "TensorFlow", 0);
    database* database5 = new database;
    *database5 = *database4; // calls assignemtn operator
    
    // Info printed in both databases should be exactly the same
    database4->print_companies();
    database4->print_items_by_company("Google");
    database5->print_companies();
    database5->print_items_by_company("Google");
    cout << endl;

    cout << "Testing if changing one database doesn't change the other made with the assignment operator" << endl;
    // erases items, adds companies, and adds items in database4 and database5 so data is different
    database4->erase_item("Google", "glass");
    database4->insert_company("Uber");
    database5->insert_company("Boeing");
    database5->insert_item("Google", "banana", 2);
    // Prints out the info in each database to make sure they're different
    cout << "database4 info" << endl;
    database4->print_companies();
    database4->print_items_by_company("Google");
    database4->print_items_by_company("Uber");
    database4->print_items_by_company("Boeing");
    cout << "database5 info" << endl;
    database5->print_companies();
    database5->print_items_by_company("Google");
    database5->print_items_by_company("Uber");

    cout << "Testing if deleting one database doesn't delete the other when created with assignment operator" << endl;
    delete database4;
    cout << "database5 after deleting database4" << endl;
    database5->print_companies();
    database5->print_items_by_company("Google");
    database5->print_items_by_company("Uber");
    database4->print_companies(); // makes sure that nothing is printed out when it's deleted
}
