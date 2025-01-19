#include "Library.h"
#include <iostream>
#include "School.h"
#include <algorithm>
#include <unordered_set>

Library::Library() : Total_capacity(2000), Current_capacity(0) {}
Library::Library(int total_capacity) : Total_capacity(total_capacity), Current_capacity(0) {}

void Library::setbooks(book& b) { books.push_back(b); }
vector<book> Library::getBooks() { return books; }

void Library::addBook(const std::string& title, const std::string& author, int pages, const std::string& genre) {
    if (Current_capacity < Total_capacity) {
        books.emplace_back(title, author, pages, genre);
        Current_capacity++;
        std::cout << "Book added successfully.\n";
    }
    else {
        std::cout << "Library is at full capacity! Cannot add more books.\n";
    }
}

book Library::getMostBorrowedBook() {
    if (books.empty()) {
        std::cerr << "The library has no books to track borrow history.\n";
        return book();
    }
    int max_borrow_count = 0;
    book most_borrowed_book = books[0];

    for (auto& b : books) {
        if (b.Borrow_count > max_borrow_count) {
            most_borrowed_book = b;
            max_borrow_count = b.Borrow_count;
        }
    }
    return most_borrowed_book;
}

void Library::displayHighestRatedBooks(size_t num) {
    if (books.empty()) {
        std::cout << "The library has no books to display.\n";
        return;
    }
    std::vector<book> sortedBooks = books;
    std::sort(sortedBooks.begin(), sortedBooks.end(), [](book& a, book& b) {
        return a.getrating() > b.getrating();
        });
    if (num > sortedBooks.size()) {
        num = sortedBooks.size();
    }
    std::cout << "Top " << num << " Rated Books:\n";
    for (int i = 0; i < num; ++i) {
        std::cout << sortedBooks[i];
    }
}

std::vector<book> Library::highestRatingBooks(size_t num) {
    std::vector<book> result = books;
    std::sort(result.begin(), result.end(), [](book& a, book& b) { return a.Rating > b.Rating; });
    if (result.size() > num) {
        result.resize(num);
    }
    return result;
}

void Library::removeBook(std::string& name) {
    auto it = std::remove_if(books.begin(), books.end(), [&name](book& b) {
        return b.gettitle() == name;
        });

    if (it != books.end()) {
        books.erase(it, books.end());
        Current_capacity--;
        std::cout << "Book \"" << name << "\" removed successfully.\n";
    }
    else {
        std::cout << "Book \"" << name << "\" not found in the library.\n";
    }
}

void Library::searchBook(std::string& keyword) {
    bool found = false;
    for (auto& b : books) {
        if (b.gettitle().find(keyword) != std::string::npos || b.getauthor().find(keyword) != std::string::npos) {
            std::cout << b;
            found = true;
        }
    }
    if (!found) {
        std::cout << "No books found with the keyword \"" << keyword << "\".\n";
    }
}

void Library::affichage() {
    if (books.empty()) {
        std::cout << "The library is empty.\n";
        return;
    }
    std::cout << "Books in the library:\n";
    for (auto& b : books) {
        std::cout << b;
    }
}

void Library::addRating(const std::string& bookTitle, float new_rating) {
    for (auto& b : books) {
        if (b.gettitle() == bookTitle) {
            if (new_rating >= 1 && new_rating <= 5) {
                b.setratings(new_rating);
                b.averagerating();
                std::cout << "Rating added successfully.\n";
            }
            else {
                std::cout << "Invalid rating! Please enter a value between 1 and 5.\n";
            }
            return;
        }
    }
    std::cout << "Book \"" << bookTitle << "\" not found in the library.\n";
}

void Library::displayMostBorrowedBook() {
    if (books.empty()) {
        std::cout << "The library has no books to track borrow history.\n";
        return;
    }
    auto mostBorrowed = *std::max_element(books.begin(), books.end(), [](book& a, book& b) {
        return a.getborrow_count() < b.getborrow_count();
        });
    std::cout << "Most Borrowed Book:\n";
    std::cout << mostBorrowed;
}


void Library::setStudentsBorrowing(student* student) {
    studentsBorrowing.insert(student);
}
void Library::removeStudentsBorrowing(student* student) {
    studentsBorrowing.erase(student);
}
bool Library::isInternalStudent( student* student)  {
    if (studentsBorrowing.find(student) != studentsBorrowing.end()) {
        return true;
    }
    return false;
}

void Library::displayStudentsBorrowing() {
    if (studentsBorrowing.empty()) {
        std::cout << "No students have borrowed books from this library.\n";
        return;
    }
    std::cout << "Students currently borrowing books from this library:\n";
    for (const auto& studentPtr : studentsBorrowing) {
        std::cout << "- " << studentPtr->getName() << " (ID: " << studentPtr->getStudentId() << ")\n";
    }
}

