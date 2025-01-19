#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <vector>
#include <string>
#include <memory>
#include "person.h"

class principal : public person {
    float salary;
    int experience;
    std::vector<std::string> Policies;

public:
    principal(std::string n = "", int a = 0, float sal = 0.0, int exp = 0, std::vector<std::string> pol = {});

    bool approveBudget(float amount);
    void affichage() override;
    void input() override;
    void managePrincipalMenu(std::vector<std::shared_ptr<principal>>& principals, std::vector<std::shared_ptr<person>>& people);
};

#endif // PRINCIPAL_H