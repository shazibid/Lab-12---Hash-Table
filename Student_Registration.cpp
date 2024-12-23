#include "Student_Registration.h"
#include <string>

int StudentTable::hashFunction(int studentID) const
{
    return studentID % SIZE;
}


/*
By passing a pointer to an existing ProfessorTable instance,
you allow StudentTable to access and update the same professor
data being used throughout your program.
*/
StudentTable::StudentTable(ProfessorTable *professorTablePtr) : StuTable(SIZE), professorTablePtr(professorTablePtr) {};


// ==== add ====================================================================
// Registers a student for a selected course and professor.
//
// Logic:
// - Prompt the user for a Student ID and a search key (course or professor name).
// - Use the `ProfessorTable::search` function to display matches for the search key.
// - If the key matches a course, list professors teaching it; if it matches a professor, list their courses.
// - Prompt the user to select from the list and validate the choice.
// - Check if the student is already registered for the selected course and professor.
// - If not registered, add the course and professor to the student's registration list.
// - If the student does not exist, create a new student profile and register them.
//
// Why this is a good approach:
// - Reusability: Relies on the `ProfessorTable::search` function, ensuring consistency and avoiding redundancy.
// - Flexibility: Supports both course-based and professor-based searches, making it user-friendly.
// - Error Handling: Validates user input and prevents duplicate registrations.
// - Dynamic Interaction: Allows users to dynamically select from a list of options, improving usability.
// - Scalability: Designed to handle new students and new registrations without requiring changes to existing logic.
// =============================================================================

void StudentTable::add()
{
    int studentID;
    string searchKey;

    // Prompt user for Student ID
    cout << "Enter Student ID: ";
    cin >> studentID;

    // if (!validateID(studentID)) {
    //  return;
    //}

    // Prompt user for Search Key (Course or Professor Name)
    cout << "Enter search key (course or professor name): ";
    cin.ignore();
    getline(cin, searchKey);

    // Remove trailing whitespace
    searchKey = searchKey.substr(0, searchKey.find_last_not_of(" \n\r\t") + 1);

    int index = hashFunction(studentID); // Hash function determines the bucket for this student

    // Check if the student already exists
    for (auto &student : StuTable[index])
    {
        if (student.studentID == studentID)
        {
            registerForCourseOrProfessor(student, searchKey);
            return;
        }
    }

    // Create a new student if not found
    cout << "Student ID not found. Creating a new student profile...\n";
    Student newStudent(studentID);
    registerForCourseOrProfessor(newStudent, searchKey);
    StuTable[index].push_back(newStudent);
    cout << "New student profile created and registered.\n";
}

// ==== registerForCourseOrProfessor ===========================================
// Helper function to handle course/professor registration.
//
// Logic:
// - Search for matches based on the search key.
// - Prompt the user to select a course or professor from the list.
// - Check if the student is already registered for the selection.
// - Register the student if not already registered.
// =============================================================================

