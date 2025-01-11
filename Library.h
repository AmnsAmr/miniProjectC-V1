#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include <algorithm>
#include "book.h"
#include "Student.h"

class Library {
    std::vector<book> books;
    std::vector<student> students; // Store students in the library
    int Total_capacity;
    int Current_capacity;

public:
    Library();
    Library(int total_capacity);

    book getMostBorrowedBook();
    void displayHighestRatedBooks(size_t num);
    std::vector<book> highestRatingBooks(size_t num);

    void setbooks(book& b);
    std::vector<book> getBooks();
    void addBook(const std::string& title, const std::string& author, int pages, const std::string& genre);
    void removeBook(std::string& name);
    void searchBook(std::string& keyword);
    void affichage();
    void addRating(const std::string& bookTitle, float new_rating);
    void displayMostBorrowedBook();

    void borrowBook(const std::string& studentName, const std::string& bookTitle);
    void addStudent(std::string& name, int age, std::string& address, std::string& grade, std::string& parent_contact);

    void input(); // Add the input function
};

#endif // LIBRARY_H