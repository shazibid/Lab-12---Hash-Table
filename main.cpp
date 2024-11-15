#include <iostream>
#include "Professor_Catalog.h"

using namespace std;

int main() {
    HashTable hashTable(10);
    string Prof_Catalog = "/Users/shazi/VS Code/Git/Lab-12---Hash-Table/professor.txt";

    hashTable.readFromFile(Prof_Catalog);

    // Display the contents of the hash table
    cout << "Hash Table Contents:\n";
    hashTable.display();

    // Search for a professor
    cout << "\nSearching for Homi The_Man:\n";
    hashTable.search("Homi The_Man");

    cout << "\nSearching for Med Mogasemi:\n";
    hashTable.search("Med Mogasemi");

    cout << "\nSearching for Michael Brown:\n";
    hashTable.search("Michael Brown");

    cout << "\nSearching for Alice Johnson:\n";
    hashTable.search("Alice Johnson");

    return 0;
}