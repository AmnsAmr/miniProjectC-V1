#include "teacher.h"
#include "student.h"
#include "globals.h"
#include <iostream>
using namespace std;

// Constructor

teacher::teacher(string name, int age, string address, float sal, string sub, int exp, bool fullTime)
    : person(name, age, address), salary(sal), subject(sub){
}

// Display teacher details
void teacher::affichage() {
    person::affichage();
    cout << "Salary: " << salary << "\n"
        << "Subject: " << subject << "\n";
    if (!students.empty()) {
        cout << "Students: \n";
        for (size_t i = 0; i < students.size(); ++i) {
            cout << "  " << i + 1 << ". ";
            students[i]->affichage();
        }
    }
    else {
        cout << "No students assigned.\n";
    }
}

// Input teacher details
void teacher::input() {
    person::input();

    bool validInputSalary = false;
    while (!validInputSalary) {
        try {
            std::cout << "Enter Salary: ";
            std::cin >> salary;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error("Invalid input. Please enter a valid integer for salary.");
            }
            validInputSalary = true;
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

    bool validSubject = false;
    while (!validSubject) {
        std::cout << "Enter Subject: ";
        std::getline(std::cin, subject);
        if (subject.empty()) {
            std::cout << "Subject cannot be empty. Please enter a subject.\n";
        }
        else {
            validSubject = true;
        }
    }
}

void teacher::addStudent(std::shared_ptr<student> stud) {
    students.push_back(stud);
}

// Assign homework to all students
void teacher::AssignHomework(std::shared_ptr<assignment> homework) {
    for (auto& stud : students) {
        stud->setAssignment(homework);
    }
}

// Overloaded << operator
ostream& operator<<(ostream& COUT, teacher& teacher) {
    COUT << "Name: " << teacher.getName() << "\n"
        << "ID: " << teacher.getID() << "\n"
        << "Salary: " << teacher.salary << "\n"
        << "Subject: " << teacher.subject << "\n"
        << "Number of Students: " << teacher.students.size() << "\n";

    COUT << "Students: ";
    for (auto& stud : teacher.students) {
        COUT << stud->getName() << " (ID: " << stud->getID() << "), ";
    }
    COUT << "\n";

    return COUT;
}

void teacher::manageTeacherMenu(vector<std::shared_ptr<teacher>>& teachers, vector<std::shared_ptr<person>>& people, vector<std::shared_ptr<student>>& students, vector<std::shared_ptr<assignment>>& assignments) {
    int choice;
    cout << "\nTeacher Menu:\n";
    cout << "1. Create a Teacher\n";
    cout << "2. Display All Teachers\n";
    cout << "3. Add a Student to a Teacher\n";
    cout << "4. Assign Homework to Students\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1: {
        std::shared_ptr<teacher> t = std::make_shared<teacher>();
        t->input();
        people.push_back(t);
        teachers.push_back(t);
        cout << "\nTeacher created successfully!\n";
        break;
    }
    case 2: {
        if (teachers.empty()) {
            cout << "No Teacher objects created yet!\n";
        }
        else {
            cout << "\nAll Teachers:\n";
            for (int i = 0; i < teachers.size(); ++i) {
                cout << "Teacher " << i + 1 << ":\n";
                teachers[i]->affichage();
                cout << "-----------------\n";
            }
        }
        break;
    }
    case 3: {
        if (teachers.empty()) {
            cout << "No teachers available to add students.\n";
        }
        else if (students.empty()) {
            cout << "No students available to add to teachers.\n";
        }
        else {
            cout << "Available Teachers:\n";
            for (int i = 0; i < teachers.size(); ++i) {
                cout << i + 1 << ". " << teachers[i]->getName() << "\n";
            }
            cout << "Enter the number of the teacher: ";
            int teacherIndex;
            cin >> teacherIndex;
            cin.ignore();
            if (teacherIndex > 0 && teacherIndex <= teachers.size()) {
                cout << "Available Students:\n";
                for (int i = 0; i < students.size(); ++i) {
                    cout << i + 1 << ". " << students[i]->getName() << "\n";
                }
                cout << "Enter the number of the student: ";
                int studentIndex;
                cin >> studentIndex;
                cin.ignore();
                if (studentIndex > 0 && studentIndex <= students.size()) {
                    teachers[teacherIndex - 1]->addStudent(students[studentIndex - 1]);
                    cout << "\nStudent added to the teacher successfully!\n";
                }
                else {
                    cout << "Invalid student number!\n";
                }
            }
            else {
                cout << "Invalid teacher number!\n";
            }
        }
        break;
    }
    case 4: {
        if (teachers.empty()) {
            cout << "No teachers available to assign homework.\n";
        }
        else if (Assignments.empty()) {
            auto a = std::make_shared<assignment>();
            a->input();
            Assignments.push_back(a);
            assignments.push_back(a);
            cout << "\nAssignment created successfully!\n";
            break;
        }
        else if (assignments.empty()) {
            auto a = std::make_shared<assignment>();
            a->input();
            Assignments.push_back(a);
            assignments.push_back(a);
            cout << "\nAssignment created successfully!\n";
            break;
        }
        else {
            cout << "Available Teachers:\n";
            for (int i = 0; i < teachers.size(); ++i) {
                cout << i + 1 << ". " << teachers[i]->getName() << "\n";
            }
            cout << "Enter the number of the teacher: ";
            int teacherIndex;
            cin >> teacherIndex;
            cin.ignore();
            if (teacherIndex > 0 && teacherIndex <= teachers.size()) {
                cout << "Available Assignments:\n";
                for (int i = 0; i < Assignments.size(); ++i) {
                    cout << i + 1 << ". " << Assignments[i]->getTitle() << "\n";
                }
                cout << "Enter the number of the Assignment: ";
                int assignmentIndex;
                cin >> assignmentIndex;
                cin.ignore();
                if (assignmentIndex > 0 && assignmentIndex <= Assignments.size()) {
                    teachers[teacherIndex - 1]->AssignHomework(Assignments[assignmentIndex - 1]);
                    cout << "\nAssignment assigned to the teacher successfully!\n";
                }
                else {
                    cout << "Invalid Assignment number!\n";
                }
            }
            else {
                cout << "Invalid teacher number!\n";
            }
        }
        break;
    }
    case 0: return;
    default: cout << "Invalid choice!\n";
    }
}