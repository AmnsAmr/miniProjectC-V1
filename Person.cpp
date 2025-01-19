#include "person.h"

// Initialize static member
int person::Person_ID = 1;

// Constructors
person::person(string n, int a)
    : Name(n), Age(a){
}

person::person(string name, int age, string address)
    : Name(name), Age(age) {
}

// Display person details
void person::affichage() {
    cout << "Name: " << Name << "\n"
        << "Age: " << Age << "\n"
        << "ID: " << ID << "\n";
}

// Input person details
void person::input() {
    cout << "Enter Name: ";
    std::getline(cin, Name);

    cout << "Enter Age: ";
    cin >> Age;
    cin.ignore(); // Clear the input buffer after cin >>
    ID = Person_ID++; // Assign and increment ID
}

// Getters
string person::getName() { return Name; }
int person::getAge() { return Age; }
int person::getID() { return ID; }


// Setters
void person::setName(string& name) { Name = name; }
void person::setID(int id) { ID = id; }