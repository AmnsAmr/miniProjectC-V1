#include "School.h"


school::school(string n, principal p, float b, Library c) : Name(n), Principal(p), budget(b), library(c) { hasLibrary = true; }
school::school(string n, principal p, float b) : Name(n), Principal(p), budget(b) {}

string school::getname() { return Name; }
principal school::getpricipal() { return Principal; }
Library& school::getlibrary() { return library; }

void school::setlibrary() {}

void school::addTeacher(std::shared_ptr<teacher> t) { Teachers.push_back(t); }

void school::addStudent(std::shared_ptr<student> s) { Students.push_back(s); }

void school::addClassroom(Group& c) { Groups.push_back(c); }

void school::addGuideline(string& guideline) { Guidelines.push_back(guideline); }

void school::allocateBudget(float amount) { budget += amount; }

void school::affichage() {
    cout << "School Name: " << Name << endl;
    Principal.affichage();
    cout << "Budget: " << budget << endl;

    cout << "Teachers: " << endl;
    for (auto& teacher : Teachers) {
        teacher->affichage();
    }

    cout << "Students: " << endl;
    for (auto& student : Students) {
        student->affichage();
    }

    cout << "Classrooms: " << endl;
    for (auto& classroom : Groups) {
        classroom.affichage();
    }
    if (hasLibrary) {
        library.affichage();
    }
    cout << "Guidelines: " << endl;
    for (auto& guideline : Guidelines) {
        cout << guideline << endl;
    }
}
void school::manageLibrary(std::vector<std::unique_ptr<Library>>& library, std::vector<std::shared_ptr<student>>& students, std::vector<std::shared_ptr<book>>& books, std::vector<std::shared_ptr<school>>& schools) {
    this->library.manageLibraryMenu(library, students, books, schools);
}
void school::input() {
    cout << "Enter School Name: ";
    getline(cin, Name);

    cout << "Enter Principal Details:\n";
    Principal.input();

    cout << "Enter Initial Budget: ";
    cin >> budget;
    cin.ignore();

    char addLibrary;
    cout << "Do you want to add a library? (y/n): ";
    cin >> addLibrary;
    cin.ignore();

    if (addLibrary == 'y' || addLibrary == 'Y') {
        Library lib;
        lib.input();
        library = lib;
        hasLibrary = true;
    }
}

void school::manageSchoolMenu(std::vector<std::shared_ptr<school>>& schools, std::vector<std::shared_ptr<student>>& students, std::vector<std::shared_ptr<book>>& books, std::vector<std::unique_ptr<Library>>& library) {
    int choice;
    cout << "\nSchool Menu:\n";
    cout << "1. Create a School\n";
    cout << "2. Display All Schools\n";
    cout << "3. Manage School Library\n";
    cout << "4. Add a Student to the school\n";
    cout << "5. Add a Teacher to the school\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1: {
        auto s = std::make_shared<school>();
        s->input();
        schools.push_back(s);
        cout << "\nSchool created successfully!\n";
        break;
    }
    case 2: {
        if (schools.empty()) {
            cout << "No School objects created yet!\n";
        }
        else {
            cout << "\nAll Schools:\n";
            for (size_t i = 0; i < schools.size(); ++i) {
                cout << "School " << i + 1 << ":\n";
                schools[i]->affichage();
                cout << "-----------------\n";
            }
        }
        break;
    }
    case 3: {
        if (schools.empty()) {
            cout << "No School objects created yet!\n";
        }
        else {
            cout << "Available schools:\n";
            for (size_t i = 0; i < schools.size(); i++) {
                cout << i + 1 << ". " << schools[i]->getname() << "\n";
            }
            cout << "Enter the number of the school to manage the library: ";
            int schoolIndex;
            cin >> schoolIndex;
            cin.ignore();
            if (schoolIndex > 0 && schoolIndex <= schools.size()) {
                schools[schoolIndex - 1]->manageLibrary(library, students, books,schools);
            }
            else {
                cout << "Invalid school number!\n";
            }
        }
        break;
    }
    case 4: {
        if (schools.empty()) {
            cout << "No schools created yet.\n";
        }
        else if (students.empty()) {
            cout << "No students available to add to schools.\n";
        }
        else {
            cout << "Available Schools:\n";
            for (int i = 0; i < schools.size(); ++i) {
                cout << i + 1 << ". " << schools[i]->getname() << "\n";
            }
            cout << "Enter the number of the school: ";
            int schoolIndex;
            cin >> schoolIndex;
            cin.ignore();
            if (schoolIndex > 0 && schoolIndex <= schools.size()) {
                cout << "Available Students:\n";
                for (int i = 0; i < students.size(); ++i) {
                    cout << i + 1 << ". " << students[i]->getName() << "\n";
                }
                cout << "Enter the number of the student: ";
                int studentIndex;
                cin >> studentIndex;
                cin.ignore();
                if (studentIndex > 0 && studentIndex <= students.size()) {
                    schools[schoolIndex - 1]->addStudent(students[studentIndex - 1]);
                    cout << "\nStudent added to school successfully!\n";
                    students[studentIndex - 1]->setAssociatedSchool(schools[schoolIndex - 1].get());
                }
                else {
                    cout << "Invalid student number!\n";
                }
            }
            else {
                cout << "Invalid school number!\n";
            }
        }
        break;
    }
    case 5: {
        if (schools.empty()) {
            cout << "No schools created yet.\n";
        }
        else if (teachers.empty()) {
            cout << "No teachers available to add to schools.\n";
        }
        else {
            cout << "Available Schools:\n";
            for (int i = 0; i < schools.size(); ++i) {
                cout << i + 1 << ". " << schools[i]->getname() << "\n";
            }
            cout << "Enter the number of the school: ";
            int schoolIndex;
            cin >> schoolIndex;
            cin.ignore();
            if (schoolIndex > 0 && schoolIndex <= schools.size()) {
                cout << "Available Teachers:\n";
                for (int i = 0; i < teachers.size(); ++i) {
                    cout << i + 1 << ". " << teachers[i]->getName() << "\n";
                }
                cout << "Enter the number of the teacher: ";
                int teacherIndex;
                cin >> teacherIndex;
                cin.ignore();
                if (teacherIndex > 0 && teacherIndex <= teachers.size()) {
                    schools[schoolIndex - 1]->addTeacher(teachers[teacherIndex - 1]);
                    cout << "\nTeacher added to school successfully!\n";
                }
                else {
                    cout << "Invalid teacher number!\n";
                }
            }
            else {
                cout << "Invalid school number!\n";
            }
        }
        break;
    }

    case 0: return;
    default: cout << "Invalid choice!\n";
    }
}