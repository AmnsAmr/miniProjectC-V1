#include "Library.h"
#include <iostream>
#include "School.h"
#include <algorithm>
#include <unordered_set>

Library::Library() : Total_capacity(5), Current_capacity(0) {}
Library::Library(int total_capacity) : Total_capacity(total_capacity), Current_capacity(0) {}

void Library::setbooks(shared_ptr<book> b) { Books.push_back(b); }
vector<std::shared_ptr<book>> Library::getBooks() const { return Books; }

void Library::addBook(const std::string& title, const std::string& author, int pages, const std::string& genre) {
    if (Current_capacity < Total_capacity) {
        Books.emplace_back(std::make_shared<book>(title, author, pages, genre));
        Current_capacity++;
        std::cout << "Book added successfully.\n";
    }
    else {
        std::cout << "Library is at full capacity! Cannot add more books.\n";
    }
}

book Library::getMostBorrowedBook() {
    if (Books.empty()) {
        std::cerr << "The library has no books to track borrow history.\n";
        return book();
    }
    int max_borrow_count = 0;
    book most_borrowed_book = *Books[0];

    for (auto& b : Books) {
        if (b->Borrow_count > max_borrow_count) {
            most_borrowed_book = *b;
            max_borrow_count = b->Borrow_count;
        }
    }
    return most_borrowed_book;
}

void Library::displayHighestRatedBooks(size_t num) {
    if (Books.empty()) {
        std::cout << "The library has no books to display.\n";
        return;
    }
    std::vector<std::shared_ptr<book>> sortedBooks = Books;
    std::sort(sortedBooks.begin(), sortedBooks.end(), [](std::shared_ptr<book> a, std::shared_ptr<book> b) {
        return a->getrating() > b->getrating();
        });
    if (num > sortedBooks.size()) {
        num = sortedBooks.size();
    }
    std::cout << "Top " << num << " Rated Books:\n";
    for (int i = 0; i < num; ++i) {
        std::cout << *sortedBooks[i];
    }
}

std::vector<book> Library::highestRatingBooks(size_t num) {
    std::vector<std::shared_ptr<book>> result = Books;
    std::sort(result.begin(), result.end(), [](std::shared_ptr<book> a, std::shared_ptr<book> b) { return a->Rating > b->Rating; });
    if (result.size() > num) {
        result.resize(num);
    }
    std::vector<book> returnBooks;
    for (const auto& bookPtr : result) {
        returnBooks.push_back(*bookPtr);
    }

    return returnBooks;
}

void Library::removeBook(std::string& name) {
    auto it = std::remove_if(Books.begin(), Books.end(), [&name](std::shared_ptr<book> b) {
        return b->gettitle() == name;
        });

    if (it != Books.end()) {
        Books.erase(it, Books.end());
        Current_capacity--;
        std::cout << "Book \"" << name << "\" removed successfully.\n";
    }
    else {
        std::cout << "Book \"" << name << "\" not found in the library.\n";
    }
}

void Library::searchBook(std::string& keyword) {
    bool found = false;
    for (auto& b : Books) {
        if (b->gettitle().find(keyword) != std::string::npos || b->getauthor().find(keyword) != std::string::npos) {
            std::cout << *b;
            found = true;
        }
    }
    if (!found) {
        std::cout << "No books found with the keyword \"" << keyword << "\".\n";
    }
}

void Library::affichage() {
    if (Books.empty()) {
        std::cout << "The library is empty.\n";
        return;
    }
    std::cout << "Books in the library:\n";
    for (auto& b : Books) {
        std::cout << *b;
    }
}

void Library::addRating(const std::string& bookTitle, float new_rating) {
    for (auto& b : Books) {
        if (b->gettitle() == bookTitle) {
            if (new_rating >= 1 && new_rating <= 5) {
                b->setratings(new_rating);
                b->averagerating();
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
    if (Books.empty()) {
        std::cout << "The library has no books to track borrow history.\n";
        return;
    }
    auto mostBorrowed = *std::max_element(Books.begin(), Books.end(), [](std::shared_ptr<book> a, std::shared_ptr<book> b) {
        return a->getborrow_count() < b->getborrow_count();
        });
    std::cout << "Most Borrowed Book:\n";
    std::cout << *mostBorrowed;
}

void Library::setStudentsBorrowing(student* student) {
    studentsBorrowing.insert(student);
}
void Library::removeStudentsBorrowing(student* student) {
    studentsBorrowing.erase(student);
}
bool Library::isInternalStudent(student* student) {
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
    auto bookIt = std::find_if(Books.begin(), Books.end(), [&bookTitle](std::shared_ptr<book> b) {
        return b->gettitle() == bookTitle;
        });
    if (bookIt == Books.end()) {
        std::cout << "Book \"" << bookTitle << "\" not found in the library.\n";
        return;
    }
    student->getbooklist().push_back(**bookIt);
    (*bookIt)->getborrow_count()++;
    setStudentsBorrowing(student);

    Books.erase(bookIt);

    std::cout << "Book \"" << bookTitle << "\" borrowed by \"" << student->getName() << "\".\n";
}

void Library::input() {
    std::string title, author, genre;
    int pages;

    std::cout << "Enter Book Title: ";
    std::getline(std::cin, title);

    std::cout << "Enter Book Author: ";
    std::getline(std::cin, author);

    bool validInput = false;
    while (!validInput) {
        try {
            std::cout << "Enter Number of Pages: ";
            std::cin >> pages;
            if (std::cin.fail()) {
                std::cin.clear();  // Clear error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Clear input buffer
                throw std::runtime_error("Invalid input. Please enter a valid integer for the number of pages.");
            }

            validInput = true;
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

    // Define the list of valid genres
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

    // Prompt user to select a genre from list.
    bool validGenre = false;
    while (!validGenre) {
        std::cout << "Available Genres:\n";
        for (size_t i = 0; i < validGenres.size(); ++i) {
            std::cout << i + 1 << ". " << validGenres[i] << "\n";
        }
        int genreChoice;
        std::cout << "Select Genre by number: ";
        std::cin >> genreChoice;

        // Validate the user input and that it is a correct integer
        if (std::cin.fail() || genreChoice < 1 || genreChoice > validGenres.size()) {
            std::cout << "Invalid input. Please enter a valid number between 1 and " << validGenres.size() << ".\n";
            std::cin.clear();  // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            genre = validGenres[genreChoice - 1];
            validGenre = true;
        }
    }
    // Create a shared_ptr for the new book before adding it
    std::shared_ptr<book> newBook = std::make_shared<book>(title, author, pages, genre);

    // Add the new book to the global books vector
    books.push_back(newBook);
    addBook(title, author, pages, genre);
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
    cout << "8. Manage Books\n"; // Changed from "Add Books"
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
                book tempBook;
                tempBook.manageBookMenu(books, schools[schoolIndex - 1]->getlibrary(), schools);
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