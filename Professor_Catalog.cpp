#include "Professor_Catalog.h"

using namespace std;

int HashTable::hashFunction(const string& key) const {
    int hashValue = 0;
    int p = 31;
    int mod = 1e9 + 7;

    for (char c : key) {
        char lowerChar = tolower(c);
        hashValue = (hashValue * p + (lowerChar - 'a' + 1)) % mod;
    }

    return hashValue % size;
}

// Reads professor data from a file
void HashTable::readFromFile(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error opening file: " << filename << "\n";
        return;
    }

    string name;
    string courseID;
    string line;
    double rating;

    while (getline(file, name)) {
        if (name.empty()) continue;

        if (!getline(file, courseID)) {
            cout << "Error reading courseID from file. Skipping entry.\n";
            continue;
        }

        if (!getline(file, line)) {
            cout << "Error reading rating from file. Skipping entry.\n";
            continue;
        }

        try {
            rating = stod(line);
        } catch (const invalid_argument& e) {
            cout << "Invalid rating format: " << line << ". Skipping entry.\n";
            continue;
        }

        // Insert the data into the hash table
        insert(name, courseID, rating);
    }

    file.close();
}

// Inserts a professor's course into the hash table
void HashTable::insert(const string& profName, const string& courseID, double rating) {
    int index = hashFunction(profName);

    // Search for the professor in the chain at this index
    for (auto& entry : table[index]) {
        if (entry.name == profName) {
            // If professor exists, add the course (rating remains the same)
            entry.courses.push_back(courseID);
            return;
        }
    }

    // If professor not found, create a new entry
    Professor newEntry = {profName, rating, {courseID}};
    table[index].push_back(newEntry);
}

// Displays the contents of the hash table
void HashTable::display() const {
    for (int i = 0; i < size; ++i) {
        if (!table[i].empty()) {
            cout << "Index " << i << ":\n";
            for (const auto& entry : table[i]) {
                cout << "  Professor: " << entry.name << "\n";
                cout << "  Rating: " << entry.rating << "\n";
                cout << "  Courses: ";
                for (const auto& course : entry.courses) {
                    cout << course << " ";
                }
                cout << "\n";
            }
        }
    }
}

// Searches for a professor by name and displays their information
void HashTable::search(const string& profName) const {
    int index = hashFunction(profName);

    // Search for the professor in the chain
    for (const auto& entry : table[index]) {
        if (entry.name == profName) {
            cout << "Professor: " << profName << "\n";
            cout << "Rating: " << entry.rating << "\n";
            cout << "Courses: ";
            for (const auto& course : entry.courses) {
                cout << course << " ";
            }
            cout << "\n";
            return;
        }
    }

    cout << "Professor " << profName << " not found.\n";
}