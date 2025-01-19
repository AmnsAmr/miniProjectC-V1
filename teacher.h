#ifndef TEACHER_H
#define TEACHER_H

#include "person.h"
#include "student.h"
#include "assignment.h"
#include <vector>
#include <string>
#include <memory>
#include <iostream>
using namespace std;

class teacher : public person {
    float salary;
    string subject;
    vector<std::shared_ptr<student>> students; //Shared pointer for students
    vector<std::shared_ptr<assignment>> Assignments; //Shared pointer for assignments

public:
    // Constructor
  
    teacher(string name = "", int age = 0, string address = "", float sal = 0.0f, string sub = "", int exp = 0, bool fullTime = false);

    // Display teacher details
    void affichage() override; // Override base class function

    // Input teacher details
    void input() override; // Override base class function

    // Add student
    void addStudent(std::shared_ptr<student> stud); // Shared pointer student

    // Assign homework to all students
    void AssignHomework(std::shared_ptr<assignment> homework); // Shared pointer assignment

    // Friend function for ostream
    friend ostream& operator<<(ostream& COUT, teacher& teacher);

    void manageTeacherMenu(vector<std::shared_ptr<teacher>>& teachers, vector<std::shared_ptr<person>>& people, vector<std::shared_ptr<student>>& students, vector<std::shared_ptr<assignment>>& assignments);
};

#endif // TEACHER_H