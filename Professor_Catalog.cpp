#include "Professor_Catalog.h"

using namespace std;

// Creates a new node
Node* newProf(const Professor& prof) {
    Node* newNode = new Node;
    newNode->data = prof;
    newNode->next = nullptr;
    return newNode;
}

// Inserts nodes into linked list
void insert(Node*& head, const Professor& prof) {
    Node* newNode = newProf(prof);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Reads .txt file and enters professor data
void readFromFile(Node*& head, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        Professor prof;
        prof.name = line;

        if (!getline(file, prof.courseID)) {
            cout << "Error reading courseID from file.\n";
            break;
        }

        if (!getline(file, line)) {
            cout << "Error reading rating from file.\n";
            break;
        }

        try {
            prof.rating = stod(line);
        } catch (const invalid_argument& e) {
            cout << "Error converting rating to double. Invalid input: " << line << endl;
            continue;
        }

        insert(head, prof);
    }

    file.close();
}

// Displays the linked list
void displayProfs(Node* head) {
    Node* temp = head;
    while (temp) {
        cout << "Professor: " << temp->data.name << endl;
        cout << "Course: " << temp->data.courseID << endl;
        cout << "Rating: " << temp->data.rating << endl;
        cout << "--------------------------" << endl;
        temp = temp->next;
    }
}

// Deletes the entire linked list to free memory
void deleteList(Node*& head) {
    Node* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
}