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
    assignment(const assignment& other);
    string getTitle();
    string getDescription();
    void markAsDone();
    bool getifdone();
    int getGrade();

    void addNameToTitle(string a);
    void setGrade(int grade);
    void affichage();
    void manageAssignmentMenu();
    std::string getLastWord();
    void input();
    friend class teacher;
};

#endif // ASSIGNMENT_H