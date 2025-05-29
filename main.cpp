#include <iostream>
#include "IndexerUI.h"
int main() {
    std::cout << "Starting Text File Indexer\n";
    IndexerUI indexer;
    indexer.run();
    std::cout << "Program finished.\n";
    return 0;
}