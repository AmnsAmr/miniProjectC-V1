#include "principal.h"
#include <iostream>

principal::principal(std::string n, int a, float sal, int exp, std::vector<std::string> pol)
    : person(n, a), salary(sal), experience(exp), Policies(pol) {
}

bool principal::approveBudget(float amount) {
    return amount <= 100000;
}

void principal::affichage() {
    person::affichage();
    std::cout << "Salary: " << salary << ", Experience: " << experience << " years" << std::endl;
}

void principal::input() {
    person::input(); // Call the base class input function to get Name, Age, and Address

    std::cout << "Enter Salary: ";
    std::cin >> salary;
    std::cin.ignore(); // Clear the input buffer after cin >>

    std::cout << "Enter Experience (in years): ";
    std::cin >> experience;
    std::cin.ignore(); // Clear the input buffer after cin >>

    std::cout << "Enter Policies (enter 'done' to finish):\n";
    std::string policy;
    while (true) {
        std::cout << "Policy: ";
        std::getline(std::cin, policy);
        if (policy == "done") {
            break;
        }
        Policies.push_back(policy);
    }
}