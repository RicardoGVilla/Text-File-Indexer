// TO-DO for IntList.cpp
// Purpose: Implement IntList class member functions to manage a dynamic sequence of integers.

// 1. Include header file
//    - Include IntList.h to access the class declaration.

// 2. Implement private helper function
//    - resize: Doubles capacity (starts at 2), reallocates array, copies elements.

// 3. Implement default constructor
//    - Initialize empty state: pData = nullptr, size = 0, capacity = 0.

// 4. Implement copy constructor
//    - Deep copy other’s array, set size and capacity.

// 5. Implement move constructor
//    - Transfer pData, size, capacity; set other to empty (pData = nullptr, size = 0, capacity = 0).
//    - Mark as noexcept.

// 6. Implement destructor
//    - Deallocate pData using delete[].

// 7. Implement copy assignment operator
//    - Check self-assignment, deallocate pData, deep copy other’s array, update size and capacity.

// 8. Implement move assignment operator
//    - Check self-assignment, deallocate pData, transfer other’s pData, size, and capacity; set other to empty.
//    - Mark as noexcept.

// 9. Implement append
//    - Add lineNumber to end, resize if size == capacity, increment size.

// 10. Implement clear
//     - Deallocate pData, set pData = nullptr, size = 0, capacity = 0.

// 11. Implement getSize
//     - Return size.
//     - Mark as const.

// 12. Implement isEmpty
//     - Return true if size == 0.
//     - Mark as const.

// 13. Implement isFull
//     - Return true if size == capacity.
//     - Mark as const.

// 14. Implement print
//     - Write elements to ostream, separated by spaces.
//     - Mark as const.

// 15. Implement getElementAt
//     - Return element at index, throw std::out_of_range if index >= size.
//     - Mark as const.

#include "IntList.h"

// Implements: void resize();
// Private helper: Doubles capacity (starts at 2), reallocates array
void IntList::resize() {
    size_t newCapacity = (capacity == 0) ? 2 : capacity * 2;
    int* newData = new int[newCapacity];
    for (size_t i = 0; i < size; ++i) {
        newData[i] = pData[i];
    }
    delete[] pData;
    pData = newData;
    capacity = newCapacity;
}

// Implements: IntList();
// Default constructor: Empty state
IntList::IntList() : pData(nullptr), size(0), capacity(0) {}

// Implements: IntList(const IntList& other);
// Copy constructor: Deep copy
IntList::IntList(const IntList& other) : size(other.size), capacity(other.capacity) {
    if (other.pData) {
        pData = new int[capacity];
        for (size_t i = 0; i < size; ++i) {
            pData[i] = other.pData[i];
        }
    } else {
        pData = nullptr;
    }
}

// Implements: IntList(IntList&& other) noexcept;
// Move constructor: Transfer ownership, leave other empty
IntList::IntList(IntList&& other) noexcept : pData(other.pData), size(other.size), capacity(other.capacity) {
    other.pData = nullptr;
    other.size = 0;
    other.capacity = 0;
}

// Implements: ~IntList();
// Destructor: Deallocate pData
IntList::~IntList() {
    delete[] pData;
}

// Implements: IntList& operator=(const IntList& other);
// Copy assignment operator: Deep copy, handle self-assignment
IntList& IntList::operator=(const IntList& other) {
    if (this != &other) {
        delete[] pData;
        size = other.size;
        capacity = other.capacity;
        if (other.pData) {
            pData = new int[capacity];
            for (size_t i = 0; i < size; ++i) {
                pData[i] = other.pData[i];
            }
        } else {
            pData = nullptr;
        }
    }
    return *this;
}

// Implements: IntList& operator=(IntList&& other) noexcept;
// Move assignment operator: Transfer ownership, handle self-assignment
IntList& IntList::operator=(IntList&& other) noexcept {
    if (this != &other) {
        delete[] pData;
        pData = other.pData;
        size = other.size;
        capacity = other.capacity;
        other.pData = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}

// Implements: void append(int lineNumber);
// Append: Add lineNumber to end, resize if needed
void IntList::append(int lineNumber) {
    if (size == capacity) {
        resize();
    }
    pData[size] = lineNumber;
    ++size;
}

// Implements: void clear();
// Clear: Deallocate pData, reset to empty state
void IntList::clear() {
    delete[] pData;
    pData = nullptr;
    size = 0;
    capacity = 0;
}

// Implements: size_t getSize() const;
// getSize: Return number of elements
size_t IntList::getSize() const {
    return size;
}

// Implements: bool isEmpty() const;
// isEmpty: Check if size is 0
bool IntList::isEmpty() const {
    return size == 0;
}

// Implements: bool isFull() const;
// isFull: Check if size equals capacity
bool IntList::isFull() const {
    return size == capacity;
}

// Implements: void print(std::ostream& os) const;
// print: Write elements to stream
void IntList::print(std::ostream& os) const {
    for (size_t i = 0; i < size; ++i) {
        os << pData[i];
        if (i < size - 1) {
            os << " ";
        }
    }
}

// Implements: int getElementAt(size_t index) const;
// getElementAt: Return element at index, throw if invalid
int IntList::getElementAt(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return pData[index];
}