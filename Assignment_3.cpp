#include "obs.h"
#include <vector>
#include <chrono>
#include <thread>

using namespace std::chrono;

extern std::unique_ptr<Student> my_hash_array[4001];
extern std::vector<std::unique_ptr<Student>> open_adressing;

int a = 0;

Student* my_array_for_chaining[80000]{};
Student* my_array_for_openadressing[80000]{};

int main(){
    fillNameBufferFromTxt();
    
    while (a < 80001) {
        Student* first = randomStudentGenerator();

        auto start = steady_clock::now();
        insert_chaining(std::unique_ptr<Student>{first});
        auto now = steady_clock::now();
        auto elapsed = duration_cast<nanoseconds>(now - start).count();
        std::cout << "\rTime elapsed for inserting in chaining: " << elapsed << " nanoseconds" << "\n";

        auto start1 = steady_clock::now();
        find_chaining(*first);
        auto now1 = steady_clock::now();
        auto elapsed1 = duration_cast<nanoseconds>(now1 - start1).count();
        std::cout << "\rTime elapsed for finding in chaining: " << elapsed1 << " nanoseconds" << "\n";

        auto start2 = steady_clock::now();
        delete_chaining(*first);
        auto now2 = steady_clock::now();
        auto elapsed2 = duration_cast<nanoseconds>(now2 - start2).count();
        std::cout << "\rTime elapsed for finding in chaining: " << elapsed2 << " nanoseconds" << "\n";
       
        ++a;

    
    }
    a = 0;

    while (a < 80001) {
        Student* first = randomStudentGenerator();

        auto start = steady_clock::now();
        insert_openAdressing(first);
        auto now = steady_clock::now();
        auto elapsed = duration_cast<nanoseconds>(now - start).count();
        std::cout << "\rTime elapsed for inserting in openAdressing: " << elapsed << " nanoseconds" << "\n";

        auto start1 = steady_clock::now();
        find_openAdressing(*first);
        auto now1 = steady_clock::now();
        auto elapsed1 = duration_cast<nanoseconds>(now1 - start1).count();
        std::cout << "\rTime elapsed for finding in openAdressing: " << elapsed1 << " nanoseconds" << "\n";

        auto start2 = steady_clock::now();
        delete_openAdressing(*first);
        auto now2 = steady_clock::now();
        auto elapsed2 = duration_cast<nanoseconds>(now2 - start2).count();
        std::cout << "\rTime elapsed for finding in openAdressing: " << elapsed2 << " nanoseconds" << "\n";

        ++a;
        

    }

    a = 0;


    

    return 0;
}

