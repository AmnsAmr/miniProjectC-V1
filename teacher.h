#ifndef TEACHER_H
#define TEACHER_H

#include "person.h"
#include "student.h"
#include "assignment.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class teacher : public person {
    float salary;
    string subject;
    int experience;
    bool isFullTime;
    vector<student> students;

public:
    // Constructor
    teacher(string name = "", int age = 0, string address = "",float sal = 0.0f, string sub = "", int exp = 0, bool fullTime = false);

    // Display teacher details
    void affichage() override; // Override base class function

    // Input teacher details
    void input() override; // Override base class function

    // Add student
    void addStudent(student student);

    // Assign homework to all students
    void AssignHomework(assignment& homework);

    // Friend function for ostream
    friend ostream& operator<<(ostream& COUT, teacher& teacher);
};

#endif // TEACHER_H