#include "teacher.h"
#include "student.h"
#include <iostream>
using namespace std;

// Constructor
teacher::teacher(string name, int age, string address,float sal, string sub, int exp, bool fullTime)
    : person(name, age, address), salary(sal), subject(sub), experience(exp), isFullTime(fullTime) {
}

// Display teacher details
void teacher::affichage() {
    person::affichage();
    cout << "Salary: " << salary << "\n"
        << "Subject: " << subject << "\n"
        << "Experience: " << experience << " years\n"
        << "Full-Time: " << (isFullTime ? "Yes" : "No") << "\n";
    if (!students.empty()) {
        cout << "Students: \n";
        for (size_t i = 0; i < students.size(); ++i) {
            cout << "  " << i + 1 << ". ";
            students[i].affichage();
        }
    }
    else {
        cout << "No students assigned.\n";
    }
}

// Input teacher details
void teacher::input() {
    // Call the base class input function to fill person details
    person::input();

    // Input teacher-specific details
    cout << "Enter Salary: ";
    cin >> salary;
    cin.ignore(); // Clear the input buffer

    cout << "Enter Subject: ";
    getline(cin, subject);

    cout << "Enter Experience (years): ";
    cin >> experience;
    cin.ignore(); // Clear the input buffer

    cout << "Is Full-Time? (1 for Yes, 0 for No): ";
    cin >> isFullTime;
    cin.ignore(); // Clear the input buffer
}

// Add a student to the teacher's list
void teacher::addStudent(student stud) {
    students.push_back(stud);
}

// Assign homework to all students
void teacher::AssignHomework(assignment& homework) {
    for (auto& stud : students) {
        stud.getAssignment(homework);
    }
}

// Overloaded << operator
ostream& operator<<(ostream& COUT, teacher& teacher) {
    COUT << "Name: " << teacher.getName() << "\n"
        << "ID: " << teacher.getID() << "\n"
        << "Address: " << teacher.getAddress() << "\n"
        << "Salary: " << teacher.salary << "\n"
        << "Subject: " << teacher.subject << "\n"
        << "Experience (years): " << teacher.experience << "\n"
        << "Full-Time: " << (teacher.isFullTime ? "Yes" : "No") << "\n"
        << "Number of Students: " << teacher.students.size() << "\n";

    COUT << "Students: ";
    for (auto& stud : teacher.students) {
        COUT << stud.getName() << " (ID: " << stud.getID() << "), ";
    }
    COUT << "\n";

    return COUT;
}