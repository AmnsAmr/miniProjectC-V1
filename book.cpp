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
    cout << "Enter Title: ";
    std::getline(cin, Title);

    cout << "Enter Author: ";
    std::getline(cin, Author);

    cout << "Enter Number of Pages: ";
    cin >> Num_page;
    cin.ignore(); // Clear the input buffer

    cout << "Enter Genre: ";
    std::getline(cin, Genre);

    // Assign a unique Book ID
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

void book::manageBookMenu(std::vector<std::shared_ptr<book>>& books, std::vector<std::unique_ptr<Library>>& library, std::vector<std::shared_ptr<school>>& schools) {
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
        else if (schools.empty()) {
            cout << "No school was created to add a book into its library.\n";
        }
        else {
            cout << "Available schools:\n";
            for (size_t i = 0; i < schools.size(); i++) {
                cout << i + 1 << ". " << schools[i]->getname() << "\n";
            }
            cout << "Enter the number of the school that you want to add a book to its library: ";
            int schoolIndex;
            cin >> schoolIndex;
            cin.ignore();
            if (schoolIndex > 0 && schoolIndex <= schools.size()) {
                cout << "Available Books:\n";
                for (size_t i = 0; i < books.size(); ++i) {
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