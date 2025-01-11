#include "book.h"
#include "Student.h"
int book::Book_ID = 1;
book::book() {};

book::book(string title, string author, int pages, string genre)
    : Title(title), Author(author), Num_page(pages), Genre(genre),Rating(0.0f), Borrow_count(0) {}

float book::getrating() { return Rating; }
string& book::getauthor() { return Author; }
int book::getpages() { return Num_page; }
string book::getgenre() { return Genre; }



int& book::getborrow_count() { return Borrow_count; }
vector<student>& book::getBorrowHistory() { return Borrow_history; }
void book::setBorrowHistory(student& s) {
    Borrow_history.push_back(s);
}

string book::gettitle() { return Title;}
void book::setratings(float a) { Ratings.push_back(a);
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
