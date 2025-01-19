#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class assignment {
    string Title;
    string Description;
    long long Due_date;
    int Grade;
    bool isDone;

public:
    assignment(string title = "", string description = "", long long duedate = 0);

    string getTitle();
    string getDescription();
    void markAsDone();

    void setGrade(int grade);
    void affichage();
    void manageAssignmentMenu(std::vector<std::shared_ptr<assignment>>& assignments);

    void input(); // Add the input function
};

#endif // ASSIGNMENT_H