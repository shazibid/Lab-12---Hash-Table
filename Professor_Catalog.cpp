//
// Created by Shazi Bidarian on 11/13/24.
//
#include "Professor_Catalog.h"
#include <iostream>
#include <ostream>
#include <iostream>
#include <string>
using namespace std;


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


};