#include"Student.h"
#include "book.h" 
using namespace std;

int student::Student_ID = 1;

student::student(){}
student::student(string& name, int& age, string& address,string& grade, string& parent_contact)
    : person(name, age, address),
    Grade(grade),
    Student_id(Student_ID++),
    Parent_contact(parent_contact) {
}

vector<book>& student::getbooklist() { return Books_borrowed; }

string student::getname() { return Name; }
void student::getAssignment(assignment hw) {
    Assignments.push_back(hw);
}

void student::displayAssignments() {
    for ( auto& assgn : Assignments) {
        assgn.affichage();
    }
}

void student::affichage() {
    person::affichage();
    cout << "Student ID: " << Student_id << "\n";
    cout << "Grade: " << Grade << "\n";
    cout << "GPA: " << GPA << "\n";
    cout << "Parent Contact: " << Parent_contact << "\n";
    cout << "Subjects: ";
    for ( auto& subject : Subjects) {
        cout << subject << " ";
    }
    cout << "\nBooks Borrowed: " << Books_borrowed.size() << "\n";
    cout << "Assignments: " << Assignments.size() << "\n";
}

void student::input() {
    // Call the base class input function to fill person details
    person::input();

    // Input student-specific details
    cout << "Enter Grade: ";
    cin >> Grade;
    cin.ignore(); // Clear the input buffer

   /* cout << "Enter GPA: ";
    cin >> GPA;
    cin.ignore(); // Clear the input buffer
   */
    cout << "Enter Parent Contact: ";
    getline(cin, Parent_contact);

    cout << "Enter Subjects (type 'done' to finish):\n";
    string subject;
    while (true) {
        cout << "Subject: ";
        getline(cin, subject);
        if (subject == "done") break;
        Subjects.push_back(subject);
    }

    // Assign a unique Student ID
    Student_id = Student_ID++;
}


void student::addrating(string& name, float a) {
    bool found = false;
    for (auto& book : Books_borrowed) {
        if (book.gettitle().find(name) != string::npos) {
            book.setratings(a);
            found = true;
        }
    }
    if (!found) {
        cout << "No books found with the name \"" << name << "\".\n";
    }
}
void student::returnbook(Library& library,  string& name) {
    bool found = false;
    for (auto i = Books_borrowed.begin(); i != Books_borrowed.end(); ) {
        if (i->gettitle().find(name) != string::npos) {
            library.setbooks(*i);
            i = Books_borrowed.erase(i);
            found = true;
        }
        else {
            ++i;
        }
    }
    if (!found) {
        cout << "No books found with the name \"" << name << "\".\n";
    }
}

ostream& operator<<(ostream& COUT, student& student) {
    COUT << "Name: " << student.getName() << "\n"
        << "ID: " << student.getID() << "\n"
        << "Address: " << student.getAddress() << "\n"
        << "Student ID: " << student.Student_id << "\n"
        << "Grade: " << student.Grade << "\n"
        << "GPA: " << student.GPA << "\n"
        << "Parent Contact: " << student.Parent_contact << "\n"
        << "Subjects: ";
    for (auto& subject : student.Subjects) {
        COUT << subject << " ";
    }
    COUT << "\nBooks Borrowed: " << student.Books_borrowed.size() << "\n"
        << "Assignments: " << student.Assignments.size() << "\n";
    return COUT;
}

