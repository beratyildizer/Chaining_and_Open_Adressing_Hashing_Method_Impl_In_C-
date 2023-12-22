There is a source and a header file in the project and their names are obs.cpp and obs.h respectively. First of all, these files should be included in the workspace environment. Also, I generated the main file so as to not waste your time. 
You can use this main file after adding obs.cpp and obs.h.
To run program, you can use any C++ compiler, but this compiler must support at least C++ 17 standard.
fillNameBufferFromTx function has been implemented to read names and surnames from txt file. After reading names and surnames, they will be used for generating random student. Firstly, this function should be called before infinitive loop.
randomStudentGenerator functions generates random object which its type is Student class.
There are three different functions for chaining and open addressing methods. These functions have been implemented to insert, find and delete process. These functions can be shown below.
int insert_chaining(std::unique_ptr<Student> p);
Student* find_chaining(Student&);
int delete_chaining(Student& student);
int insert_openAdressing(Student*);
Student* find_openAdressing(Student& student, int selection = 0);
int delete_openAdressing(Student&);
names.txt, surname.txt and primes.txt should be also located in workspace area as these files are used to generate students in fillNameBufferFromTx function.
