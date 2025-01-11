#include "Library.h"
#include <iostream>

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

void Library::borrowBook(const std::string& studentName, const std::string& bookTitle) {
    auto studentIt = std::find_if(students.begin(), students.end(), [&studentName](student& s) {
        return s.getname() == studentName;
        });

    if (studentIt == students.end()) {
        std::cout << "Student \"" << studentName << "\" not found.\n";
        return;
    }

    auto bookIt = std::find_if(books.begin(), books.end(), [&bookTitle](book& b) {
        return b.gettitle() == bookTitle;
        });

    if (bookIt == books.end()) {
        std::cout << "Book \"" << bookTitle << "\" not found in the library.\n";
        return;
    }

    studentIt->getbooklist().push_back(*bookIt);
    bookIt->getborrow_count()++;
    books.erase(bookIt);
    std::cout << "Book \"" << bookTitle << "\" borrowed by \"" << studentName << "\".\n";
}

void Library::addStudent(std::string& name, int age, std::string& address, std::string& grade, std::string& parent_contact) {
    students.emplace_back(name, age, address, grade, parent_contact);
    std::cout << "Student \"" << name << "\" added successfully.\n";
}

void Library::input() {
    int choice = 0;
    while (true) {
        cout << "\nLibrary Menu:\n";
        cout << "1. Add a Book\n";
        cout << "2. Add a Student\n";
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
        case 2: {
            string name, address, grade, parent_contact;
            int age;

            cout << "Enter Student Name: ";
            getline(cin, name);

            cout << "Enter Student Age: ";
            cin >> age;
            cin.ignore(); // Clear the input buffer

            cout << "Enter Student Address: ";
            getline(cin, address);

            cout << "Enter Student Grade: ";
            getline(cin, grade);

            cout << "Enter Parent Contact: ";
            getline(cin, parent_contact);

            addStudent(name, age, address, grade, parent_contact);
            break;
        }
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