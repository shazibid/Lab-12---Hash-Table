#include "Student_Registration.h"
#include <string>

int StudentTable::hashFunction(int studentID) const
{
    return studentID % SIZE;
}

StudentTable::StudentTable()
{
}

void StudentTable::add(int studentID, const string &courseName, const string &professorName)
{
    int index = hashFunction( studentID);

    if 


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
            return;
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

    // Hash studentID to locate the bucket
    int index = hashFunction(studentID);

    for (const auto &student : table[index]) // going through studentIDs in student table 
    {
        if (student.studentID == studentID) // if match found continue
        {
            for (const auto &reg : student.registeredCourses) // go thorugh the student registeredCourses (vector)
            {
                if (reg.courseName == courseName && reg.professorName == professorName) // if match found 
                {
                    cout << "Student " << studentID << "Is registered for " << courseName << " under professor "
                         << professorName;
                         return;
                }
                else // if not found
                {
                    cout << "Student " << studentID << "Is  NOT registered for " << courseName << " under Professor "
                         << professorName;
                        break;
                }
            }
        }
    }
}

void StudentTable::displayRegistrations(int studentID) const
{
}
