#ifndef SCHOOL_H
#define SCHOOL_H

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "Principal.h"
#include "teacher.h"
//#include "Student.h"
#include "Group.h"
#include "Library.h"
#include "globals.h"
#include "student.h"


using namespace std;
class student;
class teacher;
class school {
    string Name;
    principal Principal;
    float budget;
    Library library;
    vector<Group> Groups;
    vector<std::shared_ptr<student>> Students;
    vector<std::shared_ptr<teacher>> Teachers;
    bool hasLibrary = false;

public:
    school(string n = "", principal p = principal(), float b = 0.0, Library c = Library());
    school(string n, principal p, float b);

    string getname();
    principal getpricipal();
    Library& getlibrary();
    vector<std::shared_ptr<student>>& getStudents();

    void setlibrary();
    void addTeacher(std::shared_ptr<teacher> t);
    void addStudent(std::shared_ptr<student> s);
    void addClassroom(Group& c);
    //void manageLibrary();
    void manageSchoolMenu(std::vector<std::shared_ptr<school>>& schools, std::vector<std::shared_ptr<student>>& students, std::vector<std::shared_ptr<book>>& books, std::vector<std::unique_ptr<Library>>& library);

    void manageLibrary(std::vector<std::unique_ptr<Library>>& library, std::vector<std::shared_ptr<student>>& students, std::vector<std::shared_ptr<book>>& books, std::vector<std::shared_ptr<school>>& schools);
    void allocateBudget(float amount);
    void affichage();

    void input(); // Add the input function
};

#endif