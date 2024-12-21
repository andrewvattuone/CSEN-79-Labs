/** 
 * CSEN 79 Lab Code
 * Name: Andrew Vattuone
 * Email: avattuone@scu.edu
*/

// FILE: bag_bst.h (part of the namespace coen79_lab9)
// Behnam Dezfouli, COEN, SCU
//
// TEMPLATE CLASS PROVIDED: bag<Item>
//     (a container template class for a collection of items)
//
// TYPEDEFS for the bag<Item> class:
//   bag<Item>::value_type
//     bag<Item>::value_type is the data type of the items in the bag. It may
//     be any of the C++ built-in types (int, char, etc.), or a class with a
//     default constructor, a copy constructor, an assignment operator, and a
//     less-than operator forming a strict weak ordering.
//
//   bag<Item>::size_type
//     bag<Item>::size_type is the data type of any variable that keeps track
//     of how many items are in a bag.
//
// CONSTRUCTOR for the bag<Item> class:
//   bag( )
//     Postcondition: The bag is empty.
//
// MODIFICATION MEMBER FUNCTIONS for the bag<Item> class:
//   size_type erase(const Item& target)
//     Postcondition: All copies of target have been removed from the bag. The
//     return value is the number of copies removed (which could be zero).
//
//   bool erase_one(const Item& target)
//     Postcondition: If target was in the bag, then one copy of target has been
//     removed from the bag; otherwise the bag is unchanged. A true return value
//     indicates that one copy was removed; false indicates that nothing was
//     removed.
//
//   void insert(const Item& entry)
//     Postcondition: A new copy of entry has been inserted into the bag.
//
//   void operator +=(const bag& addend)
//     Postcondition: Each item in addend has been added to this bag.
//
// CONSTANT MEMBER FUNCTIONS for the bag<Item> class:
//   size_type size( ) const
//     Postcondition: Return value is the total number of items in the bag.
//
//   size_type count(const Item& target) const
//     Postcondition: Return value is number of times target is in the bag.
//
// NONMEMBER FUNCTIONS for the bag class:
//   bag operator +(const bag& b1, const bag& b2)
//     Postcondition: The bag returned is the union of b1 and b2.
//
// VALUE SEMANTICS for the bag class:
//   Assignments and the copy constructor may be used with bag objects.
//
// DYNAMIC MEMORY USAGE by the bag: 
//   If there is insufficient dynamic memory, then the following functions
//   throw bad_alloc: The constructors, insert, operator +=, operator +, and
//   the assignment operator.

#ifndef COEN79_BST_BAG
#define COEN79_BST_BAG

#include <cstdlib>     // Provides NULL and size_t
#include "bintree.h"   // Provides binary_tree_node and related functions

namespace lab9_avattuone
{
    template <class Item>
    class bag
    {
    public:
        // TYPEDEFS
        typedef std::size_t size_type;
        typedef Item value_type;
        
        // CONSTRUCTORS and DESTRUCTOR
        bag( ) { root_ptr = NULL; }
        bag(const bag& source);
        ~bag( );
        
        // MODIFICATION functions
        size_type erase(const Item& target);
        bool erase_one(const Item& target);
        void insert(const Item& entry);
        void operator +=(const bag& addend);
        void operator =(const bag& source);
        
        // CONSTANT functions
        size_type size( ) const;
        size_type count(const Item& target) const;
        void debug( ) const { print(root_ptr, 0); }
        
    private:
        binary_tree_node<Item> *root_ptr; // Root pointer of binary search tree
        void insert_all(binary_tree_node<Item>* addroot_ptr);
    };
    
    // NONMEMBER functions for the bag<Item> template class
    template <class Item>
    bag<Item> operator +(const bag<Item>& b1, const bag<Item>& b2);
}



// -----------------------------
// *** IMPLEMENTATION ***
// -----------------------------

namespace lab9_avattuone
{
    
#pragma mark - Toolkit Function Implementation
    
    
    // ---------------------------------
    // Toolkit functions for implementing bag class using BST
    // Note: These are not functions of the bag class
    // ---------------------------------
    
    // Removes the node with the largest value from the inputted binary tree
    template <class Item>
    void bst_remove_max(binary_tree_node<Item>*& root_ptr, Item& removed)
    // Precondition: root_ptr is a root pointer of a non-empty binary
    // search tree.
    // Postcondition: The largest item in the binary search tree has been
    // removed, and root_ptr now points to the root of the new (smaller)
    // binary search tree. The reference parameter, removed, has been set
    // to a copy of the removed item.
    {
        binary_tree_node<Item> *oldroot_ptr;
        
        assert(root_ptr != NULL);
        
        // If there's a right subtree, then the max node will be in that subtree so keep traversing through it
        if (root_ptr->right( ) != NULL)
            bst_remove_max(root_ptr->right( ), removed);
        // There's only a left subtree or there's only one node in the tree, so by definition the current node is the max
        else
        {
            // stores the data sotred in the node to be removed
            removed = root_ptr->data();
            // set the current equal to the left child and delete the old current node
            oldroot_ptr = root_ptr;
            root_ptr = root_ptr->left();
            delete oldroot_ptr;
        }
    }
    
