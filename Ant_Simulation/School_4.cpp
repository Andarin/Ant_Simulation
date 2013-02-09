#include "School_4.h"

// Not important; only used to create the names
#include <string>
#include <sstream>

School_4::School_4(void)
{
}

School_4::School_4(int student_number)
{
	_student_number = student_number;

	_student_vector = return_student_vector(_student_number);

}

School_4::~School_4(void)
{
}

std::shared_ptr<Student> School_4::create_student_pointer(std::string name) 
{
	auto shared_pointer_to_student = std::make_shared<Student>(name);
	// more or less equivalent to the line above is: 
	//std::shared_ptr<Student> shared_pointer_to_student(new Student(name));
	return shared_pointer_to_student;
}

//*************************
// !!!!! declation types changed
std::vector<std::shared_ptr<Student> > School_4::return_student_vector(int number)
{
	std::vector<std::shared_ptr<Student> > _student_vector_inside_the_function;

	for (int id = 0; id < number; id++) {

		// not important; just to create a name
		std::stringstream sstm;
		sstm << "agnes_" << id;
		std::string name = sstm.str();

		// create object
		std::shared_ptr<Student> new_student_pointer = create_student_pointer(name);
		_student_vector_inside_the_function.push_back(new_student_pointer);
	}

	return _student_vector_inside_the_function;
}
