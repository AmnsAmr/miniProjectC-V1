#include "principal.h"
#include <iostream>

principal::principal(std::string n, int a, float sal)
    : person(n, a), salary(sal) {
}

bool principal::approveBudget(float amount) {
    return amount <= 100000;
}

void principal::affichage() {
    person::affichage();
    std::cout << "Salary: " << salary <<"\n";
}

void principal::input() {
    person::input();

    bool validInputSalary = false;
    while (!validInputSalary) {
        try {
            std::cout << "Enter Salary: ";
            std::cin >> salary;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error("Invalid input. Please enter a valid integer for the salary.");
            }
            validInputSalary = true;
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
}


void principal::managePrincipalMenu(std::vector<std::shared_ptr<principal>>& principals, std::vector<std::shared_ptr<person>>& people) {
    int choice;
    std::cout << "\nPrincipal Menu:\n";
    std::cout << "1. Create a Principal\n";
    std::cout << "2. Display All Principals\n";
    std::cout << "0. Back to Main Menu\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    std::cin.ignore();

    switch (choice) {
    case 1: {
        auto pr = std::make_shared<principal>();
        pr->input();
        people.push_back(pr);
        principals.push_back(pr);
        std::cout << "\nPrincipal created successfully!\n";
        break;
    }
    case 2: {
        if (principals.empty()) {
            std::cout << "No Principal objects created yet!\n";
        }
        else {
            std::cout << "\nAll Principals:\n";
            for (size_t i = 0; i < principals.size(); ++i) {
                std::cout << "Principal " << i + 1 << ":\n";
                principals[i]->affichage();
                std::cout << "-----------------\n";
            }
        }
        break;
    }
    case 0: return;
    default: std::cout << "Invalid choice!\n";
    }
}