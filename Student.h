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
class school;
class student : public person {
    int Grade=1;
    float GPA = 0;
    vector<string> Subjects;
    static int Student_ID;
    int Student_id = 0;
    vector<book> Books_borrowed;
    vector<std::shared_ptr<assignment>> Assignments;
    school* associatedSchool = nullptr;

public:
    student();
    student(string& name, int& age, string& address, int& grade, string& parent_contact);

    vector<book>& getbooklist();
    int getGrade();
    string getname();
    int getStudentId();
    school* getAssociatedSchool();

    void setAssociatedSchool(school* school);
    void setGrade(int& grade);
    void setStudentId(int id);

    void setAssignment(std::shared_ptr<assignment> hw);
    void displayAssignments();
    void affichage() override;
    void input() override;
    void addrating(const std::string& bookTitle, float rating);

    void returnbook(Library& library, const std::string& bookTitle);

    void manageStudentMenu(std::vector<std::shared_ptr<student>>& students, std::vector<std::shared_ptr<person>>& people, std::vector<std::shared_ptr<book>>& books, std::vector<std::shared_ptr<school>>& schools, std::vector<std::unique_ptr<Library>>& library);

    friend ostream& operator<<(ostream& COUT, student& student);
};

#endif // STUDENT_H