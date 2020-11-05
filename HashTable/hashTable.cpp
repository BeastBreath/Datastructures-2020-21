#include <iostream>
#include <cstring>
#include <fstream>

#include "student.h"

using namespace std;

struct node {
  node* next;
  student* data;
  node() {
    next = NULL;
    data = NULL;
  }
  node(student* newData) {
    data = newData;
    next = NULL;
  }
  node(student* newData, node* newNext) {
    next = newNext;
     data = newData;
  }
  node(node* newNext) {
    next = newNext;
  }
};

bool addNode(int index, node** &hashTable, student* newStudent);//Adds node
student* createStudent();//Creates student from user input
student* createStudent(char* file);//Creates student from file
node** rehash(node** &hashTable);

int main() {
  int size = 101;
  node** byID = new node*[size];
  node** byFirstName = new node*[size];
  node** byLastName = new node*[size];
  node** byGPA = new node*[size];
  for (int i = 0; i < size; i++) {
    byID[i] = NULL;
    byFirstName[i] = NULL;
    byLastName[i] = NULL;
    byGPA[i] = NULL;
  }

}

bool addNode(int index, node ** &hashTable, student* newStudent) {
  node* newNode = new node(newStudent);
  if(hashTable[index] = NULL) {
    hashTable[index] = newNode;
    return false;
  }
  else {
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
    int count = 0;
    node* current = hashTable[index];
    while(current->next != NULL) {
      count ++;
      current = current->next;
    }
    if(count > 3) {
      return false;
    }
    return true;
  }
}

student* creatStudent() {
  student* newStudent = new student();
  char* firstName = new char[20];
  char* lastName = new char[20];
  int studentID;
  float studentGPA;
  cout << "What is the first name? ";
  cin >> firstName;
  newStudent->setFirstName(firstName);
  cout << "What is the last name? ";
  cin >> lastName;
  newStudent->setLastName(lastName);
  cout << "What is the studentID? ";
  cin >> studentID;
  newStudent->setStudentID(studentID);
  cout << "What is the GPA? ";
  cin >> studentGPA;
  newStudent->setGPA(studentGPA);
  return newStudent;
}
