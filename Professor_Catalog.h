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

struct Course {
    string courseID;
    vector<pair<string, double>> profs;
};

// Hash table class
class ProfessorTable {
private:
    vector<vector<Professor>> profTable;
    vector<Course> courseTable;
    int size;

    // Hash function for strings
    int hashFunction(const string& key) const;

    int findCourseIndex(const string& courseID) const;

public:
    ProfessorTable(int s) : size(s) {
        profTable.resize(size);
    }

    void readFromFile(const string& filename);
    void insert(const string& profName, const string& courseID, double rating);
    void display() const;
    void search(string& profName) const;
};

#endif // PROFESSOR_CATALOG_H