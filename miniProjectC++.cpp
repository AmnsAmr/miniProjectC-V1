#include "person.h"
#include "student.h"
#include "teacher.h"
#include "principal.h"
#include "book.h"
#include "Library.h"
#include "Group.h"
#include "assignment.h"
#include "School.h"
#include "pch.h"
#include "globals.h"

void displayMainMenu();


int main() {
    int choice = 0;

    while (true) {
        displayMainMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            if (students.empty()) {
                auto s = std::make_shared<student>();
                s->input();
                people.push_back(s);
                students.push_back(s);
                s->manageStudentMenu(students, people, books, schools, libraries);

            }
            else
            {
                cout << "Available students:\n";
                for (size_t i = 0; i < students.size(); i++) {
                    cout << i + 1 << ". " << students[i]->getName() << "\n";
                }
                cout << "Enter the number of the student you want to manage: ";
                int studentIndex;
                cin >> studentIndex;
                cin.ignore();
                if (studentIndex > 0 && studentIndex <= students.size()) {
                    students[studentIndex - 1]->manageStudentMenu(students, people, books, schools, libraries);
                }
                else {
                    auto s = std::make_shared<student>();
                    s->input();
                    people.push_back(s);
                    students.push_back(s);
                    s->manageStudentMenu(students, people, books, schools, libraries);
                }
            }

            break;
        }
        case 2: {
            if (teachers.empty()) {
                auto t = std::make_shared<teacher>();
                t->input();
                people.push_back(t);
                teachers.push_back(t);
                t->manageTeacherMenu(teachers, people, students, assignments);

            }
            else {
                cout << "Available teachers:\n";
                for (size_t i = 0; i < teachers.size(); i++) {
                    cout << i + 1 << ". " << teachers[i]->getName() << "\n";
                }
                cout << "Enter the number of the teacher you want to manage: ";
                int teacherIndex;
                cin >> teacherIndex;
                cin.ignore();
                if (teacherIndex > 0 && teacherIndex <= teachers.size()) {
                    teachers[teacherIndex - 1]->manageTeacherMenu(teachers, people, students, assignments);
                }
                else {
                    auto t = std::make_shared<teacher>();
                    t->input();
                    people.push_back(t);
                    teachers.push_back(t);
                    t->manageTeacherMenu(teachers, people, students, assignments);
                }
            }
            break;
        }
        case 3: {
            if (principals.empty()) {
                auto p = std::make_shared<principal>();
                p->input();
                people.push_back(p);
                principals.push_back(p);
                p->managePrincipalMenu(principals, people);

            }
            else {
                cout << "Available principals:\n";
                for (size_t i = 0; i < principals.size(); i++) {
                    cout << i + 1 << ". " << principals[i]->getName() << "\n";
                }
                cout << "Enter the number of the principal you want to manage: ";
                int principalIndex;
                cin >> principalIndex;
                cin.ignore();
                if (principalIndex > 0 && principalIndex <= principals.size()) {
                    principals[principalIndex - 1]->managePrincipalMenu(principals, people);
                }
                else {
                    auto p = std::make_shared<principal>();
                    p->input();
                    people.push_back(p);
                    principals.push_back(p);
                    p->managePrincipalMenu(principals, people);
                }
            }
            break;
        }
        case 4: {
            cout << "1. Create a New School\n";
            cout << "2. Manage an Existing School\n";
            cout << "Enter your choice: ";
            int subChoice;
            cin >> subChoice;
            cin.ignore();

            if (subChoice == 1) {
                if (principals.empty()) {
                    cout << "No principals available. Create a principal first!\n";
                    break;
                }
               auto s = std::make_shared<school>();
                s->input();
                cout << "School created successfully!\n";
            }
            else if (subChoice == 2) {
                if (schools.empty()) {
                    cout << "No schools to manage.\n";
                    break;
                }
                cout << "Available Schools:\n";
                for (size_t i = 0; i < schools.size(); ++i) {
                    cout << i + 1 << ". " << schools[i]->getname() << endl;
                }
                cout << "Enter school number: ";
                int schoolIndex;
                cin >> schoolIndex;
                cin.ignore();
                if (schoolIndex < 1 || schoolIndex > schools.size()) {
                    cout << "Invalid index.\n";
                    break;
                }
                schools[schoolIndex - 1]->manageSchoolMenu(schools,students,books,libraries);
                
            }
            else {
                cout << "Invalid choice.\n";
            }
            break;
        }
        case 5: {
            if (schools.empty()) {
                cout << "There are no schools yet. Please create a school first.\n";
            }
            else {
                cout << "Available schools:\n";
                for (size_t i = 0; i < schools.size(); i++) {
                    cout << i + 1 << ". " << schools[i]->getname() << "\n";
                }
                cout << "Enter the number of the school you want to add a library/book to: ";
                int schoolIndex;
                cin >> schoolIndex;
                cin.ignore();

                if (schoolIndex > 0 && schoolIndex <= schools.size()) {
                    //Check if the library already exist
                    if (schools[schoolIndex - 1]->gethasLibrary()) {
                        cout << "create a book\n";
                        auto s = std::make_shared<book>();
                        schools[schoolIndex - 1]->getlibrary().input();
                    }
                }
                else {
                    cout << "Invalid school number. Please try again.\n";
                }
            }
            break;
        }
        case 0: {
            cout << "Exiting the program...\n";
            return 0;
        }
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    }
    return 0;
}
void displayMainMenu() {
    cout << "\nMain Menu:\n";
    cout << "1. Manage Students\n";
    cout << "2. Manage Teachers\n";
    cout << "3. Manage Principals\n";
    cout << "4. Manage Schools\n";
    cout << "5. create a book\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}
