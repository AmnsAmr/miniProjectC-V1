#ifndef PROSECUTION_H
#define PROSECUTION_H

#include <vector>
#include <string>
#include <memory>
#include "School.h"

class prosecution {
    vector<string> Guidelines;
    vector<std::shared_ptr<school>> schools;

public:
    prosecution();
    prosecution(vector<string>& guidelines, vector<std::shared_ptr<school>>& schoolsList);

    vector<std::shared_ptr<school>>& getSchools();
    void addGuideline(string& guideline);
    void addSchool(std::shared_ptr<school> s);

    void affichage();
    void manageProsecutionMenu(std::vector<std::shared_ptr<prosecution>>& prosecutions);


    void input(); // Add the input function

    friend class Ministry_of_Education;
};

#endif