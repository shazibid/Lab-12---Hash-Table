#include <iostream>
#include "Professor_Catalog.h"

using namespace std;

int main() {
    Node* head = nullptr;
    string filename = "/Users/shazi/VS Code/Git/Lab-12---Hash-Table/professor.txt";

    readFromFile(head, filename);

    cout << "List of Professors:" << endl;
    displayProfs(head);

    // Free the allocated memory
    deleteList(head);

    return 0;
}