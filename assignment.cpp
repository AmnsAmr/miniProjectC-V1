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