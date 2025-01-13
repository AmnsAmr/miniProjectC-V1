#ifndef SCHOOL_H
#define SCHOOL_H

#include <string>
#include <vector>
#include <iostream>
#include "Principal.h"
#include "Teacher.h"
#include "Student.h"
#include "Group.h"
#include "Library.h"

using namespace std;

class school {
    string Name;
    principal Principal;
    float budget;
    int num_student=0;
    Library library;
    vector<Group> Groups;
    vector<student> students;
    vector<teacher> teachers;
    vector<string> Guidelines;
    bool hasLibrary = false;

public:
    school(string n = "", principal p = principal(), float b = 0.0, Library c = Library());
    school(string n, principal p, float b);

    string getname();
    principal getpricipal();
    Library& getlibrary();

    void addTeacher(teacher& t);
    void addStudent(student& s);
    void addClassroom(Group& c);
    void addGuideline(string& guideline);
    void manageLibrary();

    void allocateBudget(float amount);
    void affichage();

    void input(); // Add the input function
};

#endif