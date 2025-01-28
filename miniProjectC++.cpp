#include "person.h"
#include "student.h"
#include "teacher.h"
#include "principal.h"
#include "book.h"
#include "Library.h"
#include "Group.h"
#include "assignment.h"
#include "School.h"
//#include "Prosecution.h"
//#include "MinistryOfEducation.h"
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
       /*case 4: {
            if (books.empty()) {
                auto b = std::make_shared<book>();
                b->input();
                books.push_back(b);
                b->manageBookMenu(books, libraries, schools);

            }
            else {
                cout << "Available books:\n";
                for (size_t i = 0; i < books.size(); i++) {
                    cout << i + 1 << ". " << books[i]->gettitle() << "\n";
                }
                cout << "Enter the number of the book you want to manage: ";
                int bookIndex;
                cin >> bookIndex;
                cin.ignore();
                if (bookIndex > 0 && bookIndex <= books.size()) {
                    books[bookIndex - 1]->manageBookMenu(books, libraries, schools);
                }
                else {
                    auto b = std::make_shared<book>();
                    b->input();
                    books.push_back(b);
                    b->manageBookMenu(books, libraries, schools);
                }
            }
            break;
        }*/ 
        case 5: {
            if (libraries.empty()) {
                cout << "No Library objects created yet!\n";
            }
            else {
                cout << "Available libraries:\n";
                for (size_t i = 0; i < libraries.size(); i++) {
                    // Assuming each school has a library, accessing through the school
                    if (!schools.empty())
                    {

                        cout << i + 1 << ". Library for " << schools[i]->getname() << "\n";


                    }
                }
                if (!schools.empty())
                {
                    cout << "Enter the number of the library you want to manage: ";
                    int libraryIndex;
                    cin >> libraryIndex;
                    cin.ignore();
                    if (libraryIndex > 0 && libraryIndex <= libraries.size()) {
                        schools[libraryIndex - 1]->getlibrary().manageLibraryMenu(libraries, students, books, schools);
                    }
                    else {
                        cout << "Invalid library number!\n";
                    }
                }
                else {
                    cout << "No schools created yet, a library can only be managed through school!\n";
                }

            }

            break;
        }
        case 6: {
            if (groups.empty()) {
                auto g = std::make_shared<Group>();
                g->input();
                groups.push_back(g);
                g->manageGroupMenu(groups, students);

            }
            else {
                cout << "Available groups:\n";
                for (size_t i = 0; i < groups.size(); i++) {
                    cout << i + 1 << ". " << groups[i]->getgroup() << "\n";
                }
                cout << "Enter the number of the group you want to manage: ";
                int groupIndex;
                cin >> groupIndex;
                cin.ignore();
                if (groupIndex > 0 && groupIndex <= groups.size()) {
                    groups[groupIndex - 1]->manageGroupMenu(groups, students);
                }
                else {
                    auto g = std::make_shared<Group>();
                    g->input();
                    groups.push_back(g);
                    g->manageGroupMenu(groups, students);
                }
            }
            break;
        }
        case 7: {
            if (assignments.empty()) {
                auto a = std::make_shared<assignment>();
                a->input();
                assignments.push_back(a);
                a->manageAssignmentMenu(assignments);

            }
            else {
                cout << "Available assignments:\n";
                for (size_t i = 0; i < assignments.size(); i++) {
                    cout << i + 1 << ". " << assignments[i]->getTitle() << "\n";
                }
                cout << "Enter the number of the assignment you want to manage: ";
                int assignmentIndex;
                cin >> assignmentIndex;
                cin.ignore();
                if (assignmentIndex > 0 && assignmentIndex <= assignments.size()) {
                    assignments[assignmentIndex - 1]->manageAssignmentMenu(assignments);
                }
                else {
                    auto a = std::make_shared<assignment>();
                    a->input();
                    assignments.push_back(a);
                    a->manageAssignmentMenu(assignments);
                }
            }
            break;
        }
        case 8: {
            if (schools.empty()) {
                auto s = std::make_shared<school>();
                s->input();
                schools.push_back(s);
                s->manageSchoolMenu(schools, students, books, libraries);

            }
            else {
                cout << "Available schools:\n";
                for (size_t i = 0; i < schools.size(); i++) {
                    cout << i + 1 << ". " << schools[i]->getname() << "\n";
                }
                cout << "Enter the number of the school you want to manage: ";
                int schoolIndex;
                cin >> schoolIndex;
                cin.ignore();
                if (schoolIndex > 0 && schoolIndex <= schools.size()) {
                    schools[schoolIndex - 1]->manageSchoolMenu(schools, students, books, libraries);
                }
                else {
                    auto s = std::make_shared<school>();
                    s->input();
                    schools.push_back(s);
                    s->manageSchoolMenu(schools, students, books, libraries);
                }
            }
            break;
        }
        /*case 9: {
            if (prosecutions.empty()) {
                auto p = std::make_shared<prosecution>();
                p->input();
                prosecutions.push_back(p);
                p->manageProsecutionMenu(prosecutions);

            }
            else {
                cout << "Available prosecutions:\n";
                for (size_t i = 0; i < prosecutions.size(); i++) {
                    cout << i + 1 << ". Prosecution " << i + 1 << "\n";
                }
                cout << "Enter the number of the prosecution you want to manage: ";
                int prosecutionIndex;
                cin >> prosecutionIndex;
                cin.ignore();
                if (prosecutionIndex > 0 && prosecutionIndex <= prosecutions.size()) {
                    prosecutions[prosecutionIndex - 1]->manageProsecutionMenu(prosecutions);
                }
                else {
                    auto p = std::make_shared<prosecution>();
                    p->input();
                    prosecutions.push_back(p);
                    p->manageProsecutionMenu(prosecutions);
                }
            }
            break;
        }*/
            //case 11: manageMinistryMenu(ministry); break;
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
    //cout << "4. Manage Books \n";
    //cout << "5. Manage Library\n";
    //cout << "6. Manage Groups\n";
    //cout << "7. Manage Assignments\n";
    cout << "8. Manage Schools\n";
    //cout << "9. Manage Prosecutions\n";
    //cout << "11. Manage Ministry of Education\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}
