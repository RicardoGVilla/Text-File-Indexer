#ifndef INDEXERUI_H
#define INDEXERUI_H

#include "Indexer.h"
#include <string>
#include <limits>

// Main application class.
class IndexerUI {
private:
    Indexer index;          // The index 
    std::string currentFilename;  // Name of the currently indexed file.
    static constexpr auto max_stream_size = std::numeric_limits<std::streamsize>::max();

    // UI Helpers
    void displayMenu() const;
    int getUserChoice() const;      // Robust menu choice input.
    char getConfirmation() const;   // Robust y/n input.
    size_t getSearchLength() const; // Robust length input.
    char getSectionChar() const;    // Robust section character input.
    std::string getFileName() const;    // Robust file name query.

    // Processing Helpers
    void processIndexFile();
    void processDisplayAll();
    void processShowByLength();
    void processViewSection();

    // Utility Helper
    int getSectionIndexFromChar(char firstChar) const; // Maps char to section.

public:
    // Constructor.
    IndexerUI();

    // --- Rule of Five ---
    ~IndexerUI() = default;
    // Copying an indexer is typically undesirable (potential large state)
    // Prevent copying.
    IndexerUI(const IndexerUI& other) = delete;
    IndexerUI& operator=(const IndexerUI& other) = delete;
    // Allow moving.
    IndexerUI(IndexerUI&& other) noexcept = default;
    IndexerUI& operator=(IndexerUI&& other) noexcept = default;
    // --- End Rule of Five ---

    // Starts the main application loop.
    void run();
};

#endif  // INDEXERUI_H