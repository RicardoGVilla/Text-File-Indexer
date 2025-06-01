
// TO-DO for IndexedToken.cpp
// Purpose: Implement IndexedToken class member functions to manage a Token and its line numbers.

// 1. Include header file
//    - Include IndexedToken.h to access the class declaration.

// 2. Implement parameterized constructors
//    - Constructor (const char*, int): Initialize token with text, append lineNumber to lines.
//    - Constructor (Token, int): Initialize token, append lineNumber to lines.

// 3. Implement appendLineNumber
//    - Append lineNumber to lines.

// 4. Implement getToken
//    - Return token by const reference.
//    - Mark as const.

// 5. Implement getLineNumbers
//    - Return lines by const reference.
//    - Mark as const.

// 6. Implement print
//    - Output token followed by lines to ostream.
//    - Mark as const.

// 7. Implement compare (const char*)
//    - Compare token’s text with C-string using std::strcmp.
//    - Mark as const.

// 8. Implement compare (const IndexedToken&)
//    - Compare token with other.token using Token::compare.
//    - Mark as const.

#include "IndexedToken.h"

// Implements: IndexedToken(const char* text, int lineNumber);
// Parameterized constructor: Initialize token with text, append lineNumber
IndexedToken::IndexedToken(const char* text, int lineNumber) : token(text) {
    lines.append(lineNumber);
}

// Implements: IndexedToken(Token token, int lineNumber);
// Parameterized constructor: Initialize with Token, append lineNumber
IndexedToken::IndexedToken(Token token, int lineNumber) : token(std::move(token)) {
    lines.append(lineNumber);
}

// Implements: void appendLineNumber(size_t lineNumber);
// Append: Add lineNumber to lines
void IndexedToken::appendLineNumber(size_t lineNumber) {
    lines.append(lineNumber);
}

// Implements: const Token& getToken() const;
// getToken: Return token by const reference
const Token& IndexedToken::getToken() const {
    return token;
}

// Implements: const IntList& getLineNumbers() const;
// getLineNumbers: Return lines by const reference
const IntList& IndexedToken::getLineNumbers() const {
    return lines;
}

// Implements: void print(std::ostream& os) const;
// print: Output token followed by lines
void IndexedToken::print(std::ostream& os) const {
    token.print(os);
    os << ": ";
    lines.print(os);
}

// Implements: int compare(const char* other) const;
// compare: Compare token’s text with C-string
int IndexedToken::compare(const char* other) const {
    return std::strcmp(token.c_str(), other ? other : "");
}

// Implements: int compare(const IndexedToken& other) const;
// compare: Compare token with other.token
int IndexedToken::compare(const IndexedToken& other) const {
    return token.compare(other.token);
}