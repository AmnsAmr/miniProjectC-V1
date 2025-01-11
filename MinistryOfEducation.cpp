#include "MinistryOfEducation.h"
#include <iostream>

Ministry_of_Education::Ministry_of_Education(const string& name, vector<string> policies, float annualBudget)
    : Name(name), Policies(policies), AnnualBudget(annualBudget) {
}

void Ministry_of_Education::addPolicy(string& policy) {
    Policies.push_back(policy);
}

void Ministry_of_Education::addProsecution(prosecution* p) {
    Prosecutions.push_back(p);
}

void Ministry_of_Education::affichage() {
    cout << "Ministry of Education Name: " << Name << endl;
    cout << "Annual Budget: " << AnnualBudget << endl;

    cout << "Policies: " << endl;
    for (auto& policy : Policies) {
        cout << "- " << policy << endl;
    }

    cout << "Prosecutions: " << endl;
    for (auto& prosecution : Prosecutions) {
        prosecution->affichage(); // Use -> for pointer
    }
}

void Ministry_of_Education::AllocateBudgetToSchool(school* school, float amount) {
    if (amount > AnnualBudget) {
        cout << "Not enough budget to allocate." << endl;
        return;
    }

    bool prosecutionApproval = false;
    for (auto& prosecution : Prosecutions) {
        for (auto& s : prosecution->getSchools()) { // Use -> for pointer
            if (s.getname() == school->getname()) { // Use -> for pointer
                cout << "Prosecution approved budget allocation for " << school->getname() << "." << endl;
                prosecutionApproval = true;
                break;
            }
        }
        if (prosecutionApproval) break;
    }

    if (!prosecutionApproval) {
        cout << "Prosecution did not approve budget allocation for " << school->getname() << "." << endl;
        return;
    }

    if (school->getpricipal().approveBudget(amount)) { // Use -> for pointer
        school->allocateBudget(amount); // Use -> for pointer
        AnnualBudget -= amount;
        cout << "Allocated " << amount << " to " << school->getname() << "." << endl;
    }
    else {
        cout << "Principal did not approve budget allocation for " << school->getname() << "." << endl;
    }
}

void Ministry_of_Education::PublishGuidelines(string& guideline) {
    cout << "Ministry of Education publishing guideline: " << guideline << endl;

    for (auto& prosecution : Prosecutions) {
        prosecution->addGuideline(guideline); // Use -> for pointer

        for (auto& school : prosecution->getSchools()) { // Use -> for pointer
            school.addGuideline(guideline);
        }
    }
    cout << "Guideline successfully published to all schools under the Ministry of Education." << endl;
}

void Ministry_of_Education::input() {
    cout << "Enter Ministry of Education Name: ";
    getline(cin, Name);

    cout << "Enter Annual Budget: ";
    cin >> AnnualBudget;
    cin.ignore(); // Clear the input buffer

    char addPolicyChoice;
    while (true) {
        cout << "Do you want to add a policy? (y/n): ";
        cin >> addPolicyChoice;
        cin.ignore(); // Clear the input buffer

        if (addPolicyChoice == 'y' || addPolicyChoice == 'Y') {
            string policy;
            cout << "Enter Policy: ";
            getline(cin, policy);
            this->addPolicy(policy); // Explicitly call the member function
        }
        else {
            break;
        }
    }

    char addProsecutionChoice;
    while (true) {
        cout << "Do you want to add a prosecution? (y/n): ";
        cin >> addProsecutionChoice;
        cin.ignore(); // Clear the input buffer

        if (addProsecutionChoice == 'y' || addProsecutionChoice == 'Y') {
            prosecution* p = new prosecution();
            p->input(); // Assuming prosecution has an input function
            this->addProsecution(p); // Explicitly call the member function
        }
        else {
            break;
        }
    }
}