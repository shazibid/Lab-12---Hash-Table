#include "Professor_Catalog.h"

using namespace std;

int ProfessorTable::hashFunction(const string& key) const {
    int hash = 0;
    for (char ch : key) {
        int asciivalue = static_cast<int>(ch);
        hash = (hash + asciivalue * 23) % size; // Ensure index is within bounds
    }

    return hash >= 0 ? hash : hash + size; // Handle negative hash values
}

int ProfessorTable::findCourseIndex(const string& courseID) const {
    for (int i = 0; i < courseTable.size(); i++) { // Loop over valid range
        if (courseTable[i].courseID == courseID) {
            return i;
        }
    }
    return -1; // Return -1 if course not found
}

// Reads professor data from a file
void ProfessorTable::readFromFile(const string& filename) {
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
        if (name.empty()) {
            continue;
        }

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
            cout << "Invalid rating format. Skipping entry.\n";
            continue;
        }

        // Insert the data into the hash table
        insert(name, courseID, rating);
    }

    file.close();
}

// Inserts a professor's course into the hash table
void ProfessorTable::insert(const string& profName, const string& courseID, double rating) {
    int index = hashFunction(profName);

    // Search for the professor in the chain at this index
    for (auto& entry : profTable[index]) {
        if (entry.name == profName) {
            // If professor exists, add the course (rating remains the same)
            entry.courses.push_back(courseID);
            return;
        }
    }

    // If professor not found, create a new entry
    Professor newEntry = {profName, {courseID}, rating};
    profTable[index].push_back(newEntry);

    int courseIndex = findCourseIndex(courseID);
    if (courseIndex == -1) {
        Course newCourse = {courseID, {{profName, rating}}};
        courseTable.push_back(newCourse);
    } else {
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

// Searches for a professor by name and displays their information
void ProfessorTable::search(string& key) const {
    system("clear");
    int index = hashFunction(key); // this is the hash

    // Search for the professor in the chain
    for (const auto& prof : profTable[index]) {
        if (prof.name == key) {
            cout << "\nCourses taught by Professor " << prof.name << ":\n";
            for (const auto& course : prof.courses) {
                cout << course << "\n";
            }
            cout << "Rating: " << prof.rating << "\n";
            cout << "\n";
            return;
        }
    }

    int courseIndex = findCourseIndex(key);
    if (courseIndex != -1) {
        cout << "\nCourse: " << key << "\n";
        cout << "Professors teaching this course:\n";
        for (const auto& [profName, rating] : courseTable[courseIndex].profs) {
            cout << "  Professor: " << profName << "\n";
            cout << "  Rating: " << rating << "\n";
        }
        return;
    }

    cout << "No course or professor found.\n";
}