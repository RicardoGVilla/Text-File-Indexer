// TO-DO for IntList.h
// Purpose: Declare the IntList class to manage a dynamic sequence of integers.

// 1. Set up include guard
//    - Add header guard to prevent multiple inclusions.

// 2. Include necessary headers
//    - Include <cstddef> for size_t.
//    - Include <ostream> for output stream in print method.
//    - Include <stdexcept> for std::out_of_range in getElementAt.

// 3. Declare IntList class
//    - Define private members: pData (int*), size (size_t), capacity (size_t).
//    - Declare private helper: resize.

// 4. Declare constructors
//    - Default constructor: Initializes empty state.
//    - Copy constructor: Deep copy.
//    - Move constructor: Transfers ownership, leaves other empty (noexcept).

// 5. Declare destructor
//    - Deallocates pData.

// 6. Declare assignment operators
//    - Copy assignment: Deep copy, handles self-assignment.
//    - Move assignment: Transfers ownership, leaves other empty (noexcept).

// 7. Declare public methods
//    - append: Adds lineNumber to end, resizes if needed.
//    - clear: Removes all elements, deallocates memory.
//    - getSize (const): Returns number of elements.
//    - isEmpty (const): Checks if size is 0.
//    - isFull (const): Checks if size equals capacity.
//    - print (const): Outputs list to ostream.
//    - getElementAt (const): Returns element at index, throws std::out_of_range if invalid.

// 8. Close include guard

#ifndef INTLIST_H
#define INTLIST_H

#include <cstddef>
#include <ostream>
#include <stdexcept>

class IntList {
private:
    int* pData;         // Pointer to dynamic array of integers
    size_t size;        // Number of elements stored
    size_t capacity;    // Current allocated size of array
    void resize();      // Private helper to resize array

public:
    // Constructors
    IntList();                              // Default constructor: Empty state
    IntList(const IntList& other);          // Copy constructor: Deep copy
    IntList(IntList&& other) noexcept;      // Move constructor: Transfer ownership

    // Destructor
    ~IntList();

    // Assignment operators
    IntList& operator=(const IntList& other);       // Copy assignment: Deep copy
    IntList& operator=(IntList&& other) noexcept;   // Move assignment: Transfer ownership

    // Public methods
    void append(int lineNumber);                    // Append lineNumber to end
    void clear();                                   // Remove all elements, deallocate
    size_t getSize() const;                         // Return number of elements
    bool isEmpty() const;                           // Check if size is 0
    bool isFull() const;                            // Check if size equals capacity
    void print(std::ostream& os) const;             // Output list to stream
    int getElementAt(size_t index) const;           // Get element at index, throw if invalid
};

#endif // INTLIST_H