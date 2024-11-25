#ifndef STUDENT_REGISTRATION_H
#define STUDENT_REGISTRATION_H
#include <iostream>
#include <vector>
#include "Professor_Catalog.h"


using namespace std;

// Hash class for student registrations
class StudentTable
{
private:
    // ==== Registration Struct ===============================================
    // Represents a course and the professor teaching it.
    //
    // Fields:
    // - courseName: The name of the course (e.g., "CS-1D").
    // - professorName: The name of the professor teaching the course.
    //
    // Purpose:
    // - Bundles the course name and professor name into a single structure.
    // - Used in the `Student` struct to represent the courses a student is registered for.
    // =========================================================================

    struct Registration
    { // Keeps us from using two seperate vectors for course and professor
        string courseName;
        string professorName;

        Registration(const string &course, const string &professor)
            : courseName(course), professorName(professor) {}
    };

    // ==== Student Struct ====================================================
    // Represents a student and their registered courses.
    //
    // Fields:
    // - studentID: A unique identifier for the student (e.g., 100001).
    // - registeredCourses: A vector of `Registration` objects, representing 
    //   the courses and professors the student is registered for.
    //
    // Purpose:
    // - Stores a student's information and their course registrations.
    // - Provides flexibility for students to register for multiple courses
    //   by using a vector of `Registration` structs.
    // =========================================================================

    struct Student
    {
        int studentID;
        vector<Registration> registeredCourses; // student may have registered for multiple classes, vector allows for flexibility

        Student(int id) : studentID(id) {}
    };

    static const int SIZE = 15;            // smaller size to keep things simple
    //====== StuTable Vector======================================================
    // Purpose:
    // - Organizes students by their hashed studentID, allowing efficient lookups.
    // - Each bucket in the outer vector stores a list of `Student` structs that
    //   hash to the same index.
    //
    // Why this approach:
    // - The hash table structure ensures O(1) average-case access time for lookups.
    // - Separate chaining (vector of vectors) handles hash collisions effectively.
    vector<vector<Student>> StuTable;

    // Purpose of professorTablePtr:
    // - Provides access to professor and course data stored in the `ProfessorTable`.
    // - Used in functions like `add` and `rateProfessor` to search for professors
    //   and update their ratings.
    ProfessorTable* professorTablePtr;     

    // ====hashFunction ======================================================
    // Computes the hash index for a given student ID.
    // Input:
    // - studentID: The unique identifier for a student.
    // Output:
    // - Returns an integer index corresponding to the hash table bucket.
    // Purpose:
    // - Maps student IDs to hash table indices for efficient storage and lookup.

    int hashFunction(int studentID) const; // hash function for student

public:
    StudentTable(ProfessorTable* professorTablePtr);                                                                                                   // Constructor
    void add(); 
    bool validateID(int studentID);
    void checkRegistration() const;
    void registerForCourseOrProfessor(Student &student, const string &searchKey);
    void rateProfessor() ;
    void displayRegistrations(int studentID) const;
};

#endif // STUDENT_REGISTRATION_H
