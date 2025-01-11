#ifndef PROSECUTION_H
#define PROSECUTION_H

#include <vector>
#include <string>
#include "School.h"

class prosecution {
    vector<string> Guidelines;
    vector<school> schools;

public:
    prosecution();
    prosecution(vector<string>& guidelines , vector<school>& schoolsList);

    vector<school>& getSchools();
    void addGuideline(string& guideline);
    void addSchool(school& s);

    void affichage();

    void input(); // Add the input function

    friend class Ministry_of_Education;
};

#endif