// Modified borrowBook function
void Library::borrowBook(student* student, const std::string& bookTitle) {
    if (!student) {
        std::cout << "Invalid student pointer.\n";
        return;
    }

    auto bookIt = std::find_if(books.begin(), books.end(), [&bookTitle](book& b) {
        return b.gettitle() == bookTitle;
        });

    if (bookIt == books.end()) {
        std::cout << "Book \"" << bookTitle << "\" not found in the library.\n";
        return;
    }

    student->getbooklist().push_back(*bookIt);
    bookIt->getborrow_count()++;
    setStudentsBorrowing(student);

    std::cout << "Book \"" << bookTitle << "\" borrowed by \"" << student->getName() << "\".\n";
}
/*
void Library::addStudent(std::string& name, int age, std::string& address, int& grade, std::string& parent_contact) {
    students.emplace_back(name, age, address, grade, parent_contact);
    std::cout << "Student \"" << name << "\" added successfully.\n";
}*/

void Library::input() {
    int choice = 0;
    while (true) {
        cout << "\nLibrary Menu:\n";
        cout << "1. Add a Book\n";
        // cout << "2. Add a Student\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the input buffer

        switch (choice) {
        case 1: {
            string title, author, genre;
            int pages;

            cout << "Enter Book Title: ";
            getline(cin, title);

            cout << "Enter Book Author: ";
            getline(cin, author);

            cout << "Enter Number of Pages: ";
            cin >> pages;
            cin.ignore(); // Clear the input buffer

            cout << "Enter Book Genre: ";
            getline(cin, genre);

            addBook(title, author, pages, genre);
            break;
        }
              /* case 2: {
                   string name, address,  parent_contact;
                   int grade, age;

                   cout << "Enter Student Name: ";
                   getline(cin, name);

                   cout << "Enter Student Age: ";
                   cin >> age;
                   cin.ignore(); // Clear the input buffer

                   cout << "Enter Student Address: ";
                   getline(cin, address);

                   cout << "Enter Student Grade: ";
                   cin >> grade;

                   cout << "Enter Parent Contact: ";
                   getline(cin, parent_contact);

                   addStudent(name, age, address, grade, parent_contact);
                   break;
               }*/
        case 0: {
            return; // Exit the input function
        }
        default: {
            cout << "Invalid choice! Please try again.\n";
            break;
        }
        }
    }
}
void Library::manageLibraryMenu(std::vector<std::unique_ptr<Library>>& library, std::vector<std::shared_ptr<student>>& students, std::vector<std::shared_ptr<book>>& books, std::vector<std::shared_ptr<school>>& schools) {
    int choice;
    cout << "\nLibrary Menu:\n";
    cout << "1. Remove a Book from the Library\n";
    cout << "2. Search for a Book in the Library\n";
    cout << "3. Display All Books in the Library\n";
    cout << "4. Borrow a Book from the Library\n";
    cout << "5. Add a Rating to a Book\n";
    cout << "6. Display the Most Borrowed Book\n";
    cout << "7. Display the Highest Rated Books\n";
    cout << "8. Add Books\n";
    cout << "9. Display all students that borrow a book\n";
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
            for (size_t i = 0; i < schools.size(); i++) {
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
            for (size_t i = 0; i < schools.size(); i++) {
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
            for (size_t i = 0; i < schools.size(); i++) {
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
            for (size_t i = 0; i < schools.size(); i++) {
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
                    for (size_t i = 0; i < students.size(); ++i) {
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
                        schools[schoolIndex - 1]->getlibrary().borrowBook(students[studentIndex - 1].get(), bookName);
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
            for (size_t i = 0; i < schools.size(); i++) {
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
                        for (size_t i = 0; i < books.size(); ++i) {
                            cout << i + 1 << ". " << books[i]->gettitle() << "\n";
                        }
                        cout << "Enter the number of the book to rate: ";
                        int bookIndex;
                        cin >> bookIndex;
                        cin.ignore();
                        if (bookIndex > 0 && bookIndex <= books.size()) {
                            float rating;
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
            for (size_t i = 0; i < schools.size(); i++) {
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
            for (size_t i = 0; i < schools.size(); i++) {
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
            for (size_t i = 0; i < schools.size(); i++) {
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
    case 9: {
        if (schools.empty()) {
            cout << "No school was created.\n";
        }
        else {
            cout << "Available schools:\n";
            for (size_t i = 0; i < schools.size(); i++) {
                cout << i + 1 << ". " << schools[i]->getname() << "\n";
            }
            cout << "Enter the number of the school that you want to Display the list of students that borrowed a book from it's library: ";
            int schoolIndex;
            cin >> schoolIndex;
            cin.ignore();
            if (schoolIndex > 0 && schoolIndex <= schools.size()) {
                schools[schoolIndex - 1]->getlibrary().displayStudentsBorrowing();
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