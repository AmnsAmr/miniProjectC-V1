#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
using std::cout, std::endl, std::string, std::cin;

class person {
protected:
    string Name;
    int Age;
    static int Person_ID;
    int ID = 0;

public:
    person(string n = "", int a = 0);
    person(string name, int age, string address);

    virtual void affichage();
    virtual void input();

    string getName();
    int getAge();
    int getID();

    void setName(string& name);
    void setID(int id);
    virtual ~person() = default; // Add a virtual destructor
};

#endif // PERSON_H