// miniProjectC++.cpp
#include "person.h"
#include "student.h"
#include "teacher.h"
#include "principal.h"
#include "book.h"
#include "Library.h"
#include "Group.h"
#include "assignment.h"
#include "School.h"
#include "Prosecution.h"
#include "MinistryOfEducation.h"
#include "pch.h"

// Forward declarations
void displayMainMenu();
void managePersonMenu(vector<person*>& people);
void manageStudentMenu(vector<student*>& students, vector<person*>& people, vector<book*>& books, vector<school*>& schools, vector<Library*>& library);
void manageTeacherMenu(vector<teacher*>& teachers, vector<person*>& people, vector<student*>& students, vector<assignment*>& assignments);
void managePrincipalMenu(vector<principal*>& principals, vector<person*>& people);
void manageBookMenu(vector<book*>& books, vector<Library*>& library, vector<school*>& schools);
void manageLibraryMenu(vector<Library*>& library, vector<student*>& students, vector<book*>& books, vector<school*>& schools);
void manageGroupMenu(vector<Group*>& groups, const vector<student*>& students);
void manageAssignmentMenu(vector<assignment*>& assignments);
void manageSchoolMenu(vector<school*>& schools, vector<Library*>& library);
void manageProsecutionMenu(vector<prosecution*>& prosecutions);
void manageMinistryMenu(Ministry_of_Education* ministry);

int main() {
    int choice = 0;
    vector<person*> people;
    vector<student*> students;
    vector<teacher*> teachers;
    vector<principal*> principals;
    vector<book*> books;
    vector<Group*> groups;
    vector<assignment*> assignments;
    vector<school*> schools;
    vector<prosecution*> prosecutions;
    Ministry_of_Education* ministry = new Ministry_of_Education();
    vector<Library*> libraries;


    while (true) {
        displayMainMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: managePersonMenu(people); break;
        case 2: manageStudentMenu(students, people, books, schools, libraries); break;
        case 3: manageTeacherMenu(teachers, people, students, assignments); break;
        case 4: managePrincipalMenu(principals, people); break;
        case 5: manageBookMenu(books, libraries, schools); break;
        case 6: manageLibraryMenu(libraries, students, books, schools); break;
        case 7: manageGroupMenu(groups, students); break;
        case 8: manageAssignmentMenu(assignments); break;
        case 9: manageSchoolMenu(schools, libraries); break;
        case 10: manageProsecutionMenu(prosecutions); break;
        case 11: manageMinistryMenu(ministry); break;
        case 0: {
            cout << "Exiting the program...\n";
            for (auto p : people) delete p;
            for (auto s : students) delete s;
            for (auto t : teachers) delete t;
            for (auto pr : principals) delete pr;
            for (auto b : books) delete b;
            for (auto g : groups) delete g;
            for (auto g : assignments) delete g;
            for (auto g : schools) delete g;
            for (auto g : prosecutions) delete g;
           // delete ministry;
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
    cout << "1. Manage Persons\n";
    cout << "2. Manage Students\n";
    cout << "3. Manage Teachers\n";
    cout << "4. Manage Principals\n";
    cout << "5. Manage Books\n";
    cout << "6. Manage Library\n";
    cout << "7. Manage Groups\n";
    cout << "8. Manage Assignments\n";
    cout << "9. Manage Schools\n";
    cout << "10. Manage Prosecutions\n";
    //cout << "11. Manage Ministry of Education\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

void managePersonMenu(vector<person*>& people) {
    int choice;
    cout << "\nPerson Menu:\n";
    cout << "1. Create a Person\n";
    cout << "2. Display All Persons\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1: {
        person* p = new person();
        p->input();
        people.push_back(p);
        cout << "\nPerson created successfully!\n";
        break;
    }
    case 2: {
        if (people.empty()) {
            cout << "No Person objects created yet!\n";
        }
        else {
            cout << "\nAll Persons:\n";
            for (int i = 0; i < people.size(); ++i) {
                cout << "Person " << i + 1 << ":\n";
                people[i]->affichage();
                cout << "-----------------\n";
            }
        }
        break;
    }
    case 0: return;
    default: cout << "Invalid choice!\n";
    }
}

void manageStudentMenu(vector<student*>& students, vector<person*>& people, vector<book*>& books, vector<school*>& schools, vector<Library*>& library) {
    int choice;
    cout << "\nStudent Menu:\n";
    cout << "1. Create a Student\n";
    cout << "2. Display All Students\n";
    cout << "3. Return a Book\n";
    cout << "4. Add a rating to a book\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1: {
        student* s = new student();
        s->input();
        people.push_back(s);
        students.push_back(s);
        cout << "\nStudent created successfully!\n";
        break;
    }
    case 2: {
        if (students.empty()) {
            cout << "No Student objects created yet!\n";
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
            cout << "Available students:\n";
            for (int i = 0; i < students.size(); i++) {
                cout << i + 1 << ". " << students[i]->getName() << "\n";
            }
            cout << "Enter the number of the student that want to return the book: ";
            int studentIndex;
            cin >> studentIndex;
            cin.ignore();
            if (studentIndex > 0 && studentIndex <= students.size()) {
                if (schools.empty()) {
                    cout << "No school was created.\n";
                }
                else {
                    cout << "Available schools:\n";
                    for (int i = 0; i < schools.size(); i++) {
                        cout << i + 1 << ". " << schools[i]->getname() << "\n";
                    }
                    cout << "Enter the number of the school that the book belongs to : ";
                    int schoolIndex;
                    cin >> schoolIndex;
                    cin.ignore();
                    if (schoolIndex > 0 && schoolIndex <= schools.size()) {
                        if (schools[schoolIndex - 1]->getlibrary().getBooks().empty()) {
                            cout << "No Library was created in this school or the library is empty.\n";
                        }
                        else {
                            string bookName;
                            cout << "Enter the name of the book to return: ";
                            getline(cin, bookName);
                            students[studentIndex - 1]->returnbook(schools[schoolIndex - 1]->getlibrary(), bookName);

                        }
                    }
                    else {
                        cout << "Invalid school number!\n";
                    }
                }
            }
            else {
                cout << "Invalid student number!\n";
            }
        }
        break;
    }
    case 4: {
        if (students.empty()) {
            cout << "No students available to rate books.\n";
        }
        else {
            cout << "Available students:\n";
            for (int i = 0; i < students.size(); i++) {
                cout << i + 1 << ". " << students[i]->getName() << "\n";
            }
            cout << "Enter the number of the student: ";
            int studentIndex;
            cin >> studentIndex;
            cin.ignore();
            if (studentIndex > 0 && studentIndex <= students.size()) {
                if (students[studentIndex - 1]->getbooklist().empty()) {
                    cout << "No books available to rate from the student you selected\n";
                }
                else {
                    cout << "Available books to rate:\n";
                    for (auto& book : students[studentIndex - 1]->getbooklist()) {
                        cout << "- " << book.gettitle() << "\n";
                    }
                    string bookname;
                    float rating;
                    cout << "Enter the name of the book you want to rate : ";
                    getline(cin, bookname);
                    cout << "Enter the rating for this book (1-5) : ";
                    cin >> rating;
                    cin.ignore();
                    students[studentIndex - 1]->addrating(bookname, rating);
                }
            }
            else {
                cout << "Invalid student number!\n";
            }
        }
        break;
    }
    case 0: return;
    default: cout << "Invalid choice!\n";
    }
}

