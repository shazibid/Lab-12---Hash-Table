#ifndef STUDENT_REGISTRATION_H
#define STUDENT_REGISTRATION_H
#include <iostream>
#include <vector>

using namespace std;

// Hash class for student registrations
class StudentTable {
private:
struct Registration { // Keeps us from using two seperate vectors for course and professor
    string courseName;
    string professorName;

    Registration(const string& course, const string& professor)
        : courseName(course), professorName(professor) {}
};

//struct for storing student info
struct Student {
    int studentID;
    vector<Registration> registeredCourses; //student may have registered for multiple classes, vector allows for flexibility

    Student(int id) : studentID(id) {}
};

    static const int SIZE = 15; // smaller size to keep things simple
    vector<vector<Student>> table; //hash table
    int hashFunction(int studentID) const; //hash function for student

public:
    StudentTable(); // Constructor
    void add(int studentID, const string& courseName, const string& professorName, const vector<string>& professors); // Vector - professors for each course (to output to the options)
    void validateStudentID(int studentID);
    void checkRegistration() const;
    void displayRegistrations(int studentID) const;
};

#endif // STUDENT_REGISTRATION_H
