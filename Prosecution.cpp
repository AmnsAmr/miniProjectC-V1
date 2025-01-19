#include "Prosecution.h"
#include <iostream>
prosecution::prosecution() {};
prosecution::prosecution(vector<string>& guidelines, vector<std::shared_ptr<school>>& schoolsList)
    : Guidelines(guidelines), schools(schoolsList) {
}

vector<std::shared_ptr<school>>& prosecution::getSchools() {
    return schools;
}

void prosecution::addGuideline(string& guideline) {
    Guidelines.push_back(guideline);
}

void prosecution::addSchool(std::shared_ptr<school> s) {
    schools.push_back(s);
}

void prosecution::affichage() {
    cout << "Prosecution Guidelines: " << endl;
    for (auto& guideline : Guidelines) {
        cout << "- " << guideline << endl;
    }

    cout << "Schools under this prosecution: " << endl;
    for (auto& s : schools) {
        s->affichage();
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
            auto s = std::make_shared<school>();
            s->input(); // Assuming School has an input function
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

void prosecution::manageProsecutionMenu(std::vector<std::shared_ptr<prosecution>>& prosecutions) {
    int choice;
    cout << "\nProsecution Menu:\n";
    cout << "1. Create a Prosecution\n";
    cout << "2. Display All Prosecutions\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1: {
        auto p = std::make_shared<prosecution>();
        p->input();
        prosecutions.push_back(p);
        cout << "\nProsecution created successfully!\n";
        break;
    }
    case 2: {
        if (prosecutions.empty()) {
            cout << "No Prosecution objects created yet!\n";
        }
        else {
            cout << "\nAll Prosecutions:\n";
            for (size_t i = 0; i < prosecutions.size(); ++i) {
                cout << "Prosecution " << i + 1 << ":\n";
                prosecutions[i]->affichage();
                cout << "-----------------\n";
            }
        }
        break;
    }
    case 0: return;
    default: cout << "Invalid choice!\n";
    }
}