void manageTeacherMenu(vector<teacher*>& teachers, vector<person*>& people, vector<student*>& students, vector<assignment*>& assignments) {
    int choice;
    cout << "\nTeacher Menu:\n";
    cout << "1. Create a Teacher\n";
    cout << "2. Display All Teachers\n";
    cout << "3. Add a Student to a Teacher\n";
    cout << "4. Assign Homework to Students\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1: {
        teacher* t = new teacher();
        t->input();
        people.push_back(t);
        teachers.push_back(t);
        cout << "\nTeacher created successfully!\n";
        break;
    }
    case 2: {
        if (teachers.empty()) {
            cout << "No Teacher objects created yet!\n";
        }
        else {
            cout << "\nAll Teachers:\n";
            for (int i = 0; i < teachers.size(); ++i) {
                cout << "Teacher " << i + 1 << ":\n";
                teachers[i]->affichage();
                cout << "-----------------\n";
            }
        }
        break;
    }
    case 3: {
        if (teachers.empty()) {
            cout << "No teachers available to add students.\n";
        }
        else if (students.empty()) {
            cout << "No students available to add to teachers.\n";
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
                cout << "Available Students:\n";
                for (int i = 0; i < students.size(); ++i) {
                    cout << i + 1 << ". " << students[i]->getName() << "\n";
                }
                cout << "Enter the number of the student: ";
                int studentIndex;
                cin >> studentIndex;
                cin.ignore();
                if (studentIndex > 0 && studentIndex <= students.size()) {
                    teachers[teacherIndex - 1]->addStudent(*students[studentIndex - 1]);
                    cout << "\nStudent added to the teacher successfully!\n";
                }
                else {
                    cout << "Invalid student number!\n";
                }
            }
            else {
                cout << "Invalid teacher number!\n";
            }
        }
        break;
    }
    case 4: {
        if (teachers.empty()) {
            cout << "No teachers available to assign homework.\n";
        }
        else if (assignments.empty()) {
            cout << "No assignment available to assign to a teacher.\n";
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
                cout << "Available Assignments:\n";
                for (int i = 0; i < assignments.size(); ++i) {
                    cout << i + 1 << ". " << assignments[i]->getTitle() << "\n";
                }
                cout << "Enter the number of the Assignment: ";
                int assignmentIndex;
                cin >> assignmentIndex;
                cin.ignore();
                if (assignmentIndex > 0 && assignmentIndex <= assignments.size()) {
                    teachers[teacherIndex - 1]->AssignHomework(*assignments[assignmentIndex - 1]);
                    cout << "\nAssignment created successfully!\n";
                }
                else {
                    cout << "Invalid Assignment number!\n";
                }
            }
            else {
                cout << "Invalid teacher number!\n";
            }
        }
        break;
    }
    case 0: return;
    default: cout << "Invalid choice!\n";
    }
}

