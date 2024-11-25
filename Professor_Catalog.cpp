// =============================================================================
// File: Professor_Catalog.cpp
// =============================================================================
// Programmer: Shazi Bidarian
// Class: CS 1D
// Instructor: Med Mogasemi
// =============================================================================
// Program: Professor Catalog (Implementation File)
// =============================================================================
// Description:
// This implementation file defines the methods for the `ProfessorTable` class,
// which manages a hash table for storing professor and course information. The
// hash table uses separate chaining to handle collisions, ensuring efficient
// storage and retrieval. The class includes functions to read data from a file,
// insert new records, display the catalog, and search for professors or courses.
// =============================================================================

#include "Professor_Catalog.h"
using namespace std;

// ==== hashFunction ===========================================================
// Hash function to compute the index for a given string key.
//
// Explanation:
// - A hash function converts a key (string) into an index in the hash table.
// - This index determines where the data is stored in the table.
// - Collisions (when two keys hash to the same index) are handled by chaining.
// =============================================================================
int ProfessorTable::hashFunction(const string& key) const {
    int hash = 0;

    // Iterate over each character in the key to compute the hash value
    for (char ch: key) {
        int asciivalue = static_cast<int>(ch); // Convert character to ASCII value
        hash = (hash + asciivalue * 23) % size; // Multiply by prime number, mod table size
    }

    return hash >= 0 ? hash : hash + size; // Ensure the hash is non-negative
}

// ==== readFromFile ===========================================================
// Reads professor and course data from a file and populates the hash table.
//
// Logic:
// - For each professor entry in the file, read their name, course, and rating.
// - Use the `insert` function to add the data into the hash table and course table.
// - If the data is invalid, skip that entry and display an error message.
// =============================================================================
void ProfessorTable::readFromFile(const string& filename) {
    ifstream file(filename);                         // Open the file

    if (!file.is_open()) {                           // Check if the file opened successfully
        cout << "Error opening file: " << filename << "\n";
        return;
    }

    string name;
    string courseID;
    string line;
    double rating;

    // Read the file line by line
    while (getline(file, name)) {
        if (name.empty()) {                          // Skip empty lines
            continue;
        }

        if (!getline(file, courseID)) {             // Read courseID, skip if missing
            cout << "Error reading courseID. Skipping entry.\n";
            continue;
        }

        if (!getline(file, line)) {                 // Read rating, skip if missing
            cout << "Error reading rating. Skipping entry.\n";
            continue;
        }

        try {
            rating = stod(line);                    // Convert rating to double
        } catch (const invalid_argument&) {         // Handle invalid rating format
            cout << "Invalid rating format. Skipping entry.\n";
            continue;
        }

        insert(name, courseID, rating);             // Insert the data into the hash table
    }

    file.close();                                   // Close the file
}

// ==== insert =================================================================
// Inserts a professor's course and rating into the hash table.
//
// Logic:
// - Use the hash function to compute the index for the professor's name.
// - Traverse the chain at that index to check if the professor already exists.
// - If found, update their course list; if not, add a new entry to the chain.
// - Update the `courseTable` to include the professor's rating for the course.
// =============================================================================
void ProfessorTable::insert(const string& profName, const string& courseID, double rating) {
    int index = hashFunction(profName);             // Compute the hash index

    // Search for the professor in the chain
    for (auto& entry : profTable[index]) {          // Traverse the chain at this index
        if (entry.name == profName) {               // If professor already exists
            entry.courses.push_back(courseID);      // Add the course to their list
            return;
        }
    }

    // Create a new professor entry if not found
    Professor newEntry = {profName, {courseID}, rating};
    profTable[index].push_back(newEntry);           // Add to the chain

    index = hashFunction(courseID);
    for (auto& entry : courseTable[index]) {
        if (entry.courseID == courseID) {
            entry.profs.push_back(make_pair(profName, rating));
            return;
        }
    }

    Course newEntry2 = {courseID, {{profName, rating}}};
    courseTable[index].push_back(newEntry2);
}

// ==== display ================================================================
// Displays the contents of the professor hash table.
//
// Logic:
// - Iterate through each index in the hash table.
// - For each non-empty index, print the professors and their courses.
// =============================================================================
void ProfessorTable::display() const {
    for (int i = 0; i < size; ++i) {                // Traverse each index in the hash table
        if (!profTable[i].empty()) {                // If the chain at this index is non-empty
            cout << "Index " << i << ":\n";
            for (const auto& entry : profTable[i]) { // Traverse the chain
                cout << "  Professor: " << entry.name << "\n";
                cout << "  Rating: " << entry.rating << "\n";
                cout << "  Courses: ";
                for (const auto& course : entry.courses) { // Print each course
                    cout << course << " ";
                }
                cout << "\n";
            }
        }
    }
}

// ==== search =================================================================
// Searches for a professor or course by name.
//
// Logic:
// - Hash the professor's name to find their index in the hash table.
// - Traverse the chain to find the professor and print their details.
// - If no professor is found, check the courseTable for matching courses.
// =============================================================================
void ProfessorTable::search(string& key) const {
    int index = hashFunction(key);                  // Compute the hash index

    // Search for the professor in the chain
    for (const auto& prof : profTable[index]) {     // Traverse the chain
        if (prof.name == key) {                     // If professor is found
            cout << "\nCourses taught by Professor " << prof.name << ":\n";
            for (const auto& course : prof.courses) {
                cout << course << "\n";
            }
            cout << "Rating: " << prof.rating << "\n";
            cout << endl;
            return;
        }
    }

    for (const auto& course : courseTable[index]) {
        if (course.courseID == key) {
            cout << "\nCourse: " << course.courseID << "\n";
            cout << "Professors teaching this course:\n";
            for (const auto& profName : course.profs) {
                cout << profName.first << ", " << profName.second << endl;
            }
            cout << endl;
            return;
        }
    }

    cout << "No course or professor found.\n";      // If neither found, display message
}