/*
student cpp file
By: Nividh Singh
Date: 11/04/20
*/

#include <cstring>
#include <iostream>

#include "student.h"

using namespace std;

char* student::getFirstName(){
  return firstName;
}
void student::setFirstName(char* newFirstName) {
  strcpy(firstName, newFirstName);
}
char* student::getLastName(){
  return lastName;
}
void student::setLastName(char* newLastName) {
  strcpy(lastName, newLastName);
}
float student::getGPA() {
  return GPA;
}
void student::setGPA(float newGPA) {
  GPA = newGPA;
}
int student::getStudentID() {
return studentID;
}
void student::setStudentID(int newStudentID) {
  studentID = newStudentID;
}

student::student() {
firstName = new char[100];
  lastName = new char[100];
}
student::student(char* fName, char* lName, float nGPA, int nStudentID) {

firstName = new char[100];
  lastName = new char[100];
  
  strcpy(firstName, fName);
  strcpy(lastName, lName);
  GPA = nGPA;
  studentID = nStudentID;
}

student::student (float nGPA, int nStudentID) {
  
firstName = new char[100];
  lastName = new char[100];
  
  GPA = nGPA;
  studentID = nStudentID;
}
student::~student() {

}
