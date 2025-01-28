#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include <memory>
#include "person.h"
#include "student.h"
#include "teacher.h"
#include "principal.h"
#include "book.h"
#include "group.h"
#include "assignment.h"
#include "school.h"
//#include "Prosecution.h"
#include "library.h"
class prosecution;

extern std::vector<std::shared_ptr<person>> people;
extern std::vector<std::shared_ptr<student>> students;
extern std::vector<std::shared_ptr<teacher>> teachers;
extern std::vector<std::shared_ptr<principal>> principals;
extern std::vector<std::shared_ptr<book>> books;
extern std::vector<std::shared_ptr<Group>> groups;
extern std::vector<std::shared_ptr<assignment>> assignments;
extern std::vector<std::shared_ptr<school>> schools;
extern std::vector<std::shared_ptr<prosecution>> prosecutions;
extern std::vector<std::unique_ptr<Library>> libraries;

#endif
