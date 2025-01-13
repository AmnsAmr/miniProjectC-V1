#include "School.h"

school::school(string n, principal p, float b, Library c) : Name(n), Principal(p), budget(b), library(c) { hasLibrary = true; }
school::school(string n, principal p, float b) : Name(n), Principal(p), budget(b) {}

string school::getname() {
    return Name;
}

principal school::getpricipal() {
    return Principal;
}
Library& school::getlibrary() { return library; }

void school::addTeacher(teacher& t) {
    teachers.push_back(t);
}

void school::addStudent(student& s) {
    students.push_back(s);
}

void school::addClassroom(Group& c) {
    Groups.push_back(c);
}

void school::addGuideline(string& guideline) {
    Guidelines.push_back(guideline);
}

void school::allocateBudget(float amount) {
    budget += amount;
}

void school::affichage() {
    cout << "School Name: " << Name << endl;
    Principal.affichage();
    cout << "Budget: " << budget << endl;

    cout << "Teachers: " << endl;
    for (auto& teacher : teachers) {
        teacher.affichage();
    }

    cout << "Students: " << endl;
    for (auto& student : students) {
        student.affichage();
    }

    cout << "Classrooms: " << endl;
    for (auto& classroom : Groups) {
        classroom.affichage();
    }
    if (hasLibrary) {
        library.affichage();
    }
    cout << "Guidelines: " << endl;
    for (auto& guideline : Guidelines) {
        cout << guideline << endl;
    }
}
void school::manageLibrary() {
    library.input();
}
void school::input() {
    cout << "Enter School Name: ";
    getline(cin, Name);

    cout << "Enter Principal Details:\n";
    Principal.input();

    cout << "Enter Initial Budget: ";
    cin >> budget;
    cin.ignore(); // Clear the input buffer

    char addLibrary;
    cout << "Do you want to add a library? (y/n): ";
    cin >> addLibrary;
    cin.ignore(); // Clear the input buffer

    if (addLibrary == 'y' || addLibrary == 'Y') {
        Library lib;
        lib.input(); // Assuming Library has an input function
        library = lib;
        hasLibrary = true;
    }
}