void StudentTable::registerForCourseOrProfessor(Student &student, const string &searchKey)
{
    cout << "Searching for " << searchKey << "...\n";

    // Create a list of matches based on the searchKey
    vector<pair<string, string>> matches; // Each pair: (course, professor)

    // If the searchKey is a course, find professors teaching that course
    // Search for the course index using the searchKey in the course table
    int courseIndex = professorTablePtr->findCourseIndex(searchKey);

    if (courseIndex != -1) // If the course is found in the course table
    {
        // Loop through the professors teaching the course at the found index
        for (const auto &prof : professorTablePtr->courseTable[courseIndex].profs)
        {
            // Add each professor and the searchKey (course name) to the matches vector
            matches.emplace_back(searchKey, prof.first); // `prof.first` is the professor's name
        }
    }
    else // assume the searchKey might be a professor's name
    {
        // Compute the hash index for the professor's name
        int profIndex = professorTablePtr->hashFunction(searchKey);

        // Loop through the professors in the hash table bucket at the computed index
        for (const auto &prof : professorTablePtr->profTable[profIndex])
        {
            if (prof.name == searchKey)
            {
                // If the professor is found, loop through the courses they teach
                for (const auto &course : prof.courses)
                {
                    // Add each course and the professor's name to the matches vector
                    matches.emplace_back(course, searchKey); // `course` is the course name
                }

                // Break to avoid redundant checks
                break;
            }
        }
    }

    if (matches.empty())
    {
        cout << "No matches found for the search key.\n";
        return;
    }

    // Display matches
    cout << "\n";
    if (matches.front().first == searchKey)
    {
        cout << "Multiple professors teach " << searchKey << ". Select one:\n";
        for (int i = 0; i < matches.size(); ++i)
        {
            cout << i + 1 << ". " << matches[i].second << "\n";
        }
    }
    else if (matches.front().second == searchKey)
    {
        cout << searchKey << " teaches multiple courses. Select one:\n";
        for (int i = 0; i < matches.size(); ++i)
        {
            cout << i + 1 << ". " << matches[i].first << "\n";
        }
    }

    // Prompt user for their choice
    int choice;
    cout << "Enter your choice (1-" << matches.size() << "): ";
    cin >> choice;

    // Validate choice
    if (choice < 1 || choice > matches.size())
    {
        cout << "Invalid choice. Registration canceled.\n";
        return;
    }

    // Extract selected course and professor
    string selectedCourse = matches[choice - 1].first;
    string selectedProfessor = matches[choice - 1].second;

    // Check if the student is already registered
    for (const auto &reg : student.registeredCourses)
    {
        if (reg.courseName == selectedCourse && reg.professorName == selectedProfessor)
        {
            cout << "Student is already registered for " << selectedCourse
                 << " under Professor " << selectedProfessor << ".\n";
            return;
        }
    }

    // Register the student
    student.registeredCourses.emplace_back(selectedCourse, selectedProfessor);
    cout << "Student " << student.studentID << " registered for " << selectedCourse
         << " under Professor " << selectedProfessor << ".\n";
    for (const auto &reg : student.registeredCourses)
    {
        cout << "Registered Course: " << reg.courseName
             << ", Professor: " << reg.professorName << "\n";
    }
}


void StudentTable::validateStudentID(string studentID)
{
    // Check first that the length is 6
    if (studentID.length() != 6) {
        cout << "Student ID must be 6 digits long." << endl;
        return;
    }

    // place individual digits from ID into a vector
    vector<int> individualDigits;

    for (int i = 0; i < studentID.length(); i++) {
        char c = studentID[i];
        // check if c is not a digit using ASCII
        if (c < '0' || c > '9') {
            cout << "Invalid ID. ID must only contain digits." << endl;
            return NULL;
        }
        // Subtract ASCII values from '0' to c
        // ex: c = 2
        // In ASCII, 2 = 50, 0 = 48 ---> 50-48=2
        individualDigits.push_back(c - '0');
    }

    // need to double every second digit from the right
    for (int i = individualDigits.size() - 2; i >= 0; i -= 2) {
        individualDigits[i] = individualDigits[i] * 2;

        // Check if result of doubling a digit is greater than 9
        if (individualDigits[i] > 9) {
            // if it is, subtract 9
            individualDigits[i] = individualDigits[i] - 9;
        }
    }

    // Now calculate sum of all digits in the vector
    int sum = 0;
    for  (int i = 0; i < individualDigits.size(); i++) {
        sum = sum + individualDigits[i];
    }

    // Check for division by 10; remainder of 0 means it is divisible by 10
    if (sum % 10 == 0) {
        cout << "Valid Student ID." << endl;
    }
    else
        cout << "Invalid Student ID." << endl;
}

// ==== checkRegistration =====================================================
// Checks if a student is registered for a specific course and professor.
//
// Logic:
// - Prompt the user for a Student ID, course name, and professor name.
// - Use the `hashFunction` to locate the bucket for the Student ID.
// - Traverse the bucket to find the student and their registered courses.
// - Check if the course and professor combination matches the input.
// - Output whether the student is registered for the course and professor.
//
// Why this is a good approach:
// - **Direct Validation:** Ensures the student is actually registered for the course and professor before taking further actions.
// - **Efficient Lookup:** Uses a hash table for fast access to the student's data.
// - **Clear Feedback:** Provides immediate confirmation to the user about the registration status.
// =============================================================================

