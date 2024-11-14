//
// Created by Shazi Bidarian on 11/13/24.
//

#ifndef PROFESSOR_CATALOG_H
#define PROFESSOR_CATALOG_H
#include <iostream>
#include <string>
using namespace std;

//essentially is professor node
class Professor_Catalog {
private:
    string prof;    //this is our hashmap key
    string courseName;  //this is our hashmap value
    double rating;

public:
    Professor_Catalog(string prof, string courseName, double rating) {
        this->prof = prof;
        this->courseName = courseName;
        this->rating = rating;
    }

    ~Professor_Catalog() {}

    bool readFile(fstream& file, char* name);  //error catching
    void writeFile(fstream& file, string& prof, string& courseName);   //inputs .txt data into file
};


#endif //PROFESSOR_CATALOG_H
