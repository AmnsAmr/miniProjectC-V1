#include "person.h"

// Initialize static member
int person::Person_ID = 1;

// Constructors
person::person(string n, int a)
    : Name(n), Age(a), Address("") {
}

person::person(string name, int age, string address)
    : Name(name), Age(age), Address(address) {
}

// Display person details
void person::affichage() {
    cout << "Name: " << Name << "\n"
        << "Age: " << Age << "\n"
        << "ID: " << ID << "\n"
        << "Address: " << Address << "\n";
}

// Input person details
void person::input() {
    cout << "Enter Name: ";
    std::getline(cin, Name);

    cout << "Enter Age: ";
    cin >> Age;
    cin.ignore(); // Clear the input buffer after cin >>

    cout << "Enter Address: ";
    std::getline(cin, Address);
    ID = Person_ID++; // Assign and increment ID
}

// Getters
string person::getName() { return Name; }
int person::getAge() { return Age; }
int person::getID() { return ID; }
string person::getAddress() { return Address; }

// Setters
void person::setName( string& name) { Name = name; }
void person::setID(int id) { ID = id; }
void person::setAddress( string& address) { Address = address; }
