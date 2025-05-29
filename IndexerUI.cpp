#include "IndexerUI.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <new>
#include <sstream>
#include <stdexcept>
#include <string>

IndexerUI::IndexerUI() : currentFilename("") {}

void IndexerUI::run() {
    int choice = 0;
    do {
        displayMenu();
        choice = getUserChoice();
        try {
            switch (choice) {
                case 1: processIndexFile(); break;
                case 2: processDisplayAll(); break;
                case 3: processShowByLength(); break;
                case 4: processViewSection(); break;
                case 5: std::cout << "\nExiting program. Goodbye!" << std::endl; break;
            }
        } catch (const std::bad_alloc& e) {
            std::cerr << "\n********\nFATAL ERROR: Memory allocation failed: "
                      << e.what() << "\n********" << std::endl;
            choice = 5;
        } catch (const std::exception& e) {
            std::cerr << "\n********\nERROR: An exception occurred: " << e.what()
                      << "\n********" << std::endl;
        } catch (...) {
            std::cerr << "\n********\nERROR: An unknown exception occurred.\n********"
                      << std::endl;
        }
    } while (choice != 5);
}

void IndexerUI::displayMenu() const {
    std::cout << "\n===== Text File Indexer Menu =====\n"
              << "1. Index a text file\n"
              << "2. Show tokens in all sections\n"
              << "3. Find tokens by length\n"
              << "4. View tokens by section\n"
              << "5. Exit\n"
              << "==================================\n";
}

int IndexerUI::getUserChoice() const {
    int choice = 0;
    std::cout << "Enter your choice (1-5): ";
    while (!(std::cin >> choice) || choice < 1 || choice > 5) {
        std::cerr << "Invalid input. Please enter a number between 1 and 5: ";
        std::cin.clear();
        std::cin.ignore(max_stream_size, '\n');
    }
    std::cin.ignore(max_stream_size, '\n');
    return choice;
}

char IndexerUI::getConfirmation() const {
    char confirm = ' ';
    std::cout << " (y/n): ";
    while (true) {
        std::cin >> confirm;
        std::cin.ignore(max_stream_size, '\n');
        confirm = std::tolower(static_cast<unsigned char>(confirm));
        if (confirm == 'y' || confirm == 'n')
            return confirm;
        std::cerr << "Invalid input. Please enter 'y' or 'n': ";
    }
}

size_t IndexerUI::getSearchLength() const {
    long long inputLength = -1;
    std::cout << "Enter token length (non-negative): ";
    while (true) {
        std::cin >> inputLength;
        if (std::cin.good() && inputLength >= 0) {
            std::cin.ignore(max_stream_size, '\n');
            if (static_cast<unsigned long long>(inputLength) > std::numeric_limits<size_t>::max()) {
                std::cerr << "Input length too large. Please try again: ";
                inputLength = -1;
            } else {
                return static_cast<size_t>(inputLength);
            }
        } else {
            std::cerr << "Invalid input. Please enter a non-negative integer: ";
            std::cin.clear();
            std::cin.ignore(max_stream_size, '\n');
            inputLength = -1;
        }
    }
}

char IndexerUI::getSectionChar() const {
    char sectionChar = ' ';
    std::cout << "Enter section character (A-Z or *): ";
    while (true) {
        std::cin >> sectionChar;
        std::cin.ignore(max_stream_size, '\n');
        if (std::isalpha(static_cast<unsigned char>(sectionChar)) || sectionChar == '*')
            return sectionChar;
        std::cerr << "Invalid input. Please enter A-Z or *: ";
    }
}

std::string IndexerUI::getFileName() const {
    std::string filename;
    std::cout << "Enter the filename to index: ";
    if (!std::getline(std::cin, filename) || filename.empty()) {
        std::cerr << "Error: Invalid filename input.\n";
        if (std::cin.fail() && !std::cin.eof()) {
            std::cin.clear();
            std::cin.ignore(max_stream_size, '\n');
        }
    }
    return filename;
}

void IndexerUI::processIndexFile() {
    if (!index.isEmpty()) {
        std::cout << "Index is not empty. Clear existing index?";
        char confirm = getConfirmation();
        if (confirm != 'y') {
            std::cout << "Indexing cancelled.\n";
            return;
        }
    }
    std::string filename = getFileName();
    index.processTextFile(filename);
}

void IndexerUI::processDisplayAll() {
    if (index.isEmpty()) {
        std::cout << "\nIndex is empty.\n";
        return;
    }
    index.displayAllTokens();
}

void IndexerUI::processShowByLength() {
    if (index.isEmpty()) {
        std::cout << "\nIndex is empty.\n";
        return;
    }
    size_t length = getSearchLength();
    index.listByLength(length);
}

void IndexerUI::processViewSection() {
    if (index.isEmpty()) {
        std::cout << "\nIndex is empty.\n";
        return;
    }
    char sectionChar = getSectionChar();
    index.ViewBySection(sectionChar);
}

int IndexerUI::getSectionIndexFromChar(char firstChar) const {
    if (std::isalpha(static_cast<unsigned char>(firstChar)))
        return std::tolower(static_cast<unsigned char>(firstChar)) - 'a';
    else if (firstChar == '*')
        return 26;
    else
        return -1;
}