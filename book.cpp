#include "book.h"
#include "Student.h"
#include "Library.h"
#include "School.h"
#include <iostream>
int book::Book_ID = 1;
book::book() :Title(""), Author(""), Num_page(0), Genre(""), Rating(0.0f), Borrow_count(0) { };

book::book(string title, string author, int pages, string genre)
    : Title(title), Author(author), Num_page(pages), Genre(genre), Rating(0.0f), Borrow_count(0) {
    Book_id = Book_ID++;
}

float book::getrating() { return Rating; }
string& book::getauthor() { return Author; }
int book::getpages() { return Num_page; }
string book::getgenre() { return Genre; }

void book::settitle(string newTitle) {
    Title = newTitle;
}

// Setter for author
void book::setauthor(string newAuthor) {
    Author = newAuthor;
}

// Display all individual ratings
void book::displayAllRatings() {
    if (Ratings.empty()) {
        cout << "No ratings available.\n";
    }
    else {
        cout << "All Ratings:\n";
        for (float r : Ratings) {
            cout << "- " << r << "\n";
        }
    }
}

// Display borrow history (students)
void book::displayBorrowHistory() {
    if (Borrow_history.empty()) {
        cout << "No borrow history.\n";
    }
    else {
        cout << "Borrow History (" << Borrow_count << " entries):\n";
        for ( auto& student : Borrow_history) {
            student.getName();
        }
    }
}
void book::addborrow_count(int a) { Borrow_count += a; }
int& book::getborrow_count() { return Borrow_count; }
vector<student>& book::getBorrowHistory() { return Borrow_history; }
void book::setBorrowHistory(student& s) {
    Borrow_history.push_back(s);
}

string book::gettitle() { return Title; }
void book::setratings(float a) {
    Ratings.push_back(a);
    averagerating();
}

void book::affichage() {
    cout << "Title: " << Title << "\n"
        << "Author: " << Author << "\n"
        << "Book ID: " << Book_id << "\n"
        << "Number of Pages: " << Num_page << "\n"
        << "Genre: " << Genre << "\n"
        << "Average Rating: " << (Ratings.empty() ? 0.0 : Rating) << "\n"
        << "Times Borrowed: " << Borrow_count << "\n";
}
void book::input(Library& library) {
    std::vector<std::string> validGenres = {
            "Textbooks",
            "Dictionaries",
            "Study Guides",
            "Science",
            "History",
            "Mathematics",
            "Philosophy",
            "Psychology",
            "Business/Economics",
            "Language Learning"
    };

    std::cout << "Enter Title: ";
    std::getline(std::cin, Title);

    std::cout << "Enter Author: ";
    std::getline(std::cin, Author);

    std::cout << "Enter Number of Pages: ";
    while (!(std::cin >> Num_page)) {
        std::cout << "Invalid input. Please enter a valid integer for the number of pages: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(); // Clear the input buffer

    // Genre selection using a number
    std::cout << "Select a genre by number:\n";
    for (size_t i = 0; i < validGenres.size(); ++i) {
        std::cout << i + 1 << ". " << validGenres[i] << "\n";
    }

    int genreChoice;
    while (true) {
        std::cout << "Enter the number of your chosen genre: ";
        if (std::cin >> genreChoice) {
            if (genreChoice >= 1 && genreChoice <= validGenres.size()) {
                Genre = validGenres[genreChoice - 1];
                break; // Exit the loop if a valid choice is made
            }
            else {
                std::cout << "Invalid choice. Please enter a number between 1 and " << validGenres.size() << ".\n";
            }
        }
        else {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    shared_ptr<book> newBook = std::make_shared<book>(Title, Author, Num_page, Genre);

    library.setbooks(newBook);
}


void book::averagerating() {
    if (Ratings.empty()) {
        Rating = 0.0f;
    }
    else {
        float total = 0;
        for (float r : Ratings) {
            total += r;
        }
        Rating = total / Ratings.size();
    }
}

ostream& operator<<(ostream& os, book& b) {
    os << "Title: " << b.Title << "\n"
        << "Author: " << b.Author << "\n"
        << "Book ID: " << b.Book_id << "\n"
        << "Number of Pages: " << b.Num_page << "\n"
        << "Genre: " << b.Genre << "\n"
        << "Average Rating: " << b.Rating << "\n"
        << "Times Borrowed: " << b.Borrow_count << "\n";
    return os;
}

void book::manageBookMenu(std::vector<std::shared_ptr<book>>& books, Library& library, std::vector<std::shared_ptr<school>>& schools) {
    int choice;
    do{
        cout << "\nManage Books Menu:\n"
            << "1. Modify Book Title\n"
            << "2. Modify Book Author\n"
            << "3. View Average Rating\n"
            << "4. View All Ratings\n"
            << "5. View Borrow History\n"
            << "6. affichage\n"
            << "0. Return to Previous Menu\n"
            << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
        case 1: {
            string newTitle;
            cout << "Enter new title: ";
            getline(cin, newTitle);
            this->settitle(newTitle);
            break;
        }
        case 2: {
            string newAuthor;
            cout << "Enter new author: ";
            getline(cin, newAuthor);
            this->setauthor(newAuthor);
            break;
        }
        case 3:
            cout << "Average Rating: " << this->getrating() << "\n";
            break;
        case 4:
            this->displayAllRatings();
            break;
        case 5:
            this->displayBorrowHistory();
            break;
        case 6:
            this->affichage();
            break;
        case 0:
            return;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}