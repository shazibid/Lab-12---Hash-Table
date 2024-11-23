//
// Created by Shazi Bidarian on 11/18/24.
//
#include <iostream>
#include "Professor_Catalog.h"
using namespace std;

void showMenu(ProfessorTable& hashTable);
void registerChoice(ProfessorTable& hashTable);
void checkChoice(ProfessorTable& hashTable);
void searchChoice(ProfessorTable& hashTable);
void exitChoice();

void showMenu(ProfessorTable& hashTable) {
    int choice;

    while (true) {
        cout << "Enter an action (1: register, 2: check, 3: search, 4: exit): ";
        cin >> choice;

        while (choice < 1 || choice > 4) {
            cout << "Invalid Choice. Try Again: ";
            cin >> choice;
        }

        switch (choice) {
            case 1:
                registerChoice(hashTable);
                break;
            case 2:
                checkChoice(hashTable);
                break;
            case 3:
                searchChoice(hashTable);
                break;
            case 4:
                exitChoice();
                break;
        }
    }
}

void registerChoice(ProfessorTable& hashTable) {

}

void checkChoice(ProfessorTable& hashTable) {

}

void searchChoice(ProfessorTable& hashTable) {
    string profName;
    hashTable.display();

    cout << "Enter professor's name: ";
    cin.ignore();
    getline(cin, profName);

    hashTable.search(profName);
}

void exitChoice() {
    cout << "Thank you.\n";
    exit(0);
}