//
// Created by Shazi Bidarian on 11/18/24.
//
#include <iostream>
#include "Professor_Catalog.h"
using namespace std;

void showMenu(HashTable& hashTable);
void registerChoice(HashTable& hashTable);
void checkChoice(HashTable& hashTable);
void searchChoice(HashTable& hashTable);
void exitChoice(HashTable& hashTable);

void showMenu(int choice, HashTable& hashTable) {
    cout << "Enter an action (1: register, 2: check, 3: search, 4: exit): ";
    cin >> choice;

    while (choice < 1 || choice > 4) {
        cout << "Invalid Choice. Try Again: ";
        cin >> choice;
    }

    switch (choice) {
        case 1:
            registerChoice(hashTable);
            showMenu(choice, hashTable);
            break;
        case 2:
            checkChoice(hashTable);
            showMenu(choice, hashTable);
            break;
        case 3:
            searchChoice(hashTable);
            showMenu(choice, hashTable);
            break;
        case 4:
            exitChoice(hashTable);
            break;
    }
}

void registerChoice(HashTable& hashTable) {

}

void checkChoice(HashTable& hashTable) {

}

void searchChoice(HashTable& hashTable) {
    string profName;
    hashTable.display();

    cout << "Enter professor's name: ";
    cin.ignore();
    getline(cin, profName);

    hashTable.search(profName);
}

void exitChoice(HashTable& hashTable) {
    cout << "Thank you.\n";
}