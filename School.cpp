#include "School.h"


school::school(string n, principal p, Library c) : Name(n), Principal(p), library(c) { hasLibrary = true; }
school::school(string n, principal p) : Name(n), Principal(p) {}

string school::getname() { return Name; }
principal school::getpricipal() { return Principal; }
Library& school::getlibrary() { return library; }
bool school::gethasLibrary() { return hasLibrary; }
vector<std::shared_ptr<student>>& school::getStudents() { return Students; }
vector<std::shared_ptr<Group>>& school::getGroups() { return Groups; }
std::vector<std::shared_ptr<teacher>>& school::getTeachers() {return Teachers;}


void school::setlibrary() {}

void school::addTeacher(std::shared_ptr<teacher> t) { Teachers.push_back(t); }

void school::addStudent(std::shared_ptr<student> s) { Students.push_back(s); }

void school::addClassroom(std::shared_ptr<Group> c) { Groups.push_back(c); }



void school::affichage() {
    cout << "School Details:\n";
    cout << "Name: " << Name << "\n";
    cout << "Principal: ";
    Principal.affichage();

    cout << "Teachers:\n";
    if (Teachers.empty()) {
        cout << "    No teachers in this school yet.\n";
    }
    else {
        for (const auto& teacher : Teachers) {
            cout << "  - " << teacher->getName() << "\n";
        }
    }

    cout << "Students:\n";
    if (Students.empty()) {
        cout << "    No students in this school yet.\n";
    }
    else {
        for (const auto& student : Students) {
            cout << "  - " << student->getName() << "\n";
        }
    }

    cout << "Classrooms:\n";
    if (Groups.empty()) {
        cout << "    No classrooms in this school yet.\n";
    }
    else {
        for (auto& classroom : Groups) {
            cout << "  - ";
            classroom->affichage();
            cout << "\n";
        }
    }

    if (hasLibrary) {
        cout << "Library:\n";
        library.affichage();
    }
    else {
        cout << "No library associated with this school.\n";
    }
    cout << "-----------------\n";
}
void school::manageLibrary(std::vector<std::unique_ptr<Library>>& library, std::vector<std::shared_ptr<student>>& students, std::vector<std::shared_ptr<book>>& books, std::vector<std::shared_ptr<school>>& schools) {
    this->library.manageLibraryMenu(library, students, books, schools);
}
void school::input() {
    cout << "Enter School Name: ";
    getline(cin, Name);

    cout << "Available Principals:\n";
    for (size_t i = 0; i < principals.size(); ++i) {
        cout << i+1 << ": " << principals[i]->getName() << endl;
    }

    cout << "Select a principal : ";
    int index;
    cin >> index;
    cin.ignore();

    if (index < 0 || index-1 >= static_cast<int>(principals.size())) {
        cerr << "Invalid index. Defaulting to index 1.\n";
        index = 1;
    }

    Principal = *principals[index-1]; // Copy the selected principal
    principals.erase(principals.begin()+ index - 1);

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
    auto schoolPtr = std::make_shared<school>(*this);
    schools.push_back(schoolPtr);

}