    // Removes one node that has the inputted target value
    template <class Item>
    bool bst_remove(binary_tree_node<Item>*& root_ptr, const Item& target)
    // Precondition: root_ptr is a root pointer of a binary search tree
    // or may be NULL for an empty tree).
    // Postcondition: If target was in the tree, then one copy of target
    // has been removed, and root_ptr now points to the root of the new
    // (smaller) binary search tree. In this case the function returns true.
    // If target was not in the tree, then the tree is unchanged (and the
    // function returns false).
    {
        binary_tree_node<Item> *oldroot_ptr;
        
        if (root_ptr == NULL)
        {   // Empty tree
            // Target wasn't found in the tree, so return false
            return false;
        }
        
        if (target < root_ptr->data( ))
        {   // Continue looking in the left subtree
            
            return bst_remove(root_ptr->left(), target);
        }
        
        if (target > root_ptr->data( ))
        {   // Continue looking in the right subtree
            
            return bst_remove(root_ptr->right(), target);
        }
        
        // Target found
        if (root_ptr->left( ) == NULL)
        {   // Target was found and there is no left subtree, so we can
            // remove this node, making the right child be the new root.

            oldroot_ptr = root_ptr;
            root_ptr = root_ptr->right();
            delete oldroot_ptr;
            return true;
        }
        
        // If code reaches this point, then we must remove the target from
        // the current node. We'll actually replace this target with the
        // maximum item of left subtree.

        bst_remove_max(root_ptr->left(), root_ptr->data());
        
        return true;
    }
    
    // Removes all instances of the target node from the tree
    template <class Item>
    typename bag<Item>::size_type bst_remove_all (binary_tree_node<Item>*& root_ptr, const Item& target)
    // Precondition: root_ptr is a root pointer of a binary search tree
    // or may be NULL for an empty tree).
    // Postcondition: All copies of target have been removed from the tree
    // and root_ptr now points to the root of the new
    // (smaller) binary search tree. The return value tells how many copies
    // of the target were removed.
    {
        binary_tree_node<Item> *oldroot_ptr;
        
        if (root_ptr == NULL)
        {   // Empty tree
            // Target wasn't found in the tree, so return false
            return 0;
        }
        
        if (target < root_ptr->data( ))
        {   // Continue looking in the left subtree
            
            return bst_remove_all(root_ptr->left(), target);
            
        }
        
        if (target > root_ptr->data( ))
        {   // Continue looking in the right subtree
            
            return bst_remove_all(root_ptr->right(), target);
        }
        
        if (root_ptr->left( ) == NULL)
        {   // Target was found and there is no left subtree, so we can
            // remove this node, making the right child be the new root.

            oldroot_ptr = root_ptr;
            root_ptr = root_ptr->right();
            delete oldroot_ptr;
            return 1;
        }
        
        // If code reaches this point, then we must remove the target from
        // the current node. We'll actually replace this target with the
        // maximum item in our left subtree. We then continue
        // searching for more copies of the target to remove.
        // This continued search must start at the current root (since
        // the maximum element that we moved up from our left subtree
        // might also be a copy of the target).
        
        bst_remove_max(root_ptr->left(), root_ptr->data());
        
        return 1 + bst_remove_all(root_ptr, target);
    }
    
    
#pragma mark - Member Function Implementation

    
    // ---------------------------------
    // Member functions of the bag class
    // ---------------------------------

