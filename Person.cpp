#include "person.h"

int person::Person_ID = 1;

person::person(string n, int a)
    : Name(n), Age(a){
}

person::person(string name, int age, string address)
    : Name(name), Age(age) {
}

void person::affichage() {
    cout << "Name: " << Name << "\n"
        << "Age: " << Age << "\n"
        << "ID: " << ID << "\n";
}

void person::input() {
    bool validName = false;
    while (!validName) {
        std::cout << "Enter Name: ";
        std::getline(std::cin, Name);
        if (Name.empty()) {
            std::cout << "Name cannot be empty. Please enter a name.\n";
        }
        else {
            validName = true;
        }
    }

    bool validInput = false;
    while (!validInput) {
        try {
            std::cout << "Enter Age: ";
            std::cin >> Age;
            if (std::cin.fail()) {
                std::cin.clear();  // Clear error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Clear input buffer
                throw std::runtime_error("Invalid input. Please enter a valid integer for age.");
            }
            validInput = true;
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    ID = Person_ID++; // Assign and increment ID
}

string person::getName() { return Name; }
int person::getAge() { return Age; }
int person::getID() { return ID; }

void person::setName(string& name) { Name = name; }
void person::setID(int id) { ID = id; }