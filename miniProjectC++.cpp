/*#include "person.h"
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

int main() {
    int choice = 0;
    vector<person*> people; // Store all person objects (including students, teachers, and principals)
    vector<student*> students; // Store student objects
    vector<teacher*> teachers; // Store teacher objects
    vector<principal*> principals; // Store principal objects
    vector<book*> books; // Store book objects
    vector<Group*> groups; // Store Group objects
    vector<assignment*> assignments;
    vector<school*> schools;
    vector<prosecution*> prosecutions;
    Ministry_of_Education* ministry = new Ministry_of_Education();
    Library library; // Create a library object

    while (true) {
        // Display menu
        cout << "\nMenu:\n";
        cout << "1. Create a Person\n";
        cout << "2. Create a Student\n";
        cout << "3. Create a Teacher\n";
        cout << "4. Create a Principal\n";
        cout << "5. Create a Book\n";
        cout << "6. Add a Book to the Library\n";
        cout << "7. Remove a Book from the Library\n";
        cout << "8. Search for a Book in the Library\n";
        cout << "9. Display All Books in the Library\n";
        cout << "10. Borrow a Book from the Library\n";
        cout << "11. Add a Rating to a Book\n";
        cout << "12. Display the Most Borrowed Book\n";
        cout << "13. Display the Highest Rated Books\n";
        cout << "14. Display All Persons\n";
        cout << "15. Display All Students\n";
        cout << "16. Display All Teachers\n";
        cout << "17. Display All Principals\n";
        cout << "18. Display All Books\n";
        cout << "19. Create a Group\n";
        cout << "20. Add a Student to a Group\n";
        cout << "21. Display All Groups\n";
        cout << "22. Create an Assignment\n"; 
        cout << "23. Display All Assignments\n"; 
        cout << "24. Create a School\n";
        cout << "25. Display All Schools\n";
        cout << "26. Manage Library\n";
        cout << "27. Create a Prosecution\n";
        cout << "28. Display All Prosecutions\n";
        cout << "29. Manage Ministry of Education\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the input buffer

        switch (choice) {
        case 1: {
            // Create a Person object
            person* p = new person();
            p->input();
            people.push_back(p); // Add to the vector
            cout << "\nPerson created successfully!\n";
            break;
        }
        case 2: {
            // Create a Student object
            student* s = new student();
            s->input();
            people.push_back(s); // Add to the vector
            students.push_back(s); // Add to the students vector
            cout << "\nStudent created successfully!\n";
            break;
        }
        case 3: {
            // Create a Teacher object
            teacher* t = new teacher();
            t->input();
            people.push_back(t); // Add to the vector
            teachers.push_back(t); // Add to the teachers vector
            cout << "\nTeacher created successfully!\n";
            break;
        }
        case 4: {
            // Create a Principal object
            principal* pr = new principal();
            pr->input();
            people.push_back(pr); // Add to the vector
            principals.push_back(pr); // Add to the principals vector
            cout << "\nPrincipal created successfully!\n";
            break;
        }
        case 5: {
            // Create a Book object
            book* b = new book();
            b->input();
            books.push_back(b); // Add to the vector
            cout << "\nBook created successfully!\n";
            break;
        }
        case 6: {
            // Add a Book to the Library
            if (books.empty()) {
                cout << "No books available to add to the library.\n";
            }
            else {
                cout << "Available Books:\n";
                for (int i = 0; i < books.size(); ++i) {
                    cout << i + 1 << ". " << books[i]->gettitle() << "\n";
                }
                cout << "Enter the number of the book to add: ";
                int bookIndex;
                cin >> bookIndex;
                cin.ignore(); // Clear the input buffer
                if (bookIndex > 0 && bookIndex <= books.size()) {
                    library.addBook(books[bookIndex - 1]->gettitle(),
                        books[bookIndex - 1]->getauthor(),
                        books[bookIndex - 1]->getpages(),
                        books[bookIndex - 1]->getgenre());
                }
                else {
                    cout << "Invalid book number!\n";
                }
            }
            break;
        }
        case 7: {
            // Remove a Book from the Library
            string bookName;
            cout << "Enter the name of the book to remove: ";
            getline(cin, bookName);
            library.removeBook(bookName);
            break;
        }
        case 8: {
            // Search for a Book in the Library
            string keyword;
            cout << "Enter a keyword to search for: ";
            getline(cin, keyword);
            library.searchBook(keyword);
            break;
        }
        case 9: {
            // Display All Books in the Library
            library.affichage();
            break;
        }
        case 10: {
            // Borrow a Book from the Library
            if (students.empty()) {
                cout << "No students available to borrow a book.\n";
            }
            else {
                cout << "Available Students:\n";
                for (int i = 0; i < students.size(); ++i) {
                    cout << i + 1 << ". " << students[i]->getName() << "\n";
                }
                cout << "Enter the number of the student: ";
                int studentIndex;
                cin >> studentIndex;
                cin.ignore(); // Clear the input buffer
                if (studentIndex > 0 && studentIndex <= students.size()) {
                    string bookName;
                    cout << "Enter the name of the book to borrow: ";
                    getline(cin, bookName);
                    library.borrowBook(students[studentIndex - 1]->getName(), bookName);
                }
                else {
                    cout << "Invalid student number!\n";
                }
            }
            break;
        }
        case 11: {
            // Add a Rating to a Book
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
                cin.ignore(); // Clear the input buffer
                if (bookIndex > 0 && bookIndex <= books.size()) {
                    int rating;
                    cout << "Enter a rating (1-5): ";
                    cin >> rating;
                    cin.ignore(); // Clear the input buffer
                    library.addRating(books[bookIndex - 1]->gettitle(), rating);
                }
                else {
                    cout << "Invalid book number!\n";
                }
            }
            break;
        }
        case 12: {
            // Display the Most Borrowed Book
            book mostBorrowed = library.getMostBorrowedBook();
            cout << "Most Borrowed Book:\n";
            cout << mostBorrowed;
            break;
        }
        case 13: {
            // Display the Highest Rated Books
            int num;
            cout << "Enter the number of top-rated books to display: ";
            cin >> num;
            cin.ignore(); // Clear the input buffer
            vector<book> topRatedBooks = library.highestRatingBooks(num);
            cout << "Top " << num << " Rated Books:\n";
            for (auto& b : topRatedBooks) {
                cout << b;
            }
            break;
        }
        case 14: {
            // Display all Person objects
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
        case 15: {
            // Display all Student objects
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
        case 16: {
            // Display all Teacher objects
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
        case 17: {
            // Display all Principal objects
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
        case 18: {
            // Display all Book objects
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
        case 19: {
            // Create a Group object
            Group* g = new Group();
            g->input(); // Call the input function to gather group details
            groups.push_back(g); // Add to the groups vector
            cout << "\nGroup created successfully!\n";
            break;
        }
        case 20: {
            // Add a Student to a Group
            Group::addStudentToGroup(groups, students); // Call the new function
            break;
        }
        case 21: {
            // Display all Group objects
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
        case 22: {
            // Create an Assignment object
            assignment* a = new assignment();
            a->input(); // Call the input function to gather assignment details
            assignments.push_back(a); // Add to the assignments vector
            cout << "\nAssignment created successfully!\n";
            break;
        }
        case 23: {
            // Display all Assignment objects
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
        case 24: {
            // Create a School object
            school* s = new school();
            s->input(); // Call the input function to gather school details
            schools.push_back(s); // Add to the schools vector
            cout << "\nSchool created successfully!\n";
            break;
        }
        case 25: {
            // Display all School objects
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
        case 26: {
            // Manage Library
            library.input(); // Call the input function to manage the library
            break;
        }
        case 27: {
            // Create a Prosecution object
            prosecution* p = new prosecution();
            p->input(); // Call the input function to manage the prosecution
            prosecutions.push_back(p); // Add to the prosecutions vector
            cout << "\nProsecution created successfully!\n";
            break;
        }
        case 28: {
            // Display all Prosecution objects
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
               case 29: {
            // Manage Ministry of Education
            ministry->input(); // Call the input function to manage the ministry
            break;
        }
        case 0: {
            // Exit the program
            cout << "Exiting the program...\n";

            // Free dynamically allocated memory
            for (auto p : people) delete p;
            for (auto s : students) delete s;
            for (auto t : teachers) delete t;
            for (auto pr : principals) delete pr;
            for (auto b : books) delete b;
            for (auto g : groups) delete g;
            for (auto g : assignments) delete g;
            for (auto g : schools) delete g;
            for (auto g : prosecutions) delete g;
            return 0;
        }
        default: {
            cout << "Invalid choice! Please try again.\n";
            break;
        }
        }
    }
    return 0;
}*/