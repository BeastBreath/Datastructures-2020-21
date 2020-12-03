/*
By: Nividh Singh
Date: 12/2/20
This function uses a hashTable to store students
*/

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
student* createStudent(node** &hashTable, int size);//Creates student from user input
student* createStudent(node** &hashTable, char* firstNameFile, char* lastNameFile, int ID, int size);//Creates student from file
node** rehash(node** &hashTable, int &size);
int getIndex(int studentID);
void deleteStudent(node** &hashTable, int &size);
void searchStudent(node** &hashTable);
bool gamePlay(node** &hashTable, char* firstNameFile, char* lastNameFile, int &size);
void print(node** &hashTable, int size);
void printStudent(student* thisStudent);


int main() {
  srand(time(NULL));
  int size = 101;
  node** hashTable = new node*[size];
  for (int i = 0; i < size; i++) {
    hashTable[i] = NULL;
  }

  ifstream myFirstNameFile("firstNameFile.txt", ifstream::in);
  myFirstNameFile.seekg(0, myFirstNameFile.end);
  int fLength = myFirstNameFile.tellg();
  myFirstNameFile.seekg(0, myFirstNameFile.beg);
  char firstNameFile[fLength];
  myFirstNameFile.read(firstNameFile, fLength);
  
  ifstream myLastNameFile("lastNameFile.txt", ifstream::in);
  myLastNameFile.seekg(0, myLastNameFile.end);
  int lLength = myLastNameFile.tellg();
  myLastNameFile.seekg(0, myLastNameFile.beg);
  char lastNameFile[lLength];
  myLastNameFile.read(lastNameFile, lLength);


  bool playing = true;
  while(playing) {
    playing = gamePlay(hashTable, firstNameFile, lastNameFile, size);
    cout << "going" << endl;
  }
}

bool gamePlay(node** &hashTable, char* firstNameFile, char* lastNameFile, int &size) {
  cout << "> ";
  char* input = new char[20];
  cin.get(input, 20);
  cin.get();
  if (strcmp(input, "ADD") == 0) {
    cout << "Do you want to add a student manually or generate random students? M for manual and R for random: ";
    cin.get(input, 20);
    cin.get();
    if(strcmp(input, "M") == 0) {
      createStudent(hashTable, size);
    }
    else if(input, "R") {
      createStudent(hashTable, firstNameFile, lastNameFile, 1, size);
    }
    else {
      cout << "Invalid command" << endl;
    }
    return true;
  }
  if (strcmp(input, "DELETE") == 0) {
    deleteStudent(hashTable, size);
    return true;
  }
  if (strcmp(input, "SEARCH") == 0) {
    return true;
  }
  if (strcmp(input, "PRINT") == 0) {
    print(hashTable, size);
    return true;
  }
  if (strcmp(input, "QUIT") == 0) {
    return false;
  }
  cout << "NOT A VALID COMMAND. VALID COMMANDS ARE\nADD   DELETE   SEARCH   PRINT   QUIT" << endl;
  return true;
}

void print(node** &hashTable, int size) {
  cout << "ID\tGPA\tName" << endl;
  for (int i = 0; i < size; i++) {
    if(hashTable[i] != NULL) {
      node* current = hashTable[i];
      while(current != NULL) {
	printStudent(current->data);
	current = current->next;
      }
    }
  }
}

void printStudent(student* thisStudent) {
  cout << thisStudent->getStudentID() << "\t";
  cout << thisStudent->getGPA() << "\t";
  cout << thisStudent->getLastName() << ", ";
  cout << thisStudent->getFirstName() << endl;
}

