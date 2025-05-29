// TO-DO for Indexer.h
// Purpose: Declare the Indexer class to manage the text indexing workflow with 27 sorted DLList sections.

// 1. Set up include guard
//    - Add header guard to prevent multiple inclusions.

// 2. Include necessary headers
//    - Include <string> for currentFilename.
//    - Include <ostream> for print method.
//    - Include DLList.h for sections.
//    - Include IndexedToken.h and Token.h for token processing.

// 3. Declare Indexer class
//    - Define private members: sections (DLList[27]), currentFilename (std::string).
//    - Declare private methods: processToken (const char*, int), processToken (Token, int).

// 4. Declare constructors
//    - Default constructor: Initialize 27 empty sections.
//    - Copy constructor: Delete for efficiency.
//    - Move constructor: Defaulted (noexcept).

// 5. Declare destructor
//    - Defaulted to delegate to sections.

// 6. Declare assignment operators
//    - Copy assignment: Delete for efficiency.
//    - Move assignment: Defaulted (noexcept).

// 7. Declare public methods
//    - processTextFile: Read and index tokens from file.
//    - clear: Empty all sections.
//    - isEmpty (const): Check if index is empty.
//    - print (const): Output entire index to ostream.
//    - displayAllTokens (const): Call print(std::cout).
//    - listByLength (const): Display tokens of specified length.
//    - ViewBySection (const): Display tokens in specified section.

// 8. Close include guard

#ifndef INDEXER_H
#define INDEXER_H

#include <string>
#include <ostream>
#include "DLList.h"
#include "IndexedToken.h"
#include "Token.h"

class Indexer {
private:
    DLList sections[27];            // 27 sections (0-25: a-z, 26: non-alpha)
    std::string currentFilename;    // Name of indexed file
    void processToken(const char* text, int lineNumber); // Process C-string token
    void processToken(Token token, int lineNumber);      // Process Token object

public:

    // Constructors
    Indexer();                              // Default constructor: Empty sections (27)
    Indexer(const Indexer& other) = delete; // Copy constructor: Deleted
    Indexer(Indexer&& other) noexcept = default; // Move constructor: Defaulted

    // Destructor
    ~Indexer() = default;

    // Assignment operators
    Indexer& operator=(const Indexer& other) = delete;   // Copy assignment: Deleted
    Indexer& operator=(Indexer&& other) noexcept = default; // Move assignment: Defaulted

    // Public methods
    void processTextFile(const std::string& filename);  // Read and index file
    void clear();                           // Clear all sections
    bool isEmpty() const;                   // Check if index is empty
    void print(std::ostream& os) const;    // Output entire index
    void displayAllTokens() const;          // Print to std::cout
    void listByLength(size_t length) const; // Display tokens by length
    void ViewBySection(char section) const; // Display section by letter
};

#endif // INDEXER_H