// TO-DO for Token.cpp
// Purpose: Implement Token class member functions to manage a C-string token with manual memory management.

// 1. Include header file
//    - Include Token.h to access the class declaration.

// 2. Create a private helper function (optional)
//    - Define a helper function to allocate and copy a C-string, handling null or empty inputs by creating a 1-byte array with a null terminator.

// 3. Implement default constructor
//    - Allocate a 1-byte array for text and set it to a null terminator ('\0') for an empty token.

// 4. Implement parameterized constructor
//    - Allocate memory for text and deep copy the input C-string, handling null or empty inputs by creating an empty token.

// 5. Implement copy constructor
//    - Allocate new memory for text and deep copy the other Token’s C-string.

// 6. Implement move constructor
//    - Transfer ownership of the other Token’s text, then allocate a new 1-byte array with a null terminator for the moved-from object.
//    - Mark as noexcept.

// 7. Implement destructor
//    - Deallocate text using array deletion.

// 8. Implement copy assignment operator
//    - Check for self-assignment, deallocate existing text, allocate new memory, and deep copy the other Token’s C-string.

// 9. Implement move assignment operator
//    - Check for self-assignment, deallocate existing text, transfer ownership of the other Token’s text, and set the moved-from object to an empty token.
//    - Mark as noexcept.

// 10. Implement getFirstChar
//     - Return the first character of text (or null terminator if empty).
//     - Mark as const.

// 11. Implement c_str
//     - Return text as a const C-string.
//     - Mark as const.

// 12. Implement length
//     - Return the length of text using a <cstring> function.
//     - Mark as const.

// 13. Implement print
//     - Write text to the provided ostream.
//     - Mark as const.

// 14. Implement compare (with Token)
//     - Perform case-sensitive comparison with another Token’s text using a <cstring> function.
//     - Return an integer (<0, 0, or >0).
//     - Mark as const.

// 15. Implement compare (with C-string)
//     - Perform case-sensitive comparison with a C-string using a <cstring> function, handling null input as an empty string.
//     - Return an integer (<0, 0, or >0).
//     - Mark as const.

#include "Token.h"

// Private helper: Allocates and copies a C-string, handling null/empty cases
// Note: This is a helper function, not declared in Token.h
char* Token::allocateText(const char* str) {
    if (str == nullptr || str[0] == '\0') {
        char* newText = new char[1];
        newText[0] = '\0';
        return newText;
    }
    size_t len = strlen(str) + 1;
    char* newText = new char[len];
    strcpy(newText, str);
    return newText;
}

// Implements: Token();
// Default Constructor: Empty token
Token::Token() {
    text = new char[1];
    text[0] = '\0';
}

// Implements: Token(const char* str = "");
// Parameterized Constructor: Deep copy of input string
Token::Token(const char* str) {
    text = allocateText(str);
}

// Implements: Token(const Token& other);
// Copy Constructor: Deep copy of other.text
Token::Token(const Token& other) {
    text = allocateText(other.text);
}

// Implements: Token(Token&& other) noexcept;
// Move Constructor: Transfer ownership, leave other empty
Token::Token(Token&& other) noexcept {
    text = other.text;
    other.text = new char[1];
    other.text[0] = '\0';
}

// Implements: ~Token();
// Destructor: Deallocate text
Token::~Token() {
    delete[] text;
}

// Implements: Token& operator=(const Token& other);
// Copy Assignment Operator: Deep copy, handle self-assignment
Token& Token::operator=(const Token& other) {
    if (this != &other) {
        delete[] text; // Deallocate current text
        text = allocateText(other.text);
    }
    return *this;
}

// Implements: Token& operator=(Token&& other) noexcept;
// Move Assignment Operator: Transfer ownership, handle self-assignment
Token& Token::operator=(Token&& other) noexcept {
    if (this != &other) {
        delete[] text; // Deallocate current text
        text = other.text; // Transfer text ownership
        other.text = new char[1];
        other.text[0] = '\0';
    }
    return *this;
}

// Implements: char getFirstChar() const;
// getFirstChar: Return first character (or '\0' if empty)
char Token::getFirstChar() const {
    return text[0];
}

// Implements: const char* c_str() const;
// c_str: Return text as const char*
const char* Token::c_str() const {
    return text;
}

// Implements: size_t length() const;
// length: Return length of text
size_t Token::length() const {
    return strlen(text);
}

// Implements: void print(std::ostream& os) const;
// print: Write text to output stream
void Token::print(std::ostream& os) const {
    os << text;
}

// Implements: int compare(const Token& other) const;
// compare (with Token): Case-sensitive comparison
int Token::compare(const Token& other) const {
    return strcmp(text, other.text);
}

// Implements: int compare(const char* str) const;
// compare (with C-string): Case-sensitive comparison
int Token::compare(const char* str) const {
    return strcmp(text, str ? str : "");
}