#include "IndexerUI.h"

#include <cctype> // Provides functions to check and convert characters
#include <fstream>  // Enables file input/output using std::ifstream, std::ofstream.
#include <iostream>  // For standard input/output.
#include <limits> //  Provides info about numeric limits (like the largest/smallest int, double, etc.).
#include <new>  // For std::bad_alloc
#include <sstream>  // Used for parsing strings like a stream (like cin, but from a string).
#include <stdexcept>  // For std::exception
#include <string>  // Enables use of std::string


IndexerUI::IndexerUI() : currentFilename("") {}

// Main application loop with error handling
void IndexerUI::run() {
  int choice = 0;
  do {
    displayMenu();
    choice = getUserChoice();
    std::string filename;

    try {
      switch (choice) {
        case 1:
          processIndexFile();
          break;
        case 2:
          processDisplayAll();
          break;
        case 3:
          processShowByLength();
          break;
        case 4:
          processViewSection();
          break;
        case 5:
          std::cout << "\nExiting program. Goodbye!" << std::endl;
          break;
      }
    } catch (const std::bad_alloc& e) {
      std::cerr << "\n********\nFATAL ERROR: Memory allocation failed: "
                << e.what() << "\n********" << std::endl;
      // Consider exiting or trying to recover minimally
      choice = 5;  // Force exit on memory exhaustion
    } catch (const std::exception& e) {
      std::cerr << "\n********\nERROR: An exception occurred: " << e.what()
                << "\n********" << std::endl;
      // Continue the loop after other standard exceptions
    } catch (...) {
      std::cerr << "\n********\nERROR: An unknown exception occurred.\n********"
                << std::endl;
      // Continue the loop
    }
  } while (choice != 5);
}

// Display menu options
void IndexerUI::displayMenu() const {
  std::cout << "\n===== Text File Indexer Menu =====\n"
            << "1. Index a text file\n"
            << "2. Show tokens in all sections\n"
            << "3. Find tokens by length\n"
            << "4. View tokens by section\n"
            << "5. Exit\n"
            << "==================================\n";
}

// Robustly get and validate user's menu choice (1-5)
int IndexerUI::getUserChoice() const {
  int choice = 0;
  std::cout << "Enter your choice (1-5): ";
  while (!(std::cin >> choice) || choice < 1 || choice > 5) {
    std::cerr << "Invalid input. Please enter a number between 1 and 5: ";
    std::cin.clear();                        // Clear the error flag on cin
    std::cin.ignore(max_stream_size, '\n');  // Discard the invalid input from
                                             // the buffer up to the newline
  }
  std::cin.ignore(max_stream_size, '\n');    // Valid user choice is not allowed
                                             // to be followed by more input
                                             // so discard any trailing characters
                                             // from the buffer up to the newline
  return choice;
}

// Robustly get and validate confirmation (y/n)
char IndexerUI::getConfirmation() const {
  char confirm = ' ';
  std::cout << " (y/n): ";
  while (true) {
    std::cin >> confirm;
    // Discard rest of the line
    std::cin.ignore(max_stream_size, '\n');
    confirm = std::tolower(static_cast<unsigned char>(confirm));
    if (confirm == 'y' || confirm == 'n')
      return confirm;  // Valid input
    else
      std::cerr << "Invalid input. Please enter 'y' or 'n': ";
  }
}

// Robustly get and validate search length (non-negative integer)
size_t IndexerUI::getSearchLength() const {
  long long inputLength = -1;  // Use long long to detect large invalid numbers
  std::cout << "Enter token length (non-negative): ";
  while (true) {
    std::cin >> inputLength;
    if (std::cin.good() && inputLength >= 0) {
      // Good input and non-negative
      std::cin.ignore(max_stream_size,
                      '\n');  // Discard rest of the line before returning
      if (static_cast<unsigned long long>(inputLength) >
          std::numeric_limits<size_t>::max()) {
        std::cerr << "Input length too large. Please try again: ";
        inputLength = -1;
      } else {
        return static_cast<size_t>(inputLength);
      }
    } else {
      std::cerr << "Invalid input. Please enter a non-negative integer: ";
      std::cin.clear();
      std::cin.ignore(max_stream_size, '\n');
      inputLength = -1;  // Reset for next loop iteration
    }
  }
}

// Robustly get and validate section character (A-Z or *)
char IndexerUI::getSectionChar() const {
  char sectionChar = ' ';
  std::cout << "Enter section character (A-Z or *): ";
  while (true) {
    std::cin >> sectionChar;
    std::cin.ignore(max_stream_size, '\n');  // Discard rest of the line
    // Check if it's a valid alpha char or '*'
    if (std::isalpha(static_cast<unsigned char>(sectionChar)) ||
        sectionChar == '*')
      return sectionChar;
    else
      std::cerr << "Invalid input. Please enter A-Z or *: ";
  }
}

std::string IndexerUI::getFileName() const {
  std::string filename;
  std::cout << "Enter the filename to index: ";
  // Use getline to allow spaces in filenames
  if (!std::getline(std::cin, filename) || filename.empty()) {
    std::cerr << "Error: Invalid filename input.\n";
    // If getline failed, clear potential error state on cin if needed
    if (std::cin.fail() && !std::cin.eof()) {
      std::cin.clear();                        // clear cin
      std::cin.ignore(max_stream_size, '\n');  // skip input up to newline
    }
  }
  return filename;
}

// Process: Index a file
void IndexerUI::processIndexFile() {
  // Check if index needs clearing
  if (!index.isEmpty()) {
    // Prompts the user to confirm clearing existing data
    std::cout << "Index is not empty. Clear existing index?";
    char confirm = getConfirmation();  // Use robust input helper
    if (confirm != 'y') {
      std::cout << "Indexing cancelled.\n";
      return;
    }
  }

  std::string filename = getFileName();
  index.processTextFile(filename);
}

// Process: Display all tokens
void IndexerUI::processDisplayAll() {
  if (index.isEmpty()) {
    std::cout << "\nIndex is empty.\n";
    return;
  }
  index.displayAll();
}
// Process: Search by length
void IndexerUI::processShowByLength() {
  if (index.isEmpty()) {
    std::cout << "\nIndex is empty.\n";
    return;
  }
  size_t length = getSearchLength();
  index.searchByLength(length);
}
// Process: View by section
void IndexerUI::processViewSection() {
  if (index.isEmpty()) {
    std::cout << "\nIndex is empty.\n";
    return;
  }
  char sectionChar = getSectionChar();
  int sectionIndex = getSectionIndexFromChar(sectionChar);
  index.displaySection(sectionIndex);
}

// Helper maps valid browse char ('A'-'Z', '*') to index 0-26
int IndexerUI::getSectionIndexFromChar(char firstChar) const {
  if (std::isalpha(static_cast<unsigned char>(firstChar)))
    return std::tolower(static_cast<unsigned char>(firstChar)) - 'a';  // 0-25
  else if (firstChar == '*')
    return Indexer::NUM_SECTIONS - 1;  // 26
  else
    return -1;  // Should be unreachable due to getSectionChar validation
}