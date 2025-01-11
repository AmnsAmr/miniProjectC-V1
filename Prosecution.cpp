#include "Prosecution.h"
#include <iostream>
prosecution::prosecution() {};
prosecution::prosecution(vector<string>& guidelines, vector<school>& schoolsList)
    : Guidelines(guidelines), schools(schoolsList) {
}

vector<school>& prosecution::getSchools() {
    return schools;
}

void prosecution::addGuideline(string& guideline) {
    Guidelines.push_back(guideline);
}

void prosecution::addSchool(school& s) {
    schools.push_back(s);
}

void prosecution::affichage() {
    cout << "Prosecution Guidelines: " << endl;
    for (auto& guideline : Guidelines) {
        cout << "- " << guideline << endl;
    }

    cout << "Schools under this prosecution: " << endl;
    for (auto& s : schools) {
        s.affichage();
    }
}

void prosecution::input() {
    int choice = 0;
    while (true) {
        cout << "\nProsecution Menu:\n";
        cout << "1. Add a Guideline\n";
        cout << "2. Add a School\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the input buffer

        switch (choice) {
        case 1: {
            string guideline;
            cout << "Enter Guideline: ";
            getline(cin, guideline);
            addGuideline(guideline);
            cout << "Guideline added successfully.\n";
            break;
        }
        case 2: {
            school s;
            s.input(); // Assuming School has an input function
            addSchool(s);
            cout << "School added successfully.\n";
            break;
        }
        case 0: {
            return; // Exit the input function
        }
        default: {
            cout << "Invalid choice! Please try again.\n";
            break;
        }
        }
    }
}