// TO-DO for Indexer.cpp
// Purpose: Implement Indexer class methods to manage the text indexing workflow.

// 1. Include necessary headers
//    - Include Indexer.h for class declaration.
//    - Include <fstream> for file reading.
//    - Include <sstream> for tokenization.
//    - Include <cctype> for std::tolower and std::isalpha.
//    - Include <iostream> for error messages and output.

// 2. Implement default constructor
//    - Initialize sections as empty, currentFilename as empty.

// 3. Implement processToken (const char*, int)
//    - Map token to section, check for existing token, update or insert.

// 4. Implement processToken (Token, int)
//    - Map token to section, check for existing token, update or insert.

// 5. Implement processTextFile
//    - Open file, clear index, read lines, tokenize, call processToken.

// 6. Implement clear
//    - Clear all sections and currentFilename.

// 7. Implement isEmpty
//    - Check if all sections are empty.
//    - Mark as const.

// 8. Implement print
//    - Output all sections to ostream.
//    - Mark as const.

// 9. Implement displayAllTokens
//    - Call print(std::cout).
//    - Mark as const.

// 10. Implement listByLength
//     - Display tokens of specified length across all sections.
//     - Mark as const.

// 11. Implement ViewBySection
//     - Display tokens in specified section (by letter).
//     - Mark as const.

#include "Indexer.h"
#include <fstream>
#include <sstream>
#include <cctype>
#include <iostream>

// Implements: Indexer();
// Default constructor: Empty sections
Indexer::Indexer() : sections{}, currentFilename("") {}

// Implements: void processToken(const char* text, int lineNumber);
// processToken: Map to section, update or insert token
void Indexer::processToken(const char* text, int lineNumber) {
    if (!text) return;
    // Determine section (0-25: a-z, 26: non-alpha)
    int section = 26; // Default to non-alpha
    char first = std::tolower(text[0]);
    if (std::isalpha(first)) {
        section = first - 'a';
    }
    // Search for existing token
    DLList& sec = sections[section];
    for (size_t i = 0; i < sec.size(); ++i) {
        IndexedToken& it = sec.getIndexedTokenAt(i);
        if (it.compare(text) == 0) {
            it.appendLineNumber(lineNumber);
            return;
        }
        if (it.compare(text) > 0) {
            // Insert before this position to maintain sort
            sec.addBefore(IndexedToken(text, lineNumber), i);
            return;
        }
    }
    // Append to end if not found
    sec.addBefore(IndexedToken(text, lineNumber), sec.size());
}

// Implements: void processToken(Token token, int lineNumber);
// processToken: Map to section, update or insert token
void Indexer::processToken(Token token, int lineNumber) {
    // Delegate to const char* version
    processToken(token.c_str(), lineNumber);
}

// Implements: void processTextFile(const std::string& filename);
// processTextFile: Read file, tokenize, index tokens
void Indexer::processTextFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }
    clear();
    currentFilename = filename;
    std::string line;
    int lineNumber = 1;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string word;
        while (ss >> word) {
            processToken(word.c_str(), lineNumber);
        }
        ++lineNumber;
    }
    file.close();
}

// Implements: void clear();
// clear: Empty all sections
void Indexer::clear() {
    for (int i = 0; i < 27; ++i) {
        sections[i].clear();
    }
    currentFilename.clear();
}

// Implements: bool isEmpty() const;
// isEmpty: Check if all sections are empty
bool Indexer::isEmpty() const {
    for (int i = 0; i < 27; ++i) {
        if (!sections[i].isEmpty()) {
            return false;
        }
    }
    return true;
}

// Implements: void print(std::ostream& os) const;
// print: Output all sections
void Indexer::print(std::ostream& os) const {
    for (int i = 0; i < 27; ++i) {
        if (!sections[i].isEmpty()) {
            if (i < 26) {
                os << "Section " << char('A' + i) << ":\n";
            } else {
                os << "Section Non-Alpha:\n";
            }
            sections[i].print(os);
            os << "\n";
        }
    }
}

// Implements: void displayAllTokens() const;
// displayAllTokens: Print to std::cout
void Indexer::displayAllTokens() const {
    print(std::cout);
}

// Implements: void listByLength(size_t length) const;
// listByLength: Display tokens of specified length
void Indexer::listByLength(size_t length) const {
    bool found = false;
    for (int i = 0; i < 27; ++i) {
        for (size_t j = 0; j < sections[i].size(); ++j) {
            const IndexedToken& it = sections[i].getIndexedTokenAt(j);
            if (std::strlen(it.getToken().c_str()) == length) {
                if (!found) {
                    std::cout << "Tokens of length " << length << ":\n";
                    found = true;
                }
                it.print(std::cout);
                std::cout << "\n";
            }
        }
    }
    if (!found) {
        std::cout << "No tokens of length " << length << " found.\n";
    }
}

// Implements: void ViewBySection(char section) const;
// ViewBySection: Display tokens in specified section
void Indexer::ViewBySection(char section) const {
    char sec = std::tolower(section);
    int index = 26; // Default to non-alpha
    if (std::isalpha(sec)) {
        index = sec - 'a';
    }
    if (sections[index].isEmpty()) {
        std::cout << "Section " << (index < 26 ? std::string(1, char('A' + index)) : "Non-Alpha") << " is empty.\n";
    } else {
        std::cout << "Section " << (index < 26 ? std::string(1, char('A' + index)) : "Non-Alpha") << ":\n";
        sections[index].print(std::cout);
        std::cout << "\n";
    }
}