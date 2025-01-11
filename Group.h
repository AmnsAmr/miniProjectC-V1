#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include <string>
#include "student.h"
#include "teacher.h"

class Group {
    std::string group;
    int roomnumber;
    int capacity = 5;
    std::vector<student> students;
    std::vector<teacher> Teachers;

public:
    Group();
    Group(std::string g, int rn, std::vector<teacher> t);

    void addStudent(student& s);
    void input();
    void affichage();

    // New function to add a student to a group
    static void addStudentToGroup(std::vector<Group*>& groups, const std::vector<student*>& students);
};

#endif // GROUP_H