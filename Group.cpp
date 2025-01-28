#include "Group.h"
#include <iostream>

Group::Group(std::string g, int rn, std::vector<teacher> t) : group(g), roomnumber(rn), Teachers(t) {}
Group::Group() : roomnumber(0), capacity(5) {}

string Group::getgroup() { return group; }

void Group::addStudent(student& s) {
    if (students.size() < capacity) {
        students.push_back(s);
    }
    else {
        std::cout << "Classroom is full!" << std::endl;
    }
}

void Group::affichage() {
    std::cout << "Group Name: " << group << ", Room Number: " << roomnumber << ", Capacity: " << capacity << std::endl;
    std::cout << "Teachers: \n";
    for (auto& t : Teachers) {
        t.affichage();
    }
    std::cout << "Students: " << std::endl;
    for (auto& student : students) {
        student.affichage();
    }
}

void Group::input() {
    // Input group name
    std::cout << "Enter the group name: ";
    std::getline(std::cin, group);

    // Input room number
    std::cout << "Enter the room number: ";
    std::cin >> roomnumber;
    std::cin.ignore(); // Clear the input buffer

    // Input teachers (optional)
    char addTeacher;
    std::cout << "Do you want to add a teacher to the group? (y/n): ";
    std::cin >> addTeacher;
    std::cin.ignore(); // Clear the input buffer

    if (addTeacher == 'y' || addTeacher == 'Y') {
        std::string teacherName;
        std::cout << "Enter the teacher's name: ";
        std::getline(std::cin, teacherName);

        // Create a temporary teacher object
        teacher t(teacherName, 0, "", 0.0, 0); // Assuming default values for other attributes
        Teachers.push_back(t);
    }
}

// New function implementation
void Group::addStudentToGroup(std::vector<std::shared_ptr<Group>>& groups, const std::vector<std::shared_ptr<student>>& students) {
    if (groups.empty()) {
        std::cout << "No groups available to add a student.\n";
    }
    else if (students.empty()) {
        std::cout << "No students available to add to a group.\n";
    }
    else {
        std::cout << "Available Groups:\n";
        for (int i = 0; i < groups.size(); ++i) {
            std::cout << i + 1 << ". " << groups[i]->group << "\n";
        }
        std::cout << "Enter the number of the group: ";
        int groupIndex;
        std::cin >> groupIndex;
        std::cin.ignore(); // Clear the input buffer

        if (groupIndex > 0 && groupIndex <= groups.size()) {
            std::cout << "Available Students:\n";
            for (int i = 0; i < students.size(); ++i) {
                std::cout << i + 1 << ". " << students[i]->getName() << "\n";
            }
            std::cout << "Enter the number of the student: ";
            int studentIndex;
            std::cin >> studentIndex;
            std::cin.ignore(); // Clear the input buffer

            if (studentIndex > 0 && studentIndex <= students.size()) {
                groups[groupIndex - 1]->addStudent(*students[studentIndex - 1]);
                std::cout << "\nStudent added to the group successfully!\n";
            }
            else {
                std::cout << "Invalid student number!\n";
            }
        }
        else {
            std::cout << "Invalid group number!\n";
        }
    }
}

void Group::manageGroupMenu(std::vector<std::shared_ptr<Group>>& groups, const std::vector<std::shared_ptr<student>>& students) {
    int choice;
    cout << "\nGroup Menu:\n";
    cout << "1. Create a Group\n";
    cout << "2. Add a Student to a Group\n";
    cout << "3. Display All Groups\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1: {
        auto g = std::make_shared<Group>();
        g->input();
        groups.push_back(std::move(g));
        cout << "\nGroup created successfully!\n";
        break;
    }
    case 2: {
        this->addStudentToGroup(groups, students);
        break;
    }
    case 3: {
        if (groups.empty()) {
            cout << "No Group objects created yet!\n";
        }
        else {
            cout << "\nAll Groups:\n";
            for (size_t i = 0; i < groups.size(); ++i) {
                cout << "Group " << i + 1 << ":\n";
                groups[i]->affichage();
                cout << "-----------------\n";
            }
        }
        break;
    }
    case 0: return;
    default: cout << "Invalid choice!\n";
    }
}