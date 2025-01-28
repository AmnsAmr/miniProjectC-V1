#include "MinistryOfEducation.h"
#include "globals.h"
#include <iostream>

Ministry_of_Education::Ministry_of_Education(const string& name, vector<string> policies, float annualBudget)
    : Name(name), Policies(policies), AnnualBudget(annualBudget) {
}

string& Ministry_of_Education::getName() { return Name; }


void Ministry_of_Education::addPolicy(string& policy) {
    Policies.push_back(policy);
}

void Ministry_of_Education::addProsecution(std::shared_ptr<prosecution> p) {
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
        prosecution->affichage();
    }
}

void Ministry_of_Education::AllocateBudgetToSchool(shared_ptr<school> school, float amount) {
    if (amount > AnnualBudget) {
        cout << "Not enough budget to allocate." << endl;
        return;
    }

    bool prosecutionApproval = false;
    for (auto& prosecution : Prosecutions) {
        for (auto& s : prosecution->getSchools()) {
            if (s->getname() == school->getname()) {
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

    if (school->getpricipal().approveBudget(amount)) {
        school->allocateBudget(amount);
        AnnualBudget -= amount;
        cout << "Allocated " << amount << " to " << school->getname() << "." << endl;
    }
    else {
        cout << "Principal did not approve budget allocation for " << school->getname() << "." << endl;
    }
}

/*void Ministry_of_Education::PublishGuidelines(string& guideline) {
    cout << "Ministry of Education publishing guideline: " << guideline << endl;

    for (auto& prosecution : Prosecutions) {
        prosecution->addGuideline(guideline);

        for (auto& school : prosecution->getSchools()) {
            school->addGuideline(guideline);
        }
    }
    cout << "Guideline successfully published to all schools under the Ministry of Education." << endl;
}*/

void Ministry_of_Education::input() {
    cout << "Enter Ministry of Education Name: ";
    getline(cin, Name);

    cout << "Enter Annual Budget: ";
    cin >> AnnualBudget;
    cin.ignore();

    char addPolicyChoice;
    while (true) {
        cout << "Do you want to add a policy? (y/n): ";
        cin >> addPolicyChoice;
        cin.ignore();

        if (addPolicyChoice == 'y' || addPolicyChoice == 'Y') {
            string policy;
            cout << "Enter Policy: ";
            getline(cin, policy);
            this->addPolicy(policy);
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
            std::shared_ptr<prosecution>  p = std::make_shared<prosecution>();
            p->input();
            this->addProsecution(p);
        }
        else {
            break;
        }
    }
}