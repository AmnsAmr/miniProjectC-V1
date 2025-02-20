#include "teacher.h"
#include "student.h"
#include "globals.h"
#include <iostream>
using namespace std;

std::vector<std::shared_ptr<teacher>> teacher::allTeachers;

std::vector<std::shared_ptr<teacher>>& teacher::getTeachers() {
    return allTeachers;
}
// Constructor

teacher::teacher(string name, int age, string address, float sal, string sub, int exp, bool fullTime)
    : person(name, age, address), salary(sal), subject(sub) {
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
    if (!Assignments.empty()) {
        cout << "Assignments:\n";
        for (size_t i = 0; i < Assignments.size(); i++) {
            cout << "  - ";
            Assignments[i]->affichage();
        }
    }
    else {
        cout << "No assignments assigned.\n";
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

void teacher::addAssignment(std::shared_ptr<assignment> ass)
{
    Assignments.push_back(ass);
}

// Assign homework to all students
void teacher::AssignHomework(std::shared_ptr<assignment> homework) {
    for (auto& stud : students) {
        // Create a deep copy of the homework for each student
        auto studentHomework = std::make_shared<assignment>(*homework);
        stud->setAssignment(studentHomework);
    }
    // Optional: Keep the original in the teacher's list if needed
    Assignments.push_back(homework);
}
vector<std::shared_ptr<assignment>> teacher::getHomework() {
    vector<std::shared_ptr<assignment>> collected;
    for (auto& stud : students) {
        auto returned = stud->returnHomwork();
        collected.insert(collected.end(), returned.begin(), returned.end());
    }
    Assignments.insert(Assignments.end(), collected.begin(), collected.end());
    return collected;
}


void teacher::gradehomework() {
    for (auto& assgn : Assignments) {
        if (assgn->getifdone()) {
            cout << "Grading assignment: " << assgn->getTitle() << endl;
            float grade;
            cout << "Enter grade (0-20): ";
            cin >> grade;
            assgn->setGrade(grade);
            // Update the student's GPA
            for (auto& stud : students) {
                if (assgn->getTitle().find(stud->getName()) != string::npos) {
                    stud->calculateGPA();
                    break;
                }
            }
        }
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
    do {
        cout << "\nTeacher Menu:\n";
        cout << "1. Create a Teacher\n";
        cout << "2. Display All Teachers\n";
        cout << "3. Add a Student to this Teacher\n";
        cout << "4. Assign Homework to Students\n";
        cout << "5. Manage Assignments for this Teacher\n";
        cout << "6. Collect and Grade Homework\n";
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
            teacher::allTeachers.push_back(t);
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

            if (students.empty()) {
                cout << "No students available to add to the teacher.\n";
            }
            else {
                cout << "Available Students:\n";
                for (int i = 0; i < students.size(); ++i) {
                    cout << i + 1 << ". " << students[i]->getName() << "\n";
                }
                cout << "Enter the number of the student: ";
                int studentIndex;
                cin >> studentIndex;
                cin.ignore();
                if (studentIndex > 0 && studentIndex <= students.size()) {
                    auto studentToAdd = students[studentIndex - 1];
                    bool studentExists = false;
                    for (const auto& student : this->students) {
                        if (student == studentToAdd) {
                            studentExists = true;
                            break;
                        }
                    }
                    if (!studentExists) {
                        this->addStudent(students[studentIndex - 1]);
                        cout << "\nStudent added to the teacher successfully!\n";
                    }
                    else {
                        cout << "This student is already in this teacher's list.\n";
                    }
                }
                else {
                    cout << "Invalid student number!\n";
                }
            }

            break;
        }
        case 4: {
            if (assignments.empty()) {
                cout << "No assignments created yet, please create an assignment first.\n";
                auto a = std::make_shared<assignment>();
                a->input();
                Assignments.push_back(a);
                assignments.push_back(a);
                cout << "\nAssignment created successfully!\n";
                break;

            }
            else {

                cout << "Available Assignments:\n";
                for (int i = 0; i < assignments.size(); ++i) {
                    cout << i + 1 << ". " << assignments[i]->getTitle() << "\n";
                }
                cout << "Enter the number of the Assignment: ";
                int assignmentIndex;
                cin >> assignmentIndex;
                cin.ignore();
                if (assignmentIndex > 0 && assignmentIndex <= assignments.size()) {
                    this->AssignHomework(assignments[assignmentIndex - 1]);
                    this->addAssignment(assignments[assignmentIndex - 1]);
                    cout << "\nAssignment assigned to the teacher successfully!\n";
                }
                else {
                    cout << "Invalid Assignment number!\n";
                }
            }
            break;
        }
        case 5: {
            if (this->Assignments.empty()) {
                cout << "No assignments created yet for this teacher, please create one.\n";
                auto a = std::make_shared<assignment>();
                a->input();
                this->addAssignment(a);
                assignments.push_back(a);
                cout << "\nAssignment created and assigned successfully!\n";
            }
            else {
                cout << "Available Assignments for this teacher:\n";
                for (int i = 0; i < this->Assignments.size(); ++i) {
                    cout << i + 1 << ". " << this->Assignments[i]->getTitle() << "\n";
                }

                cout << "Enter the number of the assignment to manage (or 0 to go back): ";
                int assignmentIndex;
                cin >> assignmentIndex;
                cin.ignore();

                if (assignmentIndex > 0 && assignmentIndex <= this->Assignments.size()) {
                    // Change here as well.
                    this->Assignments[assignmentIndex - 1]->manageAssignmentMenu();
                }
                else if (assignmentIndex != 0) {
                    cout << "Invalid assignment number!\n";
                }

            }
            break;
        }
        case 6: {
            // Collect all completed assignments from students
            auto collected = this->getHomework();
            // Grade the collected assignments
            this->gradehomework();
            break;
        }
        case 0: return;
        default: cout << "Invalid choice!\n";
        }
    }while (choice != 0);
}