void school::manageSchoolMenu(std::vector<std::shared_ptr<school>>& schools, std::vector<std::shared_ptr<student>>& students, std::vector<std::shared_ptr<book>>& books, std::vector<std::unique_ptr<Library>>& library) {
    int choice;
    cout << "\nSchool Menu:\n";
    cout << "1. Create a School\n";
    cout << "2. Display All Schools\n";
    cout << "3. Manage School Library\n";
    cout << "4. Add a Student to the school\n";
    cout << "5. Add a Teacher to the school\n";
    cout << "6. Manage Students in this School\n";
    cout << "7. Manage Teachers in this School\n";
    cout << "8. Manage Groups in this School\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1: {
        auto s = std::make_shared<school>();
        s->input();
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
        this->library.manageLibraryMenu(libraries, students, books, schools);
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
            cout << "Available Students:\n";
            for (int i = 0; i < students.size(); ++i) {
                cout << i + 1 << ". " << students[i]->getName() << "\n";
            }
            cout << "Enter the number of the student: ";
            int studentIndex;
            cin >> studentIndex;
            cin.ignore();
            if (studentIndex > 0 && studentIndex <= students.size()) {

                auto studentToAdd = students[studentIndex - 1];
                bool studentExists = false;
                for (const auto& student : this->Students) {
                    if (student == studentToAdd) {
                        studentExists = true;
                        break;
                    }
                }
                if (!studentExists) {
                    this->addStudent(students[studentIndex - 1]);
                    cout << "\nStudent added to school successfully!\n";
                    students[studentIndex - 1]->setAssociatedSchool(this);
                }
                else {
                    cout << "This student is already in this school\n";
                }
            }
            else {
                cout << "Invalid student number!\n";
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
            cout << "Available Teachers:\n";
            for (int i = 0; i < teachers.size(); ++i) {
                cout << i + 1 << ". " << teachers[i]->getName() << "\n";
            }
            cout << "Enter the number of the teacher: ";
            int teacherIndex;
            cin >> teacherIndex;
            cin.ignore();
            if (teacherIndex > 0 && teacherIndex <= teachers.size()) {
                auto teacherToAdd = teachers[teacherIndex - 1];
                bool teacherExists = false;
                for (const auto& teacher : this->Teachers) {
                    if (teacher == teacherToAdd) {
                        teacherExists = true;
                        break;
                    }
                }
                if (!teacherExists) {
                    this->addTeacher(teachers[teacherIndex - 1]);
                    cout << "\nTeacher added to school successfully!\n";
                }
                else {
                    cout << "This teacher is already in this school\n";
                }
            }
            else {
                cout << "Invalid teacher number!\n";
            }
        }
        break;
    }
    case 6: {
        if (Students.empty()) {
            cout << "No students in this school to manage.\n";
        }
        else {
            cout << "Available students in this school:\n";
            for (size_t i = 0; i < Students.size(); ++i) {
                cout << i + 1 << ". " << Students[i]->getName() << "\n";
            }
            cout << "Enter the number of the student to manage: ";
            int studentIndex;
            cin >> studentIndex;
            cin.ignore();
            if (studentIndex > 0 && studentIndex <= Students.size()) {
                Students[studentIndex - 1]->manageStudentMenu(students, people, books, schools, libraries);
            }
            else {
                cout << "Invalid student number.\n";
            }
        }
        break;
    }
    case 7: {
        if (Teachers.empty()) {
            cout << "No teachers in this school to manage.\n";
        }
        else {
            cout << "Available teachers in this school:\n";
            for (size_t i = 0; i < Teachers.size(); ++i) {
                cout << i + 1 << ". " << Teachers[i]->getName() << "\n";
            }
            cout << "Enter the number of the teacher to manage: ";
            int teacherIndex;
            cin >> teacherIndex;
            cin.ignore();
            if (teacherIndex > 0 && teacherIndex <= Teachers.size()) {
                Teachers[teacherIndex - 1]->manageTeacherMenu(teachers, people, students, assignments);
            }
            else {
                cout << "Invalid teacher number.\n";
            }
        }
        break;
    }
    case 8: {
        if (Groups.empty()) {
            cout << "No groups in this school to manage. Creating a new one.\n";
            auto g = std::make_shared<Group>();
            g->input();
            this->addClassroom(g);
            cout << "\nGroup created successfully!\n";
        }
        else {
            cout << "Available groups in this school:\n";
            for (size_t i = 0; i < Groups.size(); ++i) {
                cout << i + 1 << ". " << Groups[i]->getgroup() << "\n";
            }
            cout << "Enter the number of the group to manage: ";
            int groupIndex;
            cin >> groupIndex;
            cin.ignore();
            if (groupIndex > 0 && groupIndex <= Groups.size()) {
                Groups[groupIndex - 1]->manageGroupMenu(groups, shared_from_this());
            }
            else {
                cout << "Invalid group number.\n";
            }
        }

        break;
    }
    case 0: return;
    default: cout << "Invalid choice!\n";
    }
}