void managePrincipalMenu(vector<principal*>& principals, vector<person*>& people) {
    int choice;
    cout << "\nPrincipal Menu:\n";
    cout << "1. Create a Principal\n";
    cout << "2. Display All Principals\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1: {
        principal* pr = new principal();
        pr->input();
        people.push_back(pr);
        principals.push_back(pr);
        cout << "\nPrincipal created successfully!\n";
        break;
    }
    case 2: {
        if (principals.empty()) {
            cout << "No Principal objects created yet!\n";
        }
        else {
            cout << "\nAll Principals:\n";
            for (int i = 0; i < principals.size(); ++i) {
                cout << "Principal " << i + 1 << ":\n";
                principals[i]->affichage();
                cout << "-----------------\n";
            }
        }
        break;
    }
    case 0: return;
    default: cout << "Invalid choice!\n";
    }
}
void manageBookMenu(vector<book*>& books, vector<Library*>& library, vector<school*>& schools) {
    int choice;
    cout << "\nBook Menu:\n";
    cout << "1. Create a Book\n";
    cout << "2. Add a Book to a library\n";
    cout << "3. Display All Books\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1: {
        book* b = new book();
        b->input();
        books.push_back(b);
        cout << "\nBook created successfully!\n";
        break;
    }
    case 2: {
        if (books.empty()) {
            cout << "No books available to add to the library.\n";
        }
        else if (schools.empty()) {
            cout << "No school was created to add a book into its library.\n";
        }
        else {
            cout << "Available schools:\n";
            for (int i = 0; i < schools.size(); i++) {
                cout << i + 1 << ". " << schools[i]->getname() << "\n";
            }
            cout << "Enter the number of the school that you want to add a book to its library: ";
            int schoolIndex;
            cin >> schoolIndex;
            cin.ignore();
            if (schoolIndex > 0 && schoolIndex <= schools.size()) {
                cout << "Available Books:\n";
                for (int i = 0; i < books.size(); ++i) {
                    cout << i + 1 << ". " << books[i]->gettitle() << "\n";
                }
                cout << "Enter the number of the book to add: ";
                int bookIndex;
                cin >> bookIndex;
                cin.ignore();
                if (bookIndex > 0 && bookIndex <= books.size()) {
                    schools[schoolIndex - 1]->getlibrary().addBook(books[bookIndex - 1]->gettitle(),
                        books[bookIndex - 1]->getauthor(),
                        books[bookIndex - 1]->getpages(),
                        books[bookIndex - 1]->getgenre());
                    cout << "\nBook added successfully to the library!\n";
                }
                else {
                    cout << "Invalid book number!\n";
                }
            }
            else {
                cout << "Invalid school number!\n";
            }
        }
        break;
    }
    case 3: {
        if (books.empty()) {
            cout << "No Book objects created yet!\n";
        }
        else {
            cout << "\nAll Books:\n";
            for (int i = 0; i < books.size(); ++i) {
                cout << "Book " << i + 1 << ":\n";
                books[i]->affichage();
                cout << "-----------------\n";
            }
        }
        break;
    }
    case 0: return;
    default: cout << "Invalid choice!\n";
    }
}
static void manageLibraryMenu(vector<Library*>& library, vector<student*>& students, vector<book*>& books, vector<school*>& schools) {
    int choice;
    cout << "\nLibrary Menu:\n";
    cout << "1. Remove a Book from the Library\n";
    cout << "2. Search for a Book in the Library\n";
    cout << "3. Display All Books in the Library\n";
    cout << "4. Borrow a Book from the Library\n";
    cout << "5. Add a Rating to a Book\n";
    cout << "6. Display the Most Borrowed Book\n";
    cout << "7. Display the Highest Rated Books\n";
    cout << "8. Manage Library Books\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();
    switch (choice) {
    case 1: {
        if (schools.empty()) {
            cout << "No school was created.\n";
        }
        else {
            cout << "Available schools:\n";
            for (int i = 0; i < schools.size(); i++) {
                cout << i + 1 << ". " << schools[i]->getname() << "\n";
            }
            cout << "Enter the number of the school that you want to remove a book from it's library : ";
            int schoolIndex;
            cin >> schoolIndex;
            cin.ignore();
            if (schoolIndex > 0 && schoolIndex <= schools.size()) {
                if (schools[schoolIndex - 1]->getlibrary().getBooks().empty()) {
                    cout << "The library is empty\n";
                }
                else {
                    string bookName;
                    cout << "Enter the name of the book to remove: ";
                    getline(cin, bookName);
                    schools[schoolIndex - 1]->getlibrary().removeBook(bookName);
                }
            }
            else {
                cout << "Invalid school number!\n";
            }
        }
        break;
    }
    case 2: {
        if (schools.empty()) {
            cout << "No school was created.\n";
        }
        else {
            cout << "Available schools:\n";
            for (int i = 0; i < schools.size(); i++) {
                cout << i + 1 << ". " << schools[i]->getname() << "\n";
            }
            cout << "Enter the number of the school that you want to search a book from it's library : ";
            int schoolIndex;
            cin >> schoolIndex;
            cin.ignore();
            if (schoolIndex > 0 && schoolIndex <= schools.size()) {
                if (schools[schoolIndex - 1]->getlibrary().getBooks().empty()) {
                    cout << "The library is empty\n";
                }
                else {
                    string keyword;
                    cout << "Enter a keyword to search for: ";
                    getline(cin, keyword);
                    schools[schoolIndex - 1]->getlibrary().searchBook(keyword);
                }
            }
            else {
                cout << "Invalid school number!\n";
            }
        }
        break;
    }
    case 3: {
        if (schools.empty()) {
            cout << "No school was created.\n";
        }
        else {
            cout << "Available schools:\n";
            for (int i = 0; i < schools.size(); i++) {
                cout << i + 1 << ". " << schools[i]->getname() << "\n";
            }
            cout << "Enter the number of the school that you want to Display the books from it's library : ";
            int schoolIndex;
            cin >> schoolIndex;
            cin.ignore();
            if (schoolIndex > 0 && schoolIndex <= schools.size()) {
                if (schools[schoolIndex - 1]->getlibrary().getBooks().empty()) {
                    cout << "The library is empty.\n";
                }
                else {
                    schools[schoolIndex - 1]->getlibrary().affichage();
                }
            }
            else {
                cout << "Invalid school number!\n";
            }
        }
        break;
    }
    case 4: {
        if (students.empty()) {
            cout << "No students available to borrow a book.\n";
        }
        else if (schools.empty()) {
            cout << "No school was created.\n";
        }
        else {
            cout << "Available schools:\n";
            for (int i = 0; i < schools.size(); i++) {
                cout << i + 1 << ". " << schools[i]->getname() << "\n";
            }
            cout << "Enter the number of the school that you want to borrow a book from it's library : ";
            int schoolIndex;
            cin >> schoolIndex;
            cin.ignore();
            if (schoolIndex > 0 && schoolIndex <= schools.size()) {
                if (schools[schoolIndex - 1]->getlibrary().getBooks().empty()) {
                    cout << "The library is empty.\n";
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
                        string bookName;
                        cout << "Enter the name of the book to borrow: ";
                        getline(cin, bookName);
                        schools[schoolIndex - 1]->getlibrary().borrowBook(students[studentIndex - 1]->getName(), bookName);
                    }
                    else {
                        cout << "Invalid student number!\n";
                    }
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
            cout << "No school was created.\n";
        }
        else {
            cout << "Available schools:\n";
            for (int i = 0; i < schools.size(); i++) {
                cout << i + 1 << ". " << schools[i]->getname() << "\n";
            }
            cout << "Enter the number of the school that you want to add a rating to a book: ";
            int schoolIndex;
            cin >> schoolIndex;
            cin.ignore();
            if (schoolIndex > 0 && schoolIndex <= schools.size()) {
                if (schools[schoolIndex - 1]->getlibrary().getBooks().empty()) {
                    cout << "The library is empty\n";
                }
                else {
                    if (books.empty()) {
                        cout << "No books available to rate.\n";
                    }
                    else {
                        cout << "Available Books:\n";
                        for (int i = 0; i < books.size(); ++i) {
                            cout << i + 1 << ". " << books[i]->gettitle() << "\n";
                        }
                        cout << "Enter the number of the book to rate: ";
                        int bookIndex;
                        cin >> bookIndex;
                        cin.ignore();
                        if (bookIndex > 0 && bookIndex <= books.size()) {
                            int rating;
                            cout << "Enter a rating (1-5): ";
                            cin >> rating;
                            cin.ignore();
                            schools[schoolIndex - 1]->getlibrary().addRating(books[bookIndex - 1]->gettitle(), rating);
                        }
                        else {
                            cout << "Invalid book number!\n";
                        }
                    }
                }
            }
            else {
                cout << "Invalid school number!\n";
            }
        }
        break;
    }
    case 6: {
        if (schools.empty()) {
            cout << "No school was created.\n";
        }
        else {
            cout << "Available schools:\n";
            for (int i = 0; i < schools.size(); i++) {
                cout << i + 1 << ". " << schools[i]->getname() << "\n";
            }
            cout << "Enter the number of the school that you want to Display the most borrowed book from it's library: ";
            int schoolIndex;
            cin >> schoolIndex;
            cin.ignore();
            if (schoolIndex > 0 && schoolIndex <= schools.size()) {
                if (schools[schoolIndex - 1]->getlibrary().getBooks().empty()) {
                    cout << "The library is empty\n";
                }
                else {
                    schools[schoolIndex - 1]->getlibrary().displayMostBorrowedBook();
                }
            }
            else {
                cout << "Invalid school number!\n";
            }
        }
        break;
    }
    case 7: {
        if (schools.empty()) {
            cout << "No school was created.\n";
        }
        else {
            cout << "Available schools:\n";
            for (int i = 0; i < schools.size(); i++) {
                cout << i + 1 << ". " << schools[i]->getname() << "\n";
            }
            cout << "Enter the number of the school that you want to Display the highest rated books from it's library: ";
            int schoolIndex;
            cin >> schoolIndex;
            cin.ignore();
            if (schoolIndex > 0 && schoolIndex <= schools.size()) {
                if (schools[schoolIndex - 1]->getlibrary().getBooks().empty()) {
                    cout << "The library is empty\n";
                }
                else {
                    int num;
                    cout << "Enter the number of top-rated books to display: ";
                    cin >> num;
                    cin.ignore();
                    schools[schoolIndex - 1]->getlibrary().displayHighestRatedBooks(num);
                }
            }
            else {
                cout << "Invalid school number!\n";
            }
        }
        break;
    }
    case 8: {
        if (schools.empty()) {
            cout << "No School objects created yet!\n";
        }
        else {
            cout << "Available schools:\n";
            for (int i = 0; i < schools.size(); i++) {
                cout << i + 1 << ". " << schools[i]->getname() << "\n";
            }
            cout << "Enter the number of the school to manage the library: ";
            int schoolIndex;
            cin >> schoolIndex;
            cin.ignore();
            if (schoolIndex > 0 && schoolIndex <= schools.size()) {
                schools[schoolIndex - 1]->getlibrary().input();
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
void manageGroupMenu(vector<Group*>& groups, const vector<student*>& students) {
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
        Group* g = new Group();
        g->input();
        groups.push_back(g);
        cout << "\nGroup created successfully!\n";
        break;
    }
    case 2: {
        Group::addStudentToGroup(groups, students);
        break;
    }
    case 3: {
        if (groups.empty()) {
            cout << "No Group objects created yet!\n";
        }
        else {
            cout << "\nAll Groups:\n";
            for (int i = 0; i < groups.size(); ++i) {
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
void manageAssignmentMenu(vector<assignment*>& assignments) {
    int choice;
    cout << "\nAssignment Menu:\n";
    cout << "1. Create an Assignment\n";
    cout << "2. Display All Assignments\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();
    switch (choice) {
    case 1: {
        assignment* a = new assignment();
        a->input();
        assignments.push_back(a);
        cout << "\nAssignment created successfully!\n";
        break;
    }
    case 2: {
        if (assignments.empty()) {
            cout << "No Assignment objects created yet!\n";
        }
        else {
            cout << "\nAll Assignments:\n";
            for (int i = 0; i < assignments.size(); ++i) {
                cout << "Assignment " << i + 1 << ":\n";
                assignments[i]->affichage();
                cout << "-----------------\n";
            }
        }
        break;
    }
    case 0: return;
    default: cout << "Invalid choice!\n";
    }
}

void manageSchoolMenu(vector<school*>& schools, vector<Library*>& library) {
    int choice;
    cout << "\nSchool Menu:\n";
    cout << "1. Create a School\n";
    cout << "2. Display All Schools\n";
    cout << "3. Manage School Library\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1: {
        school* s = new school();
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
            for (int i = 0; i < schools.size(); ++i) {
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
            for (int i = 0; i < schools.size(); i++) {
                cout << i + 1 << ". " << schools[i]->getname() << "\n";
            }
            cout << "Enter the number of the school to manage the library: ";
            int schoolIndex;
            cin >> schoolIndex;
            cin.ignore();
            if (schoolIndex > 0 && schoolIndex <= schools.size()) {
                schools[schoolIndex - 1]->manageLibrary();
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

void manageProsecutionMenu(vector<prosecution*>& prosecutions) {
    int choice;
    cout << "\nProsecution Menu:\n";
    cout << "1. Create a Prosecution\n";
    cout << "2. Display All Prosecutions\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1: {
        prosecution* p = new prosecution();
        p->input();
        prosecutions.push_back(p);
        cout << "\nProsecution created successfully!\n";
        break;
    }
    case 2: {
        if (prosecutions.empty()) {
            cout << "No Prosecution objects created yet!\n";
        }
        else {
            cout << "\nAll Prosecutions:\n";
            for (int i = 0; i < prosecutions.size(); ++i) {
                cout << "Prosecution " << i + 1 << ":\n";
                prosecutions[i]->affichage();
                cout << "-----------------\n";
            }
        }
        break;
    }
    case 0: return;
    default: cout << "Invalid choice!\n";
    }
}
static void manageMinistryMenu(Ministry_of_Education* ministry) {
    int choice;
    cout << "\nMinistry of Education Menu:\n";
    cout << "1. Create Ministry\n";
    cout << "2. Display Ministry Details\n";
    cout << "3. Allocate budget to a school\n";
    cout << "4. Publish Guidelines\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1: {
        ministry->input();
        break;
    }
    case 2: {
        if (ministry->getName().empty()) {
            cout << "No Ministry object created yet!\n";
        }
        else {
            cout << "\nMinistry Details:\n";
            ministry->affichage();
        }
        break;
    }
    case 3: {
        if (ministry->getName().empty()) {
            cout << "No Ministry object created yet!\n";
        }
        else {
            if (getSchools().empty()) {
                cout << "No school was created to allocate budget.\n";
            }
            else {
                cout << "Available schools:\n";
                for (int i = 0; i < getSchools().size(); i++) {
                    cout << i + 1 << ". " << schools[i]->getname() << "\n";
                }
                cout << "Enter the number of the school: ";
                int schoolIndex;
                cin >> schoolIndex;
                cin.ignore();

                if (schoolIndex > 0 && schoolIndex <= getSchools().size()) {
                    float budgetAmount;
                    cout << "Enter the amount you want to allocate to the school : ";
                    cin >> budgetAmount;
                    cin.ignore();
                    ministry->AllocateBudgetToSchool(schools[schoolIndex - 1], budgetAmount);
                }
                else {
                    cout << "Invalid school number!\n";
                }
            }
        }
        break;
    }
    case 4: {
        if (ministry->getName().empty()) {
            cout << "No Ministry object created yet!\n";
        }
        else {
            string guideline;
            cout << "Enter the Guideline to Publish : ";
            getline(cin, guideline);
            ministry->PublishGuidelines(guideline);
        }
        break;
    }
    case 0: return;
    default:
        cout << "Invalid choice!\n";
    }
}