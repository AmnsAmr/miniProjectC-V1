#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class teacher;

class assignment {
    string Title;
    string Description;
    int Grade;
    bool isDone;

public:
    assignment(string title = "", string description = "");

    string getTitle();
    string getDescription();
    void markAsDone();

    void setGrade(int grade);
    void affichage();
    void manageAssignmentMenu();

    void input();
    friend class teacher;
};

#endif // ASSIGNMENT_H