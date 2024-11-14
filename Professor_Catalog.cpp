//
// Created by Shazi Bidarian on 11/13/24.
//
#include "Professor_Catalog.h"
using namespace std;

/*
 * Do the following for prof catalog
 * 1. open txt file
 * 2. check if file opens (bool)
 * 3. read txt file into profs
 */

bool Professor_Catalog::readFile(fstream &file, char* name) {
    file.open(name, ios::in);

    if (file.fail()) {
        return false;
    } else {
        return true;
    }
}
void Professor_Catalog::writeFile(fstream &file, string& professor, char* name) {

}
