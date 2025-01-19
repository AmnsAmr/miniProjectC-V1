#include "assignment.h"

assignment::assignment(string title, string description, long long duedate)
    : Title(title), Description(description), Due_date(duedate), Grade(0), isDone(false) {
}

string assignment::getTitle() { return Title; }
string assignment::getDescription() { return Description; }

void assignment::markAsDone() { isDone = true; }

void assignment::setGrade(int grade) {
    if (grade >= 0 && grade <= 100) {
        Grade = grade;
    }
    else {
        cout << "Invalid grade! Please enter a value between 0 and 100.\n";
    }
}

void assignment::affichage() {
    cout << "Title: " << Title << "\n";
    cout << "Description: " << Description << "\n";
    cout << "Due Date: " << Due_date << "\n";
    cout << "Grade: " << Grade << "\n";
    cout << "Completed: " << (isDone ? "Yes" : "No") << "\n";
}

void assignment::input() {
    cout << "Enter Assignment Title: ";
    getline(cin, Title);

    cout << "Enter Assignment Description: ";
    getline(cin, Description);

    cout << "Enter Due Date (as a timestamp, e.g., 20231015 for October 15, 2023): ";
    cin >> Due_date;
    cin.ignore(); // Clear the input buffer
}

void assignment::manageAssignmentMenu(std::vector<std::shared_ptr<assignment>>& assignments) {
    int choice;
    cout << "\nAssignment Menu:\n";
    cout << "1. Create an Assignment\n";
    cout << "2. Display All Assignments\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();
    switch (choice) {
    case 1: {
        auto a = std::make_shared<assignment>();
        a->input();
        assignments.push_back(a);
        cout << "\nAssignment created successfully!\n";
        break;
    }
    case 2: {
        if (assignments.empty()) {
            cout << "No Assignment objects created yet!\n";
        }
        else {
            cout << "\nAll Assignments:\n";
            for (size_t i = 0; i < assignments.size(); ++i) {
                cout << "Assignment " << i + 1 << ":\n";
                assignments[i]->affichage();
                cout << "-----------------\n";
            }
        }
        break;
    }
    case 0: return;
    default: cout << "Invalid choice!\n";
    }
}