void deleteStudent(node** &hashTable, int &size) {
  int ID;
  cout << "What is ID that you want to search for? ";
  cin >> ID;
  int key = getIndex(ID);
  key = key%size;
  cout << key << endl;
  if(hashTable[key] == NULL) {
    cout << "ID NOT FOUND" << endl;
    return;
  }
  int counter = 0;
  node* current = hashTable[key];
  while(current != NULL) {
    if(current->data->getStudentID() == ID) {
      counter++;
    }
    current = current->next;
  }
  if (counter == 0) {
    cout << "ID NOT FOUND" << endl;
  }
  else if (counter == 1) {
    cout << "Are you sure you want to delete this student?" << endl;
    counter = 0;
    current = hashTable[key];
    while(current != NULL) {
      if(current->data->getStudentID() == ID) {
	counter++;
	cout << "Name: "<< current->data->getFirstName() << ' ';
	cout << current->data->getLastName() << "\nID: " << current->data->getStudentID();
	cout << "\nGPA:" << current->data->getGPA() << endl;
	break;
      }
      current = current->next;
    }
    
  }
  
  counter = 0;
  current = hashTable[key];
  while(current != NULL) {
    if(current->data->getStudentID() == ID) {
      counter++;
      cout << counter << '\t'<< current->data->getFirstName() << '\t';
      cout << current->data->getLastName() << '\t' << current->data->getStudentID();
      cout << '\t' << current->data->getGPA() << endl;
    }
    current = current->next;
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
  current = hashTable[key];
  if(current->next == NULL){
#ifdef DEBUG
    cout << "A" << endl;
#endif
    delete(current);
    current = NULL;
    return;
  }
#ifdef DEBUG
  cout << "B" << endl;
#endif
  for (int i = 1; i <= counter; i++) {
    if(i == counter) {
      //counter++;
      cout << counter << '\t'<< current->data->getFirstName() << '\t';
      cout << current->data->getLastName() << '\t' << current->data->getStudentID();
      cout << '\t' << current->data->getGPA() << endl;
      break;
    }
    current = current->next;
  }
  cin.get();
  cin.clear();
  cin.ignore('\n');
}

bool addNode(int index, node ** &hashTable, student* newStudent) {
#ifdef DEBUG
  cout << "INDEX: " << index << endl;
#endif
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

student* createStudent(node** &hashTable, int size) {
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
  addNode((getIndex(studentID)%size), hashTable, newStudent);
  cin.clear();
  cin.get();
  return newStudent;
}

student* createStudent(node** &hashTable, char* firstNameFile, char* lastNameFile, int ID, int size) {
  student* newStudent = new student();
  newStudent->setStudentID(ID);
  int randomNumber = rand();
  int index = 0;
  int firstNameSize = strlen(firstNameFile);
  index = randomNumber%firstNameSize;
  while(index < firstNameSize && firstNameFile[index] != ',') {
    index++;
  }
  if(index == firstNameSize) {
    index = 0;
  }
  else {
    index++;
  }
  char* firstName = new char[20];
  int counter = 0;
  while(index < firstNameSize && firstNameFile[index] != ',') {
    firstName[counter] = firstNameFile[index];
    counter++;
  }
  firstName[counter] = '\0';

  randomNumber = rand();
  int lastNameSize = strlen(lastNameFile);
  index = randomNumber%firstNameSize;
  while(index < lastNameSize && lastNameFile[index] != ',') {
    index++;
  }
  if(index == lastNameSize) {
    index = 0;
  }
  else {
    index++;
  }
  char* lastName = new char[20];
  counter = 0;
  while(index < lastNameSize && lastNameFile[index] != ',') {
    firstName[counter] = firstNameFile[index];
    counter++;
  }
  firstName[counter] = '\0';
  newStudent->setFirstName(firstName);
  newStudent->setLastName(lastName);




  
}

char* randomName(char* file) {
  //srand(time(NULL));
  int fileSize = strlen(file);
  int index = rand()%fileSize;
  while(file[index] != '\n') {
    index++;
    if (index >= fileSize) {
      index = 0;
      break;
    }
  }
  if(index !=0) {
    index++;
  }
  char* name = new char[15];
  int count = 0;
  while(file[index] != '\n') {
    name[count] = file[index];
    count++;
    index++;
    if(index >= fileSize) {
      return name;
    }
  }
  return name;
}

int getIndex(int studentID) {
  cout << studentID << endl;
  return studentID;
  //srand(studentID);
  //return rand();/*
  /*int key = 1;
  int powerOfTen = 1;
  for(int i = 1; i < 10; i++) {
    if(studentID%powerOfTen != 0) {
      key *= (studentID%(powerOfTen)-studentID%(powerOfTen/10));
    }
    cout << i << " K " << key << endl;
    powerOfTen *= 10;
  }
  cout << "KEY: " << key << endl;
  return key;*/
}

node** rehash(node** &hashTable, int type, int size) {

  /*
    First name = 0
    Last name = 1
    ID = 2
    GPA = 3
   */

  /*
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

void searchStudent(node** &hashTable) {
  cout << "What is the Student ID you want to search for?" << endl;
  int input;
  cin >> input;
  int key = getIndex(input);
  if(hashTable[key] == NULL) {
    cout << "Student Not Found" << endl;
    return;
  }
  int counter = 0;
  node* current;
  while(current != NULL) {
    if(current->data->getStudentID() == input) {
      cout << "Student Information: " << endl;
      cout << "Name: " << current->data->getFirstName() << " " << current->data->getLastName() << endl;
      cout << "ID: " << input << endl;
      cout << "GPA: " << current->data->getGPA() << endl;
      counter++;
    }
    current = current->next;
  }
  if (counter == 0) {
    cout << "Student Not Found" << endl;
  }
  return;
  */
}

