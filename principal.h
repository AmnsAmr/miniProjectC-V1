#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <vector>
#include <string>
#include "person.h"

class principal : public person {
    float salary;
    int experience;
    std::vector<std::string> Policies;

public:
    principal(std::string n = "", int a = 0, float sal = 0.0, int exp = 0, std::vector<std::string> pol = {});

    bool approveBudget(float amount);
    void affichage();
    void input()override; // Declare the input function
};

#endif // PRINCIPAL_H