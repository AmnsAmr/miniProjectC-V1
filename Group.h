#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include <string>
#include "student.h"
#include "teacher.h"
#include <memory>

class school; // Forward declaration
class Group {
    std::string group;
    int roomnumber;
    int capacity = 5;
    std::vector<std::shared_ptr<student>> students;
    std::vector<std::shared_ptr<teacher>> Teachers;


public:
    Group();
    Group(std::string g, int rn, std::vector<std::shared_ptr<teacher>> t);

    std::string getgroup();

    void addStudent(std::shared_ptr<student> s);
    void addTeacher(std::shared_ptr<teacher> t);

    void input();
    void affichage();
    void manageGroupMenu(std::vector<std::shared_ptr<Group>>& groups, std::shared_ptr<school> currentSchool);


};

#endif