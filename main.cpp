#include <iostream>
#include "Professor_Catalog.h"
#include "Student.h"
using namespace std;


int main() {
ProfessorTable professorTable(10);
    string professorFile = "professor.txt";

    // Initialize the student table (can be done here safely)
    StudentTable studentTable(&professorTable);

    // Read the professor data from the file
    professorTable.readFromFile(professorFile);
    professorTable.insert("Dr. Smith", "Data Structures", 4.5, 4);

    StudentTable studentRegistration(&professorTable);

   // QUICK ADD USED FOR TESTING 
    studentRegistration.add();


    //Test the rateProfessor function
    cout << "\n--- Testing rateProfessor ---\n";
    studentRegistration.rateProfessor();
    
    system("cls");

    //Display to verify rating update
    cout << "\n\nDisplaying updated professor catalog:\n";
    professorTable.display();
    
    cout << "\nTesting CHECK...\n";
    studentRegistration.checkRegistration();
    

    return 0;
}
/*OUTPUT:

Enter Student ID: 100001
Enter search key (course or professor name): Med Mogasemi
Student ID not found. Creating a new student profile...
Searching for Med Mogasemi...

Med Mogasemi teaches multiple courses. Select one:
1. CS-1A
2. CS-1D
Enter your choice (1-2): 2
Student 100001 registered for CS-1D under Professor Med Mogasemi.
Registered Course: CS-1D, Professor: Med Mogasemi
New student profile created and registered.

--- Testing rateProfessor ---
Enter ID: 100001

Enter Professor name:Joe Bannet


Displaying updated professor catalog:
Index 1:
  Professor: Med Mogasemi
  Rating: 4.5
  Courses: CS-1A CS-1D 
  Professor: Bob Badman
  Rating: 4.2
  Courses: CS-1C 
  Professor: Nadia The_Best
  Rating: 4.7
  Courses: CS-1D 
Index 2:
  Professor: Joe Bannet
  Rating: 3.6
  Courses: CS-1A 
  Professor: George Goodman
  Rating: 5
  Courses: CS-3B CS-1D 
  Professor: Dr. Smith
  Rating: 4.5
  Courses: Data Structures 
Index 3:
  Professor: Homi The_Man
  Rating: 4.7
  Courses: CS-1C CS-1A 
Index 6:
  Professor: Med Learn_as_he_teach
  Rating: 3.9
  Courses: CS-1D 
  Professor: Carlos Olive
  Rating: 4.3
  Courses: CS-1B 

Testing CHECK...
Enter student ID: 100001
Enter course name: CS-1D
Enter professor name: Med Mogasemi
Student 100001 Is registered for CS-1D under professor Med Mogasemi



*/
