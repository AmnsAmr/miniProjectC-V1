#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include <vector>


using std::cout, std::endl, std::string, std::vector, std::ostream;
class student;
class book {
    string Title;
    string Author;
    static int Book_ID;
    int Book_id;
    int Num_page;
    string Genre;
    vector<student> Borrow_history;
    vector<float> Ratings;
    float Rating;
    int Borrow_count;

public:
    book();
    book(string title, string author, int pages, string genre);

    float getrating();
    string& getauthor();
    int getpages();
    string getgenre();
    int& getborrow_count();
    vector<student>& getBorrowHistory();
    void setBorrowHistory(student& s);

    string gettitle();
    void setratings(float a);

    void affichage();
    void input();
    void averagerating();

    friend class Library;
    friend ostream& operator<<(ostream& os,book& b);
};

#endif
