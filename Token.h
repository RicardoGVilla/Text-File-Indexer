// TO-DO for Token.h
// Purpose: Declare the Token class to represent a lexical token as a null-terminated C-string.

// 1. Set up include guard
//    - Add a header guard to prevent multiple inclusions.

// 2. Include necessary headers
//    - Include <cstring> for string operations (e.g., strlen, strcpy, strcmp).
//    - Include <cctype> for character operations (e.g., isalpha, tolower).
//    - Include <ostream> for output stream in print method.

// 3. Declare Token class
//    - Define a private member char* text to store the dynamically allocated C-string.

// 4. Declare constructors
//    - Default constructor to create an empty token.
//    - Parameterized constructor with const char* parameter (default to empty string) for initializing with a C-string.
//    - Copy constructor to deep copy another Token.
//    - Move constructor (marked noexcept) to transfer ownership.

// 5. Declare destructor
//    - Declare a destructor to deallocate the C-string.

// 6. Declare assignment operators
//    - Copy assignment operator to deep copy another Token.
//    - Move assignment operator (marked noexcept) to transfer ownership.

// 7. Declare utility methods
//    - getFirstChar (const) to return the first character of the token.
//    - c_str (const) to return the C-string.
//    - length (const) to return the string length.
//    - print (const) to output the token to an ostream.
//    - compare (const) to compare with another Token (case-sensitive).
//    - compare (const) to compare with a C-string (case-sensitive).

// 8. Close include guard
//    - End the header guard.

// Adding a header guard to prevent multiple inclusions.
#ifndef TOKEN_H
#define TOKEN_H

#include <cstring>   // String functions: strlen, strcpy, strcmp
#include <cctype>    // Character functions: isalpha, tolower
#include <ostream>   // For std::ostream (used in print)

// Declaring the Token class
class Token {
private:
    // Declaring the private member char* text to store the dynamically allocated C-string
    char* text;

public:
    // Declaring constructors
    Token();                                // Constructor to create an empty token.
    Token(const char* str = "");            // Constructor with const char* parameter (default to empty string) for initializing with a C-string.
    Token(const Token& other);              // Copy constructor to deep copy another Token.
    Token(Token&& other) noexcept;          // Move constructor (marked noexcept) to transfer ownership.

    // Declare default destructor
    ~Token();

    // Declaring assignment operators
    Token& operator=(const Token& other);   // Copy assignment operator to deep copy another Token.
    Token& operator=(Token&& other) noexcept; // Move assignment operator (marked noexcept) to transfer ownership.

    // Declaring utility methods
    char getFirstChar() const;              // getFirstChar (const) to return the first character of the token.
    const char* c_str() const;              // c_str (const) to return the C-string.
    size_t length() const;                  // length (const) to return the string length.
    void print(std::ostream& os) const;     // print (const) to output the token to an ostream.
    int compare(const Token& other) const;  // compare (const) to compare with another Token (case-sensitive).
    int compare(const char* str) const;     // compare (const) to compare with a C-string (case-sensitive).
};

#endif // TOKEN_H