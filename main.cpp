#include <iostream>
#include "Professor_Catalog.h"
#include "Menu.cpp"

using namespace std;

int main() {
    HashTable hashTable(10);
    string Prof_Catalog = "/Users/shazi/VS Code/Git/Lab-12---Hash-Table/professor.txt";

    hashTable.readFromFile(Prof_Catalog);
    hashTable.insert("Dr. Smith", "Data Structures", 4.5);

    showMenu(hashTable);

    return 0;
}