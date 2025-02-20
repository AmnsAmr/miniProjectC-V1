#include "assignment.h"
#include "teacher.h"
#include <vector>
#include <memory>
using namespace std;

assignment::assignment(string title, string description)
    : Title(title), Description(description), Grade(0), isDone(false) {
}
assignment::assignment(const assignment& other)
    : Title(other.Title), Description(other.Description),
    Grade(other.Grade), isDone(other.isDone) {
}

string assignment::getTitle() { return Title; }
string assignment::getDescription() { return Description; }

void assignment::markAsDone() { isDone = true; }
int assignment::getGrade() { return Grade; }
bool assignment::getifdone() { return isDone; }

void assignment::addNameToTitle(string a) { Title.append(a); }
void assignment::setGrade(int grade) {
    if (grade >= 0 && grade <= 20) {
        Grade = grade;
    }
    else {
        cout << "Invalid grade! Please enter a value between 0 and 100.\n";
    }
}
std::string assignment::getLastWord() {
    size_t lastSpace = getTitle().find_last_of(" ");
    if (lastSpace == std::string::npos)
        return getTitle();
    return getTitle().substr(lastSpace + 1);
}

void assignment::affichage() {
    cout << "Title: " << Title << "\n";
    cout << "Description: " << Description << "\n";
    cout << "Grade: " << Grade << "\n";
    cout << "Completed: " << (isDone ? "Yes" : "No") << "\n";
}

void assignment::input() {
    cout << "Enter Assignment Title: ";
    getline(cin, Title);

    cout << "Enter Assignment Description: ";
    getline(cin, Description);
}
void assignment::manageAssignmentMenu() {
    int choice;
    do {
        cout << "\nAssignment Menu:\n";
        cout << "1. Create an Assignment for this teacher\n";
        cout << "2. Display Assignments for this teacher\n";
        cout << "0. Back to Teacher Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();


        teacher* currentTeacher = nullptr;


        for (auto& teacherPtr : teacher::getTeachers()) {
            for (const auto& assignmentPtr : teacherPtr->Assignments) {
                if (assignmentPtr.get() == this) {
                    currentTeacher = teacherPtr.get();
                    break;
                }
            }
            if (currentTeacher) {
                break;
            }
        }
        if (currentTeacher == nullptr) {
            cout << "Error: This assignment is not associated with a teacher.\n";
            return;
        }



        switch (choice) {
        case 1: {
            auto a = std::make_shared<assignment>();
            a->input();
            currentTeacher->Assignments.push_back(a);
            cout << "\nAssignment created successfully!\n";
            break;
        }
        case 2: {
            if (currentTeacher->Assignments.empty()) {
                cout << "No Assignment objects created for this teacher yet!\n";
            }
            else {
                cout << "\nAll Assignments:\n";
                for (size_t i = 0; i < currentTeacher->Assignments.size(); ++i) {
                    cout << "Assignment " << i + 1 << ":\n";
                    currentTeacher->Assignments[i]->affichage();
                    cout << "-----------------\n";
                }
            }
            break;
        }
        case 0: return;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}