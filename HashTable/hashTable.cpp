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
  ~node() {
    //data->~student();
    //delete data;
    //delete next;
  }
};

bool addNode(int index, node** &hashTable, student* newStudent);//Adds node
student* createStudent();//Creates student from user input
student* createStudent(char* file);//Creates student from file
node** rehash(node** &hashTable, int size);
int getIndex(int studentID);
void deleteStudent(node** &hashMap);

int main() {
  int size = 101;
  node** hashTable = new node*[size];
  for (int i = 0; i < size; i++) {
    hashTable[i] = NULL;
  }
}

void deleteStudent(node** &hashTable) {
  int ID;
  cout << "What is ID that you want to search for? ";
  cin >> ID;
  int key = getIndex(ID); 
  if(hashTable[key] == NULL) {
    cout << "ID NOT FOUND" << endl;
    return;
  }
  int counter = 0;
  node* current = hashTable[key];
  while(current->next != NULL) {
    if(current->data->getStudentID() == ID) {
      counter++;
      cout << counter << '\t'<< current->data->getFirstName() << '\t';
      cout << current->data->getLastName() << '\t' << current->data->getStudentID();
      cout << '\t' << current->data->getGPA() << endl;
      }
    current = current->next;
  }
  if(current->data->getStudentID() == ID) {
    counter++;
    cout << counter << '\t'<< current->data->getFirstName() << '\t'; 
    cout << current->data->getLastName() << '\t' << current->data->getStudentID();
    cout << '\t' << current->data->getGPA() << endl;
  }
  
  if(counter == 0) {
    cout << "ID NOT FOUND" << endl;
    return;    
  }

  cout << "Please type the number of the student you would like to delete: ";
  int index;
  cin >> index;

  if(index > counter) {
    cout << "INVALID INPUT. PLEASE TRY AGAIN!";
  }
  
  for (int i = 1; i <= counter; i++)
   if(i == counter) {
      counter++;
      cout << counter << '\t'<< current->data->getFirstName() << '\t';
      cout << current->data->getLastName() << '\t' << current->data->getStudentID();
      cout << '\t' << current->data->getGPA() << endl;
      current = current->next;
    }

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

student* createStudent() {
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

int getIndex(int studentID) {
  int key = 0;
  int powerOfTen = 1;
  for(int i = 0; i < 10; i++) {
    key *= studentID%(powerOfTen);
    powerOfTen *= 10;
  }
  return key;
}

node** rehash(node** &hashTable, int type, int newSize) {

  /*
    First name = 0
    Last name = 1
    ID = 2
    GPA = 3
   */
  
  int oldSize = sizeof(hashTable);
  node** newHashTable = new node*[newSize];
  for(int i = 0; i < newSize; i++) {
    newHashTable[i] = new node();
  }

  
  for (int i = 0; i < oldSize; i++) {
    if(hashTable[i] == NULL) {
      break;
    }
    node* current = hashTable[i];
    bool conflicts = addNode(getIndex(current->data->getStudentID()), newHashTable, current->data);
    if(conflicts) {
      //delete new hashTable
      return rehash(hashTable, type, newSize+oldSize);
    }
    while(current->next != NULL) {
      current = current->next;
      conflicts = addNode(getIndex(current->data->getStudentID()), newHashTable, current->data);
      if (conflicts) {
	//delete hashTable
	return rehash(hashTable, type, newSize+oldSize);
      }
    }
  }
  hashTable = newHashTable;
  //Delete hashtable
  return newHashTable;
}
