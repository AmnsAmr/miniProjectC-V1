#ifndef MINISTRYOFEDUCATION_H
#define MINISTRYOFEDUCATION_H

#include <vector>
#include <string>
#include "Prosecution.h"

class Ministry_of_Education {
    string Name;
    vector<string> Policies;
    float AnnualBudget;
    vector<prosecution*> Prosecutions; // Use pointers to prosecutions

public:
    Ministry_of_Education(const string& name = "", vector<string> policies = {}, float annualBudget = 0.0);

    string& getName();

    void addPolicy(string& policy);
    void addProsecution(prosecution* p); // Accept a pointer to prosecution

    void affichage();
    void AllocateBudgetToSchool(school* school, float amount); // Accept a pointer to school
    void PublishGuidelines(string& guideline);

    void input(); // Add the input function
};

#endif