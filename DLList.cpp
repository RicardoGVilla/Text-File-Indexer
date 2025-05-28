```cpp
// TO-DO for DLList.cpp
// Purpose: Implement DLList class member functions to manage a doubly linked list of IndexedToken objects.

// 1. Include header file
//    - Include DLList.h to access the class declaration.

// 2. Implement private helper function
//    - getNodeAt: Return node at pos, throw std::out_of_range if invalid.

// 3. Implement default constructor
//    - Initialize empty list: head = nullptr, tail = nullptr, nodeCount = 0.

// 4. Implement copy constructor
//    - Deep copy other’s list, node by node.

// 5. Implement move constructor
//    - Transfer head, tail, nodeCount; set other to empty (noexcept).

// 6. Implement destructor
//    - Deallocate all nodes.

// 7. Implement copy assignment operator
//    - Check self-assignment, clear current list, deep copy other.

// 8. Implement move assignment operator
//    - Check self-assignment, clear current list, transfer other’s data (noexcept).

// 9. Implement addBefore
//    - Insert new node before pos, update links, throw std::out_of_range.

// 10. Implement remove
//     - Remove node at pos, update links, return true, throw std::out_of_range.

// 11. Implement getIndexedTokenAt (non-const)
//     - Return IndexedToken& at pos, throw std::out_of_range.

// 12. Implement getIndexedTokenAt (const)
//     - Return const IndexedToken& at pos, throw std::out_of_range.

// 13. Implement clear
//     - Deallocate all nodes, reset to empty state.

// 14. Implement size
//     - Return nodeCount.
//     - Mark as const.

// 15. Implement isEmpty
//     - Return true if nodeCount == 0.
//     - Mark as const.

// 16. Implement print
//     - Output each IndexedToken to ostream.
//     - Mark as const.

#include "DLList.h"

// Implements: Node* getNodeAt(size_t pos) const;
// Helper: Return node at pos, throw if invalid
DLList::Node* DLList::getNodeAt(size_t pos) const {
    if (pos >= nodeCount) {
        throw std::out_of_range("Position out of range");
    }
    Node* current = head;
    for (size_t i = 0; i < pos; ++i) {
        current = current->next;
    }
    return current;
}

// Implements: DLList();
// Default constructor: Empty list
DLList::DLList() : head(nullptr), tail(nullptr), nodeCount(0) {}

// Implements: DLList(const DLList& other);
// Copy constructor: Deep copy
DLList::DLList(const DLList& other) : head(nullptr), tail(nullptr), nodeCount(0) {
    Node* current = other.head;
    while (current) {
        addBefore(current->data, nodeCount); // Appends to end
        current = current->next;
    }
}

// Implements: DLList(DLList&& other) noexcept;
// Move constructor: Transfer ownership
DLList::DLList(DLList&& other) noexcept
    : head(other.head), tail(other.tail), nodeCount(other.nodeCount) {
    other.head = nullptr;
    other.tail = nullptr;
    other.nodeCount = 0;
}

// Implements: ~DLList();
// Destructor: Deallocate all nodes
DLList::~DLList() {
    clear();
}

// Implements: DLList& operator=(const DLList& other);
// Copy assignment: Deep copy, handle self-assignment
DLList& DLList::operator=(const DLList& other) {
    if (this != &other) {
        clear();
        Node* current = other.head;
        while (current) {
            addBefore(current->data, nodeCount); // Appends to end
            current = current->next;
        }
    }
    return *this;
}

// Implements: DLList& operator=(DLList&& other) noexcept;
// Move assignment: Transfer ownership, handle self-assignment
DLList& DLList::operator=(DLList&& other) noexcept {
    if (this != &other) {
        clear();
        head = other.head;
        tail = other.tail;
        nodeCount = other.nodeCount;
        other.head = nullptr;
        other.tail = nullptr;
        other.nodeCount = 0;
    }
    return *this;
}

// Implements: void addBefore(IndexedToken data, size_t pos);
// addBefore: Insert before pos, throw if invalid
void DLList::addBefore(IndexedToken data, size_t pos) {
    if (pos > nodeCount) {
        throw std::out_of_range("Position out of range");
    }
    Node* newNode = new Node(data);
    if (nodeCount == 0) {
        // Empty list
        head = tail = newNode;
    } else if (pos == 0) {
        // Insert at head
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    } else if (pos == nodeCount) {
        // Insert at tail
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    } else {
        // Insert in middle
        Node* current = getNodeAt(pos);
        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
    }
    ++nodeCount;
}

// Implements: bool remove(size_t pos);
// remove: Remove at pos, throw if invalid
bool DLList::remove(size_t pos) {
    if (pos >= nodeCount) {
        throw std::out_of_range("Position out of range");
    }
    Node* current = getNodeAt(pos);
    if (nodeCount == 1) {
        // Single node
        head = tail = nullptr;
    } else if (current == head) {
        // Remove head
        head = head->next;
        head->prev = nullptr;
    } else if (current == tail) {
        // Remove tail
        tail = tail->prev;
        tail->next = nullptr;
    } else {
        // Remove in middle
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }
    delete current;
    --nodeCount;
    return true;
}

// Implements: IndexedToken& getIndexedTokenAt(size_t pos);
// getIndexedTokenAt: Return non-const reference at pos
IndexedToken& DLList::getIndexedTokenAt(size_t pos) {
    return getNodeAt(pos)->data;
}

// Implements: const IndexedToken& getIndexedTokenAt(size_t pos) const;
// getIndexedTokenAt: Return const reference at pos
const IndexedToken& DLList::getIndexedTokenAt(size_t pos) const {
    return getNodeAt(pos)->data;
}

// Implements: void clear();
// clear: Remove all nodes
void DLList::clear() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
    nodeCount = 0;
}

// Implements: size_t size() const;
// size: Return nodeCount
size_t DLList::size() const {
    return nodeCount;
}

// Implements: bool isEmpty() const;
// isEmpty: Check if empty
bool DLList::isEmpty() const {
    return nodeCount == 0;
}

// Implements: void print(std::ostream& os) const;
// print: Output all IndexedTokens
void DLList::print(std::ostream& os) const {
    Node* current = head;
    while (current) {
        current->data.print(os);
        if (current->next) {
            os << "\n";
        }
        current = current->next;
    }
}