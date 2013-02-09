#pragma once

#include "Student.h"
#include <vector>
class School_4
{
public:
	School_4(void);
	School_4(int); // second constructor when client hands in the number of students
	~School_4(void);

	// object variables
	int _student_number;

	//*************************
	// !!!!! return type changed
	std::vector<std::shared_ptr<Student> > _student_vector;

	// this line says: "create a vector" of "objects of the type 'std::shared_ptr<Student>' "
	// 'std::shared_ptr<Student>' is a shared pointer to objects of the class "Student"
	// to make this ugly line clearer, one could use in the header
	// typedef std::shared_ptr<Student> student_ptr;
	// this is just an abbrevation, using "student_ptr" instead of "std::shared_ptr<Student>", thus giving 
	// std::vector<student_ptr> _student_vector;

	// object functions
	//*************************
	// !!!!! return type changed
	std::shared_ptr<Student> create_student_pointer(std::string);
	std::vector<std::shared_ptr<Student> > return_student_vector(int);
}
