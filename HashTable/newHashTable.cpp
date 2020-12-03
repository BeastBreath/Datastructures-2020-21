#include<iostream>
#include<cstring>
#include<fstream>
#include "student.h"
//#include "node.h"

struct node {
  node* next;
  student* data;
  node() {
    next = NULL;
    data = NULL;
  }
};

int hashFunction(int ID, int size);
void ADD(int index, node** &hashTable, student* newStudent);
bool rehashCheck(node** &table, int size);
void print(node** &hashTable, int size);
void rehash(node** &hashTable, int &size);
void DELETE(node** &hashTable, int index, int ID);
void printStudent(student* thisStudent);


int main () {
  cout << "START" << endl;
  srand(time(NULL));
  
  int size = 101;
  node** hashTable = new node*[size];
  for(int i = 0; i < size; i++) {
    hashTable[i] = NULL;
  }

  ifstream firstNameStream;
  firstNameStream.open("firstNameFile.txt");
  ifstream lastNameStream;
  lastNameStream.open("lastNameFile");

  int randomID = 1;
  bool playingGame = true;
  
  while(playingGame) {
    cout << "> ";
    char input[50];
    cin.get(input, 49);
    cin.get();

    if(strcmp(input, "ADD") == 0) {
      cout << "Do you want to add a student manually or generate random students? M for manual and R for random:";
      cin.get(input, 2);
      cin.get();
      if(strcmp(input, "M") == 0) {
	student* newStudent = new student();
	cout << "First Name: ";
	char* firstName = new char[51];
	cin.get(firstName, 50);
	cin.get();
	newStudent->setFirstName(firstName);

	cout << "Last Name: ";
	char* lastName = new char[51];
	cin.get(lastName, 50);
	cin.get();
	newStudent->setLastName(lastName);

	int ID;
	cout << "Student ID: ";
	cin >> ID;
	cin.get();
	newStudent->setStudentID(ID);

	float GPA;
	cout << "Student GPA: ";
	cin >> GPA;
	cin.get();
	newStudent->setGPA(GPA);

	//cout << "S" << endl;
	
	int index = hashFunction(ID, size);
	ADD(index, hashTable, newStudent);

	//cout << "DSFSD" << endl;
	
	if(rehashCheck(hashTable, index) == true) {
	  cout << "getting rehashed" << endl;
	  rehash(hashTable, size);
	}
	cout << "S" << endl;
      }
      else if(strcmp(input, "R") == 0) {
	/*int numberOfStudents;
	cout << "How many students would you like to add?" << endl;
	cin >> numberOfStudents;
	cin.get();

	for(int i = 0; i < numberOfStudents; i++) {
	  student* newStudent = new Student();
	  int randomNumber = rand();
	  
	}
	*/
	
      }
      

    }

    else if (strcmp(input, "PRINT") == 0) {
      cout << "A" << endl;
      print(hashTable, size);
    }

    else if(strcmp(input, "DELETE") == 0) {
      int ID;
      cout << "What is the ID of the lucky student getting wiped from the school? ";
      cin >> ID;
      cin.get();
      int index = hashFunction(ID, size);
      DELETE(hashTable, index, ID);
    }
    else if(strcmp(input, "QUIT") == 0) {
      break;
    }
    else{
      cout << "STOP PUTTING COMMANDS THAT DON'T WORK" << endl;
    }
  }
  
  
}


int hashFunction (int ID, int size) {
  int index = ID%size;
  return index;
}

void ADD(int index, node** &hashTable, student* newStudent) {
  node* current = hashTable[index];
  node* studentNode =  new node();
  studentNode->next = NULL;
  studentNode->data = newStudent;
  if(current == NULL) {
    hashTable[index] = studentNode;
  }

  else {
    studentNode->next = hashTable[index];
    hashTable[index] = studentNode;
    

    /*
    while(current->next != NULL) {
      current = current->next;
    }
    current->next = studentNode;*/
  }
  cout << "Success" << index << endl;
}


bool rehashCheck(node** &hashTable, int index) {
  node* current = hashTable[index];
  int counter = 0;
  while(current != NULL) {
    cout << "asdfsdf" << endl;
    current = current->next;
    counter++;
    cout << "1S" << endl;
  }
  cout << "S" << endl;
  if (counter < 3) {
    return false;
  }
  return true;

}


void print(node** &hashTable, int size) {
  cout << "S" << endl;
  for (int i = 0; i < size; i++) {
    cout << "I: " << i << endl;
    node* current = hashTable[i];
    while(current != NULL) {
      cout << "SDF" << endl;
      printStudent(current->data);
      current = current->next;
    }
  }
}


void printStudent(student* thisStudent) {
  cout << thisStudent->getStudentID() << "\t";
  cout << thisStudent->getGPA() << "\t";
  cout << thisStudent->getLastName() << ", ";
  cout << thisStudent->getFirstName() << endl;
}

void rehash(node** &hashTable, int &size) {
  int newSize = size * 2;
  node* current;
  node** newHashTable = new node*[newSize];
  for(int i = 0; i < newSize; i++) {
    newHashTable[i] = NULL;
  }

  for (int i = 0; i < size; i++) {
    current = hashTable[i];
    while(current != NULL) {
      ADD(hashFunction(current->data->getStudentID(), newSize), newHashTable, current->data);
      current = current->next;
    }
  }

  hashTable = newHashTable;
  size = newSize;
}

void DELETE(node** &hashTable, int index, int ID) {

  node* current = hashTable[index];
  node* previous = NULL;
  
  if(current == NULL) {
    cout << "INDEX: " << index << endl;
    cout << "NO STUDENTS IN THIS INDEX" << endl;
    cout << "STUDENT NOT FOUND" << endl;
    return;
  }
  
  while(current->next != NULL) {
    if(current->data->getStudentID() == ID) {
      cout << "Are you sure you want to delete this student (Y for yes and N for no):" << endl;
      printStudent(current->data);
    }
    char* input = new char[20];
    cin.get(input, 19);
    cin.get();
    if(strcmp(input, "Y") == 0) {
      node*temp = current->next;
      if(previous == NULL) {
	current->~node();
	hashTable[index] = temp;
      }
      else {
	current->~node();
	previous->next = temp;
      }
      cout << "The student has been removed" << endl;
    }
  }
}
