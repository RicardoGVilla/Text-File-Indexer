```cpp
// TO-DO for DLList.h
// Purpose: Declare the DLList class to manage a doubly linked list of IndexedToken objects.

// 1. Set up include guard
//    - Add header guard to prevent multiple inclusions.

// 2. Include necessary headers
//    - Include IndexedToken.h for IndexedToken data.
//    - Include <ostream> for print method.
//    - Include <stdexcept> for std::out_of_range.

// 3. Declare DLList class
//    - Define private nested Node class: prev (Node*), data (IndexedToken), next (Node*).
//    - Define private members: head (Node*), tail (Node*), nodeCount (size_t).
//    - Declare private helper: getNodeAt.

// 4. Declare constructors
//    - Default constructor: Initialize empty list.
//    - Copy constructor: Deep copy.
//    - Move constructor: Transfer ownership (noexcept).

// 5. Declare destructor
//    - Deallocate all nodes.

// 6. Declare assignment operators
//    - Copy assignment: Deep copy, handle self-assignment.
//    - Move assignment: Transfer ownership, handle self-assignment (noexcept).

// 7. Declare public methods
//    - addBefore: Insert IndexedToken before pos, throw std::out_of_range.
//    - remove: Remove node at pos, throw std::out_of_range.
//    - getIndexedTokenAt (non-const): Return IndexedToken& at pos, throw std::out_of_range.
//    - getIndexedTokenAt (const): Return const IndexedToken& at pos, throw std::out_of_range.
//    - clear: Remove all nodes.
//    - size (const): Return nodeCount.
//    - isEmpty (const): Check if list is empty.
//    - print (const): Output all IndexedToken objects to ostream.

// 8. Close include guard

#ifndef DLLIST_H
#define DLLIST_H

#include "IndexedToken.h"
#include <ostream>
#include <stdexcept>

class DLList {
private:
    // Nested Node class
    class Node {
    public:
        Node* prev;             // Pointer to previous node
        IndexedToken data;      // IndexedToken data
        Node* next;             // Pointer to next node
        Node(const IndexedToken& data, Node* prv = nullptr, Node* nxt = nullptr)
            : prev(prv), data(data), next(nxt) {}
    };

    Node* head;                 // Pointer to first node
    Node* tail;                 // Pointer to last node
    size_t nodeCount;           // Number of nodes
    Node* getNodeAt(size_t pos) const; // Helper to get node at position

public:
    // Constructors
    DLList();                               // Default constructor: Empty list
    DLList(const DLList& other);            // Copy constructor: Deep copy
    DLList(DLList&& other) noexcept;        // Move constructor: Transfer ownership

    // Destructor
    ~DLList();

    // Assignment operators
    DLList& operator=(const DLList& other);         // Copy assignment: Deep copy
    DLList& operator=(DLList&& other) noexcept;     // Move assignment: Transfer ownership

    // Public methods
    void addBefore(IndexedToken data, size_t pos);  // Insert before pos
    bool remove(size_t pos);                        // Remove at pos
    IndexedToken& getIndexedTokenAt(size_t pos);    // Return non-const reference at pos
    const IndexedToken& getIndexedTokenAt(size_t pos) const; // Return const reference at pos
    void clear();                                   // Remove all nodes
    size_t size() const;                            // Return nodeCount
    bool isEmpty() const;                           // Check if empty
    void print(std::ostream& os) const;             // Output all IndexedTokens
};

#endif // DLLIST_H