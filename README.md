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
