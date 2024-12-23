#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <random>

#define SUCCEED						1u
#define UNSUCCEED					!SUCCEED

#define MAX_NAME_LENGTH				50
#define MAX_NAMES					3000

#define MAX_SURNAME_LENGTH			50
#define MAX_SURNAME					3000

#define FACULTY_ID(X)				((X) + (9))
#define ASSIGN_ID(YY,FF,DD,NNN)		(((YY) * 10000000) + ((FF) * 100000) + ((DD) * 1000) + (NNN))

#define A							17u
#define B							31u


class Student;
Student* find_openAdressing(Student& student, int selection = 0);

class Student {
	friend Student* randomStudentGenerator(void); 

	friend int insert_chaining(std::unique_ptr<Student> p);
	friend Student* find_chaining(Student&);
	friend int delete_chaining(Student& student);

	friend int insert_openAdressing(Student*);
	friend Student* find_openAdressing(Student& student, int selection);
	friend int delete_openAdressing(Student&);

	std::unique_ptr<Student> p{};
	std::string name{""};
	std::string lastname{""};
	
	std::string department{""};
	std::string faculty{""};

	Student(std::string name_, std::string lastname_, unsigned int ID_, std::string department_, std::string faculty_)
		: name{ name_ }, lastname{ lastname_ }, ID{ ID_ }, department{ department_ }, faculty{ faculty_ } { }

public:
	unsigned int ID{ 0 };
	Student() = default;
	static unsigned int m;
	unsigned int operator*(unsigned int val)
	{
		return (ID % 4001u) * val;
	}

};

class hasher {
public:
	unsigned int operator()(Student& student, unsigned int x = Student::m)
	{
		return (((student * A) + B)) % x;
	}
};

class openAdressing_hasher {
public:
	static int i;
	static unsigned int m1;
	unsigned int operator()(Student& student)
	{
		return (hasher{}(student,m1) + (i * (hasher{}(student,m1)))) % 81001u;
	}
};


void fillNameBufferFromTxt(void);

Student* randomStudentGenerator(void);

int insert_chaining(std::unique_ptr<Student> p);
Student* find_chaining(Student&);
int delete_chaining(Student& student);

int insert_openAdressing(Student*);
//Student* find_openAdressing(Student& student, int selection = 0);
int delete_openAdressing(Student&);
