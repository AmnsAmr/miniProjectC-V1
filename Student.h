#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"
#include "assignment.h"
#include <vector>
#include <memory>
#include <string>
#include "book.h"
#include "Library.h"

class book;
class student : public person {
    string Grade;
    float GPA=0;
    vector<string> Subjects;
    static int Student_ID;
    int Student_id=0;
    string Parent_contact;
    vector<book> Books_borrowed;
    vector<assignment> Assignments;

public:
    student();
    student(string& name, int& age, string& address,string& grade, string& parent_contact);

    vector<book>& getbooklist();

    string getname();
    void getAssignment(assignment hw);
    void displayAssignments();
    void affichage() override;
    void input() override;
    void addrating(string& name, float a);

    void returnbook(Library& library,  string& name);

    friend ostream& operator<<(ostream& COUT,student& student);
};

#endif // STUDENT_H


