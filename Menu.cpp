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
        cout << "Enter an action (1: register, 2: check, 3: search, 4: rate, 5:exit): ";
        cin >> choice;

        while (choice < 1 || choice > 5) {
            cout << "Invalid Choice. Try Again: ";
            cin >> choice;
        }

        switch (choice) {
            case 1:
                registerChoice(hashTable, studentTable);
                break;
            case 2:
                checkChoice(studentTable);
                break;
            case 3:
                searchChoice(hashTable);
                break;
            case 4:
                rateProf(studentTable);
            case 5:
                exitChoice();
                break;
        }
    }
}

void registerChoice(ProfessorTable& hashTable, StudentTable& studentTable) {
    studentTable.add();
}

void checkChoice(StudentTable& studentTable) {
    studentTable.checkRegistration();
}

void searchChoice(ProfessorTable& hashTable) {
    string profName;
    hashTable.display();

    cout << "Enter professor's name: ";
    cin.ignore();
    getline(cin, profName);

    hashTable.search(profName);
}

void rateProf(StudentTable& studentTable){
    studentTable.rateProfessor();
}

void exitChoice() {
    cout << "Thank you.\n";
    exit(0);
}
