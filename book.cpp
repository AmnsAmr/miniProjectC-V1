#include "book.h"
#include "Student.h"
#include "Library.h"
#include "School.h"
#include <iostream>
int book::Book_ID = 1;
book::book() :Title(""), Author(""), Num_page(0), Genre(""), Rating(0.0f), Borrow_count(0) { Book_id = Book_ID++; };

book::book(string title, string author, int pages, string genre)
    : Title(title), Author(author), Num_page(pages), Genre(genre), Rating(0.0f), Borrow_count(0) {
    Book_id = Book_ID++;
}

float book::getrating() { return Rating; }
string& book::getauthor() { return Author; }
int book::getpages() { return Num_page; }
string book::getgenre() { return Genre; }



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

void book::input() {

    bool validTitle = false;
    while (!validTitle) {
        std::cout << "Enter Title: ";
        std::getline(std::cin, Title);
        if (Title.empty()) {
            std::cout << "Title cannot be empty. Please enter a title.\n";
        }
        else {
            validTitle = true;
        }
    }

    bool validAuthor = false;
    while (!validAuthor) {
        std::cout << "Enter Author: ";
        std::getline(std::cin, Author);
        if (Author.empty()) {
            std::cout << "Author cannot be empty. Please enter an author.\n";
        }
        else {
            validAuthor = true;
        }
    }


    bool validPages = false;
    while (!validPages) {
        try {
            std::cout << "Enter Number of Pages: ";
            std::cin >> Num_page;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error("Invalid input. Please enter a valid integer for the number of pages.");
            }
            validPages = true;
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }


    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bool validGenre = false;
    while (!validGenre) {
        std::cout << "Enter Genre: ";
        std::getline(std::cin, Genre);
        if (Genre.empty()) {
            std::cout << "Genre cannot be empty. Please enter a genre.\n";
        }
        else {
            validGenre = true;
        }
    }
    Book_id = Book_ID++;
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
    cout << "\nBook Menu:\n";
    cout << "1. Create a Book\n";
    cout << "2. Add a Book to this Library\n";
    cout << "3. Display All Books\n";
    cout << "0. Back to Library Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1: {
        auto b = std::make_shared<book>();
        b->input();
        books.push_back(b);
        cout << "\nBook created successfully!\n";
        break;
    }
    case 2: {
        if (books.empty()) {
            cout << "No books available to add to the library.\n";
        }
        else {
            cout << "Available Books:\n";
            for (size_t i = 0; i < books.size(); ++i) {
                cout << i + 1 << ". " << books[i]->gettitle() << "\n";
            }
            cout << "Enter the number of the book to add: ";
            int bookIndex;
            cin >> bookIndex;
            cin.ignore();
            if (bookIndex > 0 && bookIndex <= books.size()) {
                auto bookToAdd = books[bookIndex - 1];
                bool bookExists = false;
                for (const auto& book : library.getBooks()) {
                    if (book->gettitle() == bookToAdd->gettitle()) {
                        bookExists = true;
                        break;
                    }
                }
                if (!bookExists) {
                    library.addBook(books[bookIndex - 1]->gettitle(),
                        books[bookIndex - 1]->getauthor(),
                        books[bookIndex - 1]->getpages(),
                        books[bookIndex - 1]->getgenre());
                    cout << "\nBook added successfully to the library!\n";
                }
                else {
                    cout << "This book already exists in the library.\n";
                }
            }
            else {
                cout << "Invalid book number!\n";
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
            for (size_t i = 0; i < books.size(); ++i) {
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