void StudentTable::checkRegistration() const
{
    int studentID;
    string courseName, professorName;
    cout << "Enter student ID: ";
    cin >> studentID;

    cout << "Enter course name: ";
    cin >> courseName;

    cout << "Enter professor name: ";
    cin.ignore();
    getline(cin, professorName);

    // Remove trailing whitespace from inputs// looked this up bc it was not working
    courseName = courseName.substr(0, courseName.find_last_not_of(" \n\r\t") + 1);
    professorName = professorName.substr(0, professorName.find_last_not_of(" \n\r\t") + 1);

    // Hash studentID to locate the bucket
    int index = hashFunction(studentID);

    for (const auto &student : StuTable[index]) // going through bucket ay stuTable at index
    {
        if (student.studentID == studentID) // if match found continue
        {
            for (const auto &reg : student.registeredCourses) // go thorugh the student registeredCourses (vector)
            {
                if (reg.courseName == courseName && reg.professorName == professorName) // if match found
                {
                    cout << "Student " << studentID << " Is registered for " << courseName << " under professor "
                         << professorName;
                    return;
                }
                else // if not found
                {
                    cout << "Student " << studentID << " Is  NOT registered for " << courseName << " under Professor "
                         << professorName;
                    break;
                }
            }
        }
    }
}

// ==== rateProfessor =========================================================
// Updates the rating for a professor based on student input.
//
// Logic:
// - Prompt the user for a Student ID and professor name.
// - Use the `hashFunction` to locate the bucket for the Student ID.
// - Traverse the bucket to find the student and their registered courses.
// - Check if the student has registered for a course taught by the professor.
// - If found, prompt the user for a new rating and validate the input.
// - Update the professor's rating in the `ProfessorTable` by recalculating
//   the average with the new rating.
//
// Why this is a good approach:
// - Integrity Check: Ensures only students who are registered for a professor's course can update their rating.
// - Interactive Feedback: Allows users to directly input a new rating and see the updated value in real time.
// - Centralized Rating Management: Updates the professor's rating in the `ProfessorTable`, maintaining consistency.
// - Validation: Includes input validation to ensure ratings remain within the allowed range (1.0 to 5.0).
// =============================================================================

void StudentTable::rateProfessor()
{

    int studentID;
    double newRating;
    string professorName;

    cout << "Enter ID: ";
    cin >> studentID;

    // if (!validateID(studentID)) {
    //     return;
    // }

    cout << "\nEnter Professor name: ";
    cin.ignore();
    getline(cin, professorName);

    int index = hashFunction(studentID);

    for (const auto &student : StuTable[index]) // going through studentIDs in student table
    {
        if (student.studentID == studentID) // if match found continue
        {
            for (const auto &reg : student.registeredCourses) // go thorugh the student registeredCourses (vector)
            {
                if (reg.professorName == professorName)
                {
                    cout << "\nEnter Rating for " << professorName << ", be nice :))! : ";
                    cin >> newRating;
                    // validtaing input
                    if (newRating < 0.0 || newRating > 5.0)
                    {
                        cout << "\nInvalid rating. Please provide a rating between 0.0 and 5.0.\n";
                        return;
                    }
                    // The hashFunction of professorTablePtr computes a hash index (profIndex) for professorName.
                    // this index is used to access the appropriate bucket in the professor hash table.
                    // -> accesses the hashfunc from the ProfessorTable object being pointed to.

                     int profIndex = professorTablePtr->hashFunction(professorName);

                   for (auto &i : professorTablePtr->profTable[profIndex]) // iterates the bucket at profIndex in the professor hash table (profTable) to find matching Professor
                                                                            // In prof.cpp, profTable defined as vector<vector<Professor>>, each bucket stores list of Professor structs

                    {
                        if (i.name == professorName)
                        {
                            // Update professor's rating//
                            i.numRatings++;                                                    // inc number of ratings
                            i.rating = ((i.rating * i.numRatings) + newRating) / i.numRatings; // recalculating the average rating for mr.prof
                            if (i.rating > 5.0)
                                i.rating = 5.0; // Keeps it between 1-5 idk if this is correct, check later, easy fix
                            if (i.rating < 1.0)
                                i.rating = 1.0;
                            cout << "Updated rating for Professor " << professorName << ": " << i.rating << "\n";
                            return;
                        }
                    }

                    cout << "Professor " << professorName << " not found in the catalog.\n";
                }
                cout << "\n not registered with " << professorName;
            }
        }
    }
}

void StudentTable::displayRegistrations(int studentID) const
{
}
