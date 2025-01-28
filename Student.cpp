#include"Student.h"
#include "book.h"
#include "School.h"
using namespace std;

int student::Student_ID = 1;

student::student() { Grade = 1; }
student::student(string& name, int& age, string& address, int& grade, string& parent_contact)
    : person(name, age, address),
    Grade(grade),
    Student_id(Student_ID++){
}

vector<book>& student::getbooklist() { return Books_borrowed; }
int student::getGrade() { return Grade; }
string student::getname() { return Name; }
int student::getStudentId() { return Student_id; }
school* student::getAssociatedSchool() { return associatedSchool; }

void student::setGrade(int& grade) { Grade = grade; }
void student::setStudentId(int id) { Student_id = id; }
void student::setAssignment(std::shared_ptr<assignment> hw) { Assignments.push_back(hw); } //Shared ptr
void student::setAssociatedSchool(school* school) { associatedSchool = school; }

void student::displayAssignments() {
    for (auto& assgn : Assignments) {
        assgn->affichage();
    }
}

void student::affichage() {
    person::affichage();
    cout << "Student ID: " << Student_id << "\n";
    cout << "Grade: " << Grade << "\n";
    cout << "GPA: " << GPA << "\n";
    cout << "Subjects: ";
    for (auto& subject : Subjects) {
        cout << subject << " ";
    }
    cout << "\nBooks Borrowed: " << Books_borrowed.size() << "\n";
    cout << "Assignments: " << Assignments.size() << "\n";
}

void student::input() {
    person::input();

    bool validInput = false;
    while (!validInput) {
        try {
            std::cout << "Enter Grade: ";
            std::cin >> Grade;
            if (std::cin.fail()) {
                std::cin.clear();  // Clear error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Clear input buffer
                throw std::runtime_error("Invalid input. Please enter a valid integer for the grade.");
            }
            validInput = true;
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    Student_id = Student_ID++;
}


void student::addrating(const std::string& bookTitle, float rating) {
    bool bookFound = false;
    for (auto& book : Books_borrowed) {
        if (book.gettitle() == bookTitle) {
            book.setratings(rating);
            bookFound = true;
        }
    }
    if (!bookFound) {
        std::cout << "Book \"" << bookTitle << "\" not found in the list of borrowed books.\n";
    }
}
void student::returnbook(Library& library, const std::string& bookTitle) {
    for (auto bookIt = Books_borrowed.begin(); bookIt != Books_borrowed.end(); ++bookIt) {
        if (bookIt->gettitle() == bookTitle) {
            library.setbooks(std::make_shared<book>(*bookIt));
            Books_borrowed.erase(bookIt);
            std::cout << "Book \"" << bookTitle << "\" returned successfully.\n";
            return;
        }
    }

    std::cout << "Book \"" << bookTitle << "\" not found in the student's list.\n";
}

ostream& operator<<(ostream& COUT, student& student) {
    COUT << "Name: " << student.getName() << "\n"
        << "ID: " << student.getID() << "\n"
        << "Student ID: " << student.Student_id << "\n"
        << "Grade: " << student.Grade << "\n"
        << "GPA: " << student.GPA << "\n"
        << "Subjects: ";
    for (auto& subject : student.Subjects) {
        COUT << subject << " ";
    }
    COUT << "\nBooks Borrowed: " << student.Books_borrowed.size() << "\n"
        << "Assignments: " << student.Assignments.size() << "\n";
    return COUT;
}

void student::manageStudentMenu(std::vector<std::shared_ptr<student>>& students, std::vector<std::shared_ptr<person>>& people, std::vector<std::shared_ptr<book>>& books, std::vector<std::shared_ptr<school>>& schools, std::vector<std::unique_ptr<Library>>& library) {
    int choice;
    cout << "\nStudent Menu:\n";
    cout << "1. Create a Student\n";
    cout << "2. Display All Students\n";
    cout << "3. Return a Book\n";
    cout << "4. Add a rating to a book\n";
    cout << "5. Associate the student with a school\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1: {
        std::shared_ptr<student> s = std::make_shared<student>();
        s->input();
        people.push_back(s);
        students.push_back(s);
        cout << "\nStudent created successfully!\n";
        break;
    }
    case 2: {
        if (students.empty()) {
            cout << "No Students created yet!\n";
        }
        else {
            cout << "\nAll Students:\n";
            for (int i = 0; i < students.size(); ++i) {
                cout << "Student " << i + 1 << ":\n";
                students[i]->affichage();
                cout << "-----------------\n";
            }
        }
        break;
    }
    case 3: {
        if (students.empty()) {
            cout << "No students available to return books.\n";
        }
        else {
            if (this->associatedSchool == nullptr) {
                cout << "The student does not have a school yet.\n";
            }
            else if (this->associatedSchool->getlibrary().getBooks().empty())
            {
                cout << "No Library was created in this school or the library is empty.\n";
            }
            else
            {
                if (this->Books_borrowed.empty())
                {
                    cout << "The student has no books to return.\n";
                }
                else
                {
                    string bookName;
                    cout << "Enter the name of the book to return: ";
                    getline(cin, bookName);
                    this->returnbook(this->associatedSchool->getlibrary(), bookName);
                }
            }
        }
        break;
    }
    case 4: {
        if (students.empty()) {
            cout << "No students available to rate books.\n";
        }
        else {
            if (this->getbooklist().empty()) {
                cout << "No books available to rate from the student you selected\n";
            }
            else {
                cout << "Available books to rate:\n";
                for (book& book : this->Books_borrowed) {
                    cout << "- " << book.gettitle() << "\n";
                }
                string bookname;
                float rating;
                cout << "Enter the name of the book you want to rate : ";
                getline(cin, bookname);
                cout << "Enter the rating for this book (1-5) : ";
                cin >> rating;
                cin.ignore();
                this->addrating(bookname, rating);
            }

        }
        break;
    }
    case 5: {
        if (schools.empty()) {
            cout << "No schools to choose from, create a school first.\n";
        }
        else {
            cout << "Available schools:\n";
            for (int i = 0; i < schools.size(); i++) {
                cout << i + 1 << ". " << schools[i]->getname() << "\n";
            }
            cout << "Enter the number of the school: ";
            int schoolIndex;
            cin >> schoolIndex;
            cin.ignore();
            if (schoolIndex > 0 && schoolIndex <= schools.size()) {

                // Check if the student is already associated with a school
                if (this->associatedSchool != nullptr) {
                    // Remove student from the previous school list
                    auto& currentSchoolStudents = this->associatedSchool->getStudents();
                    auto it = std::remove_if(currentSchoolStudents.begin(), currentSchoolStudents.end(),
                        [this](const std::shared_ptr<student>& s) {return s.get() == this; });
                    currentSchoolStudents.erase(it, currentSchoolStudents.end());
                }


                // Set the new school association
                this->setAssociatedSchool(schools[schoolIndex - 1].get());
                schools[schoolIndex - 1]->addStudent(shared_from_this());// Add to the school's student list
                cout << "The student is now associated with school: " << schools[schoolIndex - 1]->getname() << "\n";
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