// =============================================================================
// File: Professor_Catalog.h
// =============================================================================
// Programmer: Shazi Bidarian
// Class: CS 1D
// Instructor: Med Mogasemi
// =============================================================================
// Program: Professor Catalog (Header File)
// =============================================================================
// Description:
// This header file defines the `ProfessorTable` class, which implements a hash
// table to store professor information and their associated courses and ratings.
// It also includes a structure for courses and professors. The class provides
// functionality to read data from a file, insert new records, display the
// catalog, and search for professors by name.
// =============================================================================

#ifndef PROFESSOR_CATALOG_H
#define PROFESSOR_CATALOG_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// ==== Professor Struct =======================================================
// Structure to store information about a professor, including their name, a
// list of courses they teach, and their rating.
// =============================================================================
struct Professor {
    string name;               // Professor's name
    vector<string> courses;    // List of courses taught by the professor
    double rating;             // Professor's rating
};

// ==== Course Struct ==========================================================
// Structure to store course information, including the course ID and a list of
// professors who teach the course along with their ratings.
// =============================================================================
struct Course {
    string courseID;                       // Course ID (e.g., "CS1D")
    vector<pair<string, double>> profs;   // List of professors and their ratings
};

// ==== ProfessorTable Class ===================================================
// Hash table class to manage a catalog of professors and courses. The hash
// table uses separate chaining to handle collisions.
//
// Public Methods:
// - ProfessorTable(int s): Constructor to initialize the hash table.
// - void readFromFile(const string& filename): Reads professor data from a file.
// - void insert(const string& profName, const string& courseID, double rating):
//   Inserts a new professor record into the hash table.
// - void display() const: Displays all professor records in the catalog.
// - void search(string& profName) const: Searches for a professor by name and
//   displays their details.
//
// Private Methods:
// - int hashFunction(const string& key) const: Hash function to compute the
//   index for a given string key.
// - int findCourseIndex(const string& courseID) const: Helper function to find
//   the index of a course in the course table.
// =============================================================================
class ProfessorTable {
private:
    vector<vector<Professor>> profTable; // Hash table for professors
    vector<Course> courseTable;         // Table for courses
    int size;                           // Size of the hash table

    // Hash function for strings
    int hashFunction(const string& key) const;

    // Helper function to find the index of a course
    int findCourseIndex(const string& courseID) const;

public:
    // Constructor to initialize the hash table
    ProfessorTable(int s) : size(s) {
        profTable.resize(size);
    }

    // Reads professor data from a file
    void readFromFile(const string& filename);

    // Inserts a new professor record into the hash table
    void insert(const string& profName, const string& courseID, double rating);

    // Displays all professor records in the catalog
    void display() const;

    // Searches for a professor by name and displays their details
    void search(string& profName) const;
};

#endif // PROFESSOR_CATALOG_H