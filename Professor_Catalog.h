#ifndef PROFESSOR_CATALOG_H
#define PROFESSOR_CATALOG_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Professor data struct
struct Professor {
    string name;
    string courseID;
    double rating;
};

// Node struct for linked list
struct Node {
    Professor data;
    Node* next;
};

// Function prototypes
Node* newProf(const Professor& prof);
void insert(Node*& head, const Professor& prof);
void readFromFile(Node*& head, const string& filename);
void displayProfs(Node* head);
void deleteList(Node*& head); // Free allocated memory

#endif // PROFESSOR_CATALOG_H