    // Copy constructor for bag
    // NOTE: The copy constructor needs to make a new copy of the source’s
    // tree, and point root_ptr to the root of this copy
    // Use the tree_copy function to do the copying
    template <class Item>
    bag<Item>::bag(const bag<Item>& source)
    // Library facilities used: bintree.h
    {
        // copies every element from the source tree into the current bag's tree
        root_ptr = tree_copy(source.root_ptr);
    }
    
    
    // Destructor for bag
    template <class Item>
    bag<Item>::~bag( )
    // Header file used: bintree.h
    {
        // clears all the elements from the bag's tree
        tree_clear(root_ptr);
    }
    
    
    // Returns the total number of elements in the bag
    template <class Item>
    typename bag<Item>::size_type bag<Item>::size( ) const
    // Header file used: bintree.h
    {
        // returns the total number of nodes in the bag's tree
        return tree_size(root_ptr);
    }
    
    
    // Insert
    // Case 1: First handle this special case: When the first entry is inserted,
    //         simply call root_ptr = new binary_tree_node<Item>(entry)
    // Case 2: There are already some other entries in the tree:
    //    • We pretend to search for the exact entry that we are trying to insert
    //    • We stop the search just before the cursor falls off the bottom of the tree,
    //      and we insert the new entry at the spot where the cursor was about to fall off
    template <class Item>
    void bag<Item>::insert(const Item& entry)
    // Header file used: bintree.h
    {
        binary_tree_node<Item> *cursor = root_ptr;
        bool done = false;
        
        // If the tree is empty then insert the element as the first node in the tree
        if (root_ptr == NULL)
        {
            root_ptr = new binary_tree_node<Item>(entry);
            return;
        }
        
        // Tree has at least 1 element
        do
        {
            if (cursor->data( ) >= entry)
            {   // Go left
                
                // If there's no left child, then insert the node there since it's supposed to go there according to BST organization
                if (cursor->left() == NULL)
                {
                    cursor->left() = new binary_tree_node<Item>(entry);
                    done = true;
                }
                // Keep searching for the left subtree to find a spot to insert the node
                else
                {
                    cursor = cursor->left();
                }
            }
            else
            {   // Go right

                // If there's no right child, then insert the node there since it's supposed to go there according to BST organization
                if (cursor->right() == NULL)
                {
                    cursor->right() = new binary_tree_node<Item>(entry);
                    done = true;
                }
                // Keep searching for the left subtree to find a spot to insert the node
                else
                {
                    cursor = cursor->right();
                }
            }
        }   while (!done);
    }
    
    
    // Count how many instances of the inputted target are in the bag
    template <class Item>
    typename bag<Item>::size_type bag<Item>::count(const Item& target) const
    {
        size_type answer = 0;
        binary_tree_node<Item> *cursor = root_ptr;
        
        while (cursor != NULL)
        {
            if (cursor->data( ) < target)
                // Go right.
                cursor = cursor->right( );
            else
            {
                // If the current node has a data value equal to the target, increase count by 1
                if (cursor->data() == target)
                {
                    ++answer;
                }
                // Go left since any duplicates of target can only be in the left subtree
                cursor = cursor->left();
            }
        }
        return answer;
    }
    
    // Erase all instances of the target from the bag
    template <class Item>
    typename bag<Item>::size_type bag<Item>::erase(const Item& target)
    {
        // Remove all nodes that have the target data value from the tree
        return bst_remove_all(root_ptr, target);
    }
    
    // Erase one instance of the target from the bag
    template <class Item>
    bool bag<Item>::erase_one(const Item& target)
    {
        // Remove one node that has the target data value from the tree
        return bst_remove(root_ptr, target);
    }
    
    
    // The assignment operator:
    // 1. First check if it is a self-assignment by comparing (this == &source): If yes, then return
    // 2. If there is no self-assignment, then before we copy the source tree we must release all
    //    memory used by the nodes of the current tree
    //    Use tree_clear to release memory
    template <class Item>
    void bag<Item>::operator =(const bag<Item>& source)
    // Header file used: bintree.h
    {
        // self-assignment so don't reassign
        if (this == &source || root_ptr == source.root_ptr)
        {
            return;
        }

        // erase the current bag's tree and set it equal to the source tree
        tree_clear(root_ptr);
        root_ptr = tree_copy(source.root_ptr);
    }
    
    // overloaded += operator
    template <class Item>
    void bag<Item>::operator +=(const bag<Item>& addend)
    {
        // if the addend bag shares the same tree as the current bag
        if (root_ptr == addend.root_ptr)
        {
            // make a copy of the tree and then do insert_all since otherwise you'd be inserting into the same bag you're trying to read values from
            bag<Item> copy = addend;
            insert_all(copy.root_ptr);
        }
        // bags use different trees
        else
            // insert all the elements from the addend tree to the tree of the current bag
            insert_all(addend.root_ptr);
    }
    
    // overloaded + operator
    template <class Item>
    bag<Item> operator +(const bag<Item>& b1, const bag<Item>& b2)
    {
        // creates a new bag, adds b1 and b2 to that bag, and returns the new bag
        bag<Item> sum;
        sum += b1;
        sum += b2;
        return sum;
    }
    
    // inserts all the items from one tree into the current tree
    template <class Item>
    void bag<Item>::insert_all(binary_tree_node<Item>* addroot_ptr)
    // Precondition: addroot_ptr is the root pointer of a binary search tree that
    // is separate for the binary search tree of the bag that activated this
    // method.
    // Postcondition: All the items from the addroot_ptr's binary search tree
    // have been added to the binary search tree of the bag that activated this
    // method.
    {
        // as long as the addroot tree isn't empty, keep going through it and inserting items from it into the current tree
        if (addroot_ptr != NULL)
        {
            // preorder traversal is used to add the elements
            insert(addroot_ptr->data());
            insert_all(addroot_ptr->left());
            insert_all(addroot_ptr->right());
        }
    }

}

#endif
