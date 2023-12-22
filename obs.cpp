#include "obs.h"


using namespace std;


char names[MAX_NAMES][MAX_NAME_LENGTH];
char surnames[MAX_SURNAME][MAX_NAME_LENGTH];

const char* faculties[9]{"Faculty of Engineering", "Medical Sciences Faculty", "Faculty of Economics and Administrative Sciences",
                            "faculty of Economy", "Faculty of Science", "faculty of Architecture", "Faculty of Health Sciences", "Faculty of fine arts",
                            "Social Sciencies Faculties"};

const char* departments[9][9]{ {"Computer Engineering", "Biomedical Engineering", "Electronic Engineering", "Mechanical Engineering", "Industrial Engineering", "Mechatronics Engineering", "Environment Engineering","Chemical Engineering", "Software Engineering"},
                    {"Biochemistry", "Neurosciencies", "Oncology", "Paediatrics", "Pathalogy", "Medicine", "Psychology","Orthopaedics", "Psychiatry"},
                    {"Public Relations", "Media", "Media Communication", "Communication", "Radio", "Television", "Cinema","Newspaper", "Paper"}, 
                    {"Business", "Economy", "Finance", "Industry", "Economy Management", "Business Communication", "Politics","Trade", "Trade for Abroad"},                
                    {"Physical", "Chemistry", "Mathematic", "Biology", "Electric", "Genetic", "Geometry","Molecular Biology", "Physical Science"}, 
                    {"Building", "Architecture", "Graphic", "Interior Architecture", "Interior Building", "Interior Graphic", "Desing","Design Pattern", "Grafic Dessign"}, 
                    {"Medicine", "Medicine1", "Medicine2", "Medicine3", "Medicine4", "Medicine5", "Medicine6", "Medicene7", "Medicene8"}, 
                    {"Art", "English", "Turkish", "Germany", "History", "Music", "Body Health", "Classic", "Turkish History"},
                    {"Education", "Law", "Sociology", "Development", "Economics", "Music", "Government", "Law Rules", "Training"}, };

int primeNumbers[9];
int primeSayac{ 0 };


unique_ptr<Student> my_hash_array[4001]{};
vector<unique_ptr<Student>> open_adressing(81001);

std::random_device rd;
std::mt19937 gen(rd());

unsigned int Student::m = 4001u;
int openAdressing_hasher::i = 1;
unsigned int openAdressing_hasher::m1 = 81001u;

void fillNameBufferFromTxt(void)
{
    char buffer[MAX_NAME_LENGTH];
    FILE* file;
    int numNames{};

    // Open file
    file = fopen("names.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Read names into array
    while (fgets(buffer, MAX_NAME_LENGTH, file) != NULL && numNames < MAX_NAMES) {
        // Remove newline character
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(names[numNames], buffer);
        numNames++;
    }
    fclose(file);
    numNames = 0;

    file = fopen("surname.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Read names into array
    while (fgets(buffer, MAX_SURNAME_LENGTH, file) != NULL && numNames < MAX_SURNAME) {
        // Remove newline character
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(surnames[numNames], buffer);
        numNames++;
    }
    fclose(file);

    file = fopen("primes.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    int count = 0;

    // Read primes number
    while (count < 9 && fscanf(file, "%d", &primeNumbers[count]) == 1) {
        count++;
    }
    fclose(file);

}
Student* randomStudentGenerator(void)
{
    std::uniform_int_distribution<> distrib(0, 10000);
    int randomIndex_name = distrib(gen) % 3000;
    int randomIndex_surname = distrib(gen) % 3000;
    int department1 = (distrib(gen) % 9);
    int faculty = (distrib(gen) % 9);

    return new Student{ names[randomIndex_name], surnames[randomIndex_surname], ASSIGN_ID((distrib(gen) % 10u) + 12u, faculty, (faculty * 9u) + department1, (distrib(gen) % 899u) + 100u), departments[faculty][department1], faculties[faculty] };

}


int insert_chaining(unique_ptr<Student> p)
{
    if (find_chaining(*p) != nullptr)
        return UNSUCCEED;

    if (!my_hash_array[hasher{}(*p)]) {
        my_hash_array[hasher{}(*p)] = std::move(p);
        return SUCCEED;
    }

    Student* temp{ my_hash_array[hasher{}(*p)].get()};

    while (temp->p) {
        temp = (temp->p).get();
    }
    temp->p = std::move(p);

    return SUCCEED;
}

Student* find_chaining(Student& student)
{
    if (!my_hash_array[hasher{}(student)])
        return nullptr;

    Student* temp = my_hash_array[hasher{}(student)].get();
    
    if (temp == nullptr)
        return nullptr;

    while (student.ID != temp->ID) {
        if (!temp->p)
            return nullptr;
        temp = (temp->p).get();
    }

    return temp;

}


int delete_chaining(Student& student)
{
    if (!find_chaining(student))
        return UNSUCCEED;

    unique_ptr<Student>& temp = my_hash_array[hasher{}(student)];

    while (temp) {
        if ((*temp).ID == student.ID) {
            if ((*temp).p) {
                Student* x = (*temp).p.get();
                temp.reset((*temp).p.release());
                delete x;
            }
            else temp.reset();
            return SUCCEED;
        }
        unique_ptr<Student>& temp1 = temp->p;
        temp.release();
        temp.reset(temp1.get());
        temp1.release();
    }

    return UNSUCCEED;

}


int insert_openAdressing(Student* p)
{
    auto temp = openAdressing_hasher{}(*p);

    if (temp > openAdressing_hasher::m1)
        return UNSUCCEED;

    while ((open_adressing[temp])) {
        if ((open_adressing[temp]->ID == 1u))
            break;
        openAdressing_hasher::i++;

        if (openAdressing_hasher::i > 15) {
            openAdressing_hasher::i = 1u;
            return UNSUCCEED;
        }

        temp = openAdressing_hasher{}(*p);
        if (temp > openAdressing_hasher::m1) {
            openAdressing_hasher::i = 1u;
            return UNSUCCEED;
        }
            
    }
    openAdressing_hasher::i = 1u;
    (open_adressing[temp]).reset(p);
    return SUCCEED;
}

Student* find_openAdressing(Student& student, int selection)
{
    if (selection > 1)
        return nullptr;

    auto temp = openAdressing_hasher{}(student);

    

    if (!open_adressing[temp])
        return nullptr;

    while (open_adressing[temp]->ID != student.ID) {
        openAdressing_hasher::i++;
        temp = openAdressing_hasher{}(student);

        if (!open_adressing[temp]) {
            openAdressing_hasher::i = 1;
            return nullptr;
        }

        if (openAdressing_hasher::i > 15) {
            openAdressing_hasher::i = 1;
            return nullptr;
        }

    }

    openAdressing_hasher::i = 1;

    if (selection) {
        unique_ptr<Student> temp1{ open_adressing[temp].release() };
        open_adressing[temp].reset(new Student{"","",1,"",""});
        return temp1.release();
    }

    return open_adressing[temp].get();
    
}

int delete_openAdressing(Student& student)
{
    unique_ptr<Student> temp{ find_openAdressing(student,1) };

    return temp ? 1 : 0;

}