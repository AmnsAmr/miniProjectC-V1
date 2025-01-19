#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include <algorithm>
#include "book.h"
#include "Student.h"
#include <memory>
#include <unordered_set>

class Library {
    std::vector<book> books;
    //std::vector<student> students; // Store students in the library
    int Total_capacity;
    int Current_capacity;
    std::unordered_set<student*> studentsBorrowing; // Track students borrowing books, storing raw pointers


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
    bool isInternalStudent(student* student);
    void displayStudentsBorrowing();
    void setStudentsBorrowing(student* student);
    void removeStudentsBorrowing(student* student);
    // modify the function to take a student ptr
    void borrowBook(student* student, const std::string& bookTitle);

    //void addStudent(std::string& name, int age, std::string& address, int& grade, std::string& parent_contact);

    void input(); // Add the input function
    void manageLibraryMenu(std::vector<std::unique_ptr<Library>>& library, std::vector<std::shared_ptr<student>>& students, std::vector<std::shared_ptr<book>>& books, std::vector<std::shared_ptr<school>>& schools);

};

#endif // LIBRARY_H