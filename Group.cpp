#include "Group.h"
#include "School.h"
#include <iostream>

Group::Group(std::string g, int rn, std::vector<std::shared_ptr<teacher>> t) : group(g), roomnumber(rn), Teachers(t) {}
Group::Group() : roomnumber(0), capacity(5) {}

std::string Group::getgroup() { return group; }

void Group::addStudent(std::shared_ptr<student> s) {
    if (students.size() < capacity) {
        students.push_back(s);
    }
    else {
        std::cout << "Classroom is full!" << std::endl;
    }
}
void Group::addTeacher(std::shared_ptr<teacher> t) {
    Teachers.push_back(t);

}


void Group::affichage() {
    std::cout << "Group Name: " << group << ", Room Number: " << roomnumber << ", Capacity: " << capacity << std::endl;
    std::cout << "Teachers: \n";
    for (const auto& t : Teachers) {
        std::cout << " -" << t->getName() << "\n";
    }
    std::cout << "Students: " << std::endl;
    for (const auto& student : students) {
        std::cout << " -" << student->getName() << "\n";
    }
}

void Group::input() {
    // Input group name
    std::cout << "Enter the group name: ";
    std::getline(std::cin, group);

    // Input room number
    std::cout << "Enter the room number: ";
    std::cin >> roomnumber;
    std::cin.ignore();
}


void Group::manageGroupMenu(std::vector<std::shared_ptr<Group>>& groups, std::shared_ptr<school> currentSchool) {
    int choice;
    do {
        std::cout << "\nGroup Menu:\n";
        std::cout << "1. Create a Group\n";
        std::cout << "2. Add a Student to this Group\n";
        std::cout << "3. Add a Teacher to this Group\n";
        std::cout << "4. Display the Groups\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1: {
            auto g = std::make_shared<Group>();
            g->input();
            groups.push_back(std::move(g));
            std::cout << "\nGroup created successfully!\n";
            break;
        }
        case 2: {
            if (currentSchool->getStudents().empty()) {
                std::cout << "No students available to add to a group in this school.\n";
            }
            else {
                std::cout << "Available Students:\n";
                for (int i = 0; i < currentSchool->getStudents().size(); ++i) {
                    std::cout << i + 1 << ". " << currentSchool->getStudents()[i]->getName() << "\n";
                }
                std::cout << "Enter the number of the student: ";
                int studentIndex;
                std::cin >> studentIndex;
                std::cin.ignore();

                if (studentIndex > 0 && studentIndex <= currentSchool->getStudents().size()) {
                    bool studentExists = false;
                    for (const auto& student : this->students) {
                        if (student == currentSchool->getStudents()[studentIndex - 1])
                        {
                            studentExists = true;
                            break;
                        }
                    }
                    if (!studentExists) {
                        this->addStudent(currentSchool->getStudents()[studentIndex - 1]);
                        std::cout << "\nStudent added to the group successfully!\n";
                    }
                    else {
                        std::cout << "This student is already in this group\n";
                    }
                }
                else {
                    std::cout << "Invalid student number!\n";
                }
            }
            break;
        }
        case 3: {
            if (!currentSchool) {
                std::cout << "Error: No school associated with this group.\n";
                break;
            }
            if (currentSchool->getTeachers().empty()) {
                std::cout << "No teachers available to add to a group in this school.\n";
            }
            else {
                std::cout << "Available Teachers:\n";
                for (int i = 0; i < currentSchool->getTeachers().size(); ++i) {
                    std::cout << i + 1 << ". " << currentSchool->getTeachers()[i]->getName() << "\n";
                }
                std::cout << "Enter the number of the teacher: ";
                int teacherIndex;
                std::cin >> teacherIndex;
                std::cin.ignore();

                if (teacherIndex > 0 && teacherIndex <= currentSchool->getTeachers().size()) {
                    bool teacherExists = false;
                    for (const auto& teacher : this->Teachers) {
                        if (teacher == currentSchool->getTeachers()[teacherIndex - 1])
                        {
                            teacherExists = true;
                            break;
                        }
                    }
                    if (!teacherExists) {
                        this->addTeacher(currentSchool->getTeachers()[teacherIndex - 1]);
                        std::cout << "\nTeacher added to the group successfully!\n";
                    }
                    else {
                        std::cout << "This teacher is already in this group\n";
                    }
                }
                else {
                    std::cout << "Invalid teacher number!\n";
                }
            }
            break;
        }
        case 4: {
            std::cout << "\nCurrent Group Details:\n";
            this->affichage();
            std::cout << "-----------------\n";
            break;
        }
        case 0: return;
        default: std::cout << "Invalid choice!\n";
        }
    }while (choice != 0);
}