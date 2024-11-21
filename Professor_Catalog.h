#ifndef PROFESSOR_CATALOG_H
#define PROFESSOR_CATALOG_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Struct for storing professor information
struct Professor {
    string name;
    vector<string> courses; // List of courses
    double rating;
};

// Hash table class
class HashTable {
private:
    vector<vector<Professor>> table;
    int size;

    // Hash function for strings
    int hashFunction(const string& key) const;

public:
    HashTable(int s) : size(s) {
        table.resize(size);
    }

    void readFromFile(const string& filename);
    void insert(const string& profName, const string& courseID, double rating);
    void display() const;
    void search( string& profName) const;
};

#endif // PROFESSOR_CATALOG_H