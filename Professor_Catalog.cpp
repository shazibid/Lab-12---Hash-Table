#include "Professor_Catalog.h"

using namespace std;

int ProfessorTable::hashFunction(const string& key) const {
    int hash{};
    int p = 7;

    for (int i = 0; i < key.length(); i++) {
        int asciivalue = (hash + int(key[i]));
        hash = (hash + asciivalue * 23) % p;
    }

    return hash;
}
// ==== findCourseIndex ========================================================
// Helper function to find the index of a course in the course table.
//
// Logic:
// - Loop through the `courseTable` to find a course that matches `courseID`.
// - Return the index if found; otherwise, return -1 to indicate not found.
// =============================================================================
int ProfessorTable::findCourseIndex(const string& courseID) const {
    for (int i = 0; i < courseTable.size(); i++) {   // Traverse the courseTable vector
        if (courseTable[i].courseID == courseID) {  // Check if courseID matches
            return i;                               // Return the index if found
        }
    }
    return -1;                                      // Return -1 if not found
}

// Reads professor data from a file
/////////////////UPDATED -  GIVEN BY CHATGPT IT WAS NOT READING PROPERLY WHEN GOING THROUGH HASH////////////////
void ProfessorTable::readFromFile(const std::string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error opening file: " << filename << "\n";
        return;
    }

    string name;
    string courseID;
    string line;
    double rating;
    int numRatings;

    while (std::getline(file, name)) {
        if (name.empty()) continue; // Skip empty lines

        getline(file, courseID);
        getline(file, line);

        // Parse rating
        try {
            rating = stod(line);
        } catch (const invalid_argument& e) {
          cout << "Invalid rating format. Skipping entry.\n";
            continue;
        }

        // Parse numRatings (additional line in the file)
        getline(file, line);
        try {
            numRatings = stoi(line);
        } catch (const invalid_argument& e) {
           cout << "Invalid number of ratings format. Skipping entry.\n";
            continue;
        }

        // Clean up trailing spaces/newlines
        name = name.substr(0, name.find_last_not_of(" \n\r\t") + 1);
        courseID = courseID.substr(0, courseID.find_last_not_of(" \n\r\t") + 1);

        // Insert cleaned values
        insert(name, courseID, rating, numRatings);
    }

    file.close();
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
void ProfessorTable::insert(const string& profName, const string& courseID, double rating, int numRatings) {
    int index = hashFunction(profName);             // Compute the hash index

    // Search for the professor in the chain
    for (auto& entry : profTable[index]) {          // Traverse the chain at this index
        if (entry.name == profName) {               // If professor already exists
            entry.courses.push_back(courseID);      // Add the course to their list
            return;
        }
    }

    // Create a new professor entry if not found
    Professor newEntry = {profName, {courseID}, rating, numRatings};
    profTable[index].push_back(newEntry);           // Add to the chain

    // Update the courseTable
    int courseIndex = findCourseIndex(courseID);    // Find the course in courseTable
    if (courseIndex == -1) {                        // If course does not exist
        Course newCourse = {courseID, {{profName, rating}}};
        courseTable.push_back(newCourse);           // Add a new course entry
    } else {                                        // If course exists, update it
        courseTable[courseIndex].profs.push_back({profName, rating});
    }
}
// Displays the contents of the hash table
void ProfessorTable::display() const {
    for (int i = 0; i < size; ++i) {
        if (!profTable[i].empty()) {
            cout << "Index " << i << ":\n";
            for (const auto& entry : profTable[i]) {
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

// ==== search =================================================================
// Searches for a professor or course by name.
//
// Logic:
// - Hash the professor's name to find their index in the hash table.
// - Traverse the chain to find the professor and print their details.
// - If no professor is found, check the courseTable for matching courses.
// =============================================================================
void ProfessorTable::search(string& key) const {
    system("clear");
    int index = hashFunction(key);                  // Compute the hash index

    // Search for the professor in the chain
    for (const auto& prof : profTable[index]) {     // Traverse the chain
        if (prof.name == key) {                     // If professor is found
            cout << "\nCourses taught by Professor " << prof.name << ":\n";
            for (const auto& course : prof.courses) {
                cout << course << "\n";
            }
            cout << "Rating: " << prof.rating << "\n";
            return;
        }
    }

    // Search for the course in the course table
    int courseIndex = findCourseIndex(key);
    if (courseIndex != -1) {                        // If course is found
        cout << "\nCourse: " << key << "\n";
        cout << "Professors teaching this course:\n";
        for (const auto& [profName, rating] : courseTable[courseIndex].profs) {
            cout << "  Professor: " << profName << "\n";
            cout << "  Rating: " << rating << "\n";
        }
        return;
    }

    cout << "No course or professor found.\n";      // If neither found, display message
}