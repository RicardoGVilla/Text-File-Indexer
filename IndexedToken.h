```
// TO-DO for IndexedToken.h
// Purpose: Declare the IndexedToken class to aggregate a Token and its list of line numbers.

// 1. Set up include guard
//    - Add header guard to prevent multiple inclusions.

// 2. Include necessary headers
//    - Include Token.h for Token member.
//    - Include IntList.h for IntList member.
//    - Include <ostream> for print method.
//    - Include <cstring> for std::strcmp in compare.

// 3. Declare IndexedToken class
//    - Define private members: token (Token), lines (IntList).

// 4. Declare constructors
//    - Parameterized constructor (const char*, int): Initialize token and add lineNumber.
//    - Parameterized constructor (Token, int): Initialize token and add lineNumber.
//    - Copy constructor: Deep copy (defaulted).
//    - Move constructor: Transfer ownership (defaulted, noexcept).

// 5. Declare destructor
//    - Defaulted to delegate to Token and IntList.

// 6. Declare assignment operators
//    - Copy assignment: Deep copy (defaulted).
//    - Move assignment: Transfer ownership (defaulted, noexcept).

// 7. Declare public methods
//    - appendLineNumber: Add lineNumber to lines.
//    - getToken (const): Return token by const reference.
//    - getLineNumbers (const): Return lines by const reference.
//    - print (const): Output token and lines to ostream.
//    - compare (const char*, const): Compare token’s text with C-string.
//    - compare (const IndexedToken&, const): Compare token with other.token.

// 8. Close include guard

#ifndef INDEXEDTOKEN_H
#define INDEXEDTOKEN_H

#include "Token.h"
#include "IntList.h"
#include <ostream>
#include <cstring>

class IndexedToken {
private:
    Token token;        // The token
    IntList lines;      // List of line numbers

public:
    // Constructors
    IndexedToken(const char* text, int lineNumber);     // Initialize with C-string and line number
    IndexedToken(Token token, int lineNumber);          // Initialize with Token and line number
    IndexedToken(const IndexedToken& other) = default;  // Copy constructor: Deep copy
    IndexedToken(IndexedToken&& other) noexcept = default; // Move constructor: Transfer ownership

    // Destructor
    ~IndexedToken() = default;                          // Defaulted to delegate to Token and IntList

    // Assignment operators
    IndexedToken& operator=(const IndexedToken& other) = default; // Copy assignment: Deep copy
    IndexedToken& operator=(IndexedToken&& other) noexcept = default; // Move assignment: Transfer ownership

    // Public methods
    void appendLineNumber(size_t lineNumber);           // Append lineNumber to lines
    const Token& getToken() const;                      // Return token by const reference
    const IntList& getLineNumbers() const;              // Return lines by const reference
    void print(std::ostream& os) const;                 // Output token and lines to stream
    int compare(const char* other) const;               // Compare token’s text with C-string
    int compare(const IndexedToken& other) const;       // Compare token with other.token
};

#endif // INDEXEDTOKEN_H