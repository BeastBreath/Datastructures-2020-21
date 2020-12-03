#include<iostream>
#include<cstring>
#include<fstream>
#include "student.h"

//Node stuct
struct node {
  node* next;
  student* data;
  node() {
    next = NULL;
    data = NULL;
  }
  ~node() {
    delete data;
  }
};

//Prototypes
int hashFunction(int ID, int size);
void ADD(int index, node** &hashTable, student* newStudent);
bool rehashCheck(node** &table, int size);
void print(node** &hashTable, int size);
void rehash(node** &hashTable, int &size);
void DELETE(node** &hashTable, int index, int ID);
void printStudent(student* thisStudent);

//Main function
int main () {
  cout << "Welcome to HashTable. Please type ADD, PRINT, DELETE, or QUIT to start" << endl;
  srand(time(NULL));

  //Setting up hashTable
  int size = 101;
  node** hashTable = new node*[size];
  for(int i = 0; i < size; i++) {
    hashTable[i] = NULL;
  }

  //Setting up input file streams
  ifstream firstNameStream;
  firstNameStream.open("firstNameFile.txt");
  ifstream lastNameStream;
  lastNameStream.open("lastNameFile");

  //Setting up other variables
  int randomID = 1;
  bool playingGame = true;

  //Loop for while the game is going
  while(playingGame) {
    cout << "> ";
    char input[50];
    cin.get(input, 49);
    cin.get();

    //If user selects to add students
    if(strcmp(input, "ADD") == 0) {
      cout << "Do you want to add a student manually or randomly? M for manual and R for random: ";
      cin.get(input, 2);
      cin.get();
      //If user selects to add students manully
      if(strcmp(input, "M") == 0) {
	//The next lines get input from the user and put it into a new student
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

	int index = hashFunction(ID, size);
	ADD(index, hashTable, newStudent);
	
	//Check if hashTable needs to be rehashed
	if(rehashCheck(hashTable, index) == true) {
	  rehash(hashTable, size);
	}
      }
      //If user selects to randomly add students
      else if(strcmp(input, "R") == 0) {

	int numberOfStudents;
	cout << "How many students would you like to add?" << endl;
	cin >> numberOfStudents;
	cin.get();

	//Loop to generate as many students as user asked for
	for(int i = 0; i < numberOfStudents; i++) {
	  student* newStudent = new student();
	  int firstNumber = rand()%11;
	  int secondNumber = rand()%11;

	  //The next bunch of lines get the file input for first/last names, and also reset the stream
	  for(int j = 0; j < 11; j++) {
	    if(firstNumber == j) {
	      char firstName[20];
	      firstNameStream >> firstName;
	      newStudent->setFirstName(firstName);
	    }
	    else {
	      char scan[20];
	      firstNameStream >> scan;
	    }
	    if(secondNumber == j) {
	      char lastName[20];
	      lastNameStream >> lastName;
	      newStudent->setLastName(lastName);
	    }
	    else {
	      char scan[20];
	      lastNameStream >> scan;
	    }
	  }
	  
	  firstNameStream.close();
	  firstNameStream.open("firstNameFile.txt");
          lastNameStream.close();
          lastNameStream.open("lastNameFile.txt");
	  newStudent->setStudentID(randomID);
	  newStudent->setGPA((float)(rand() % 400) / (float)(100));
	  ADD(hashFunction(randomID, size), hashTable, newStudent);

	  //Check if needs to be rehashed
	  if(rehashCheck(hashTable, hashFunction(randomID, size)) == true) {
	    cout << "getting rehashed" << endl;
	    rehash(hashTable, size);
	  }
	  randomID++;
	}
      }
    }
    //If user selects print
    else if (strcmp(input, "PRINT") == 0) {
      print(hashTable, size);
    }
    //If user selects delete
    else if(strcmp(input, "DELETE") == 0) {
      //The next lines get the ID from the user, finds the index, and calls the delete function
      int ID;
      cout << "What is the ID of the lucky student getting wiped from the school? ";
      cin >> ID;
      cin.get();
      int index = hashFunction(ID, size);
      DELETE(hashTable, index, ID);
    }
    //If user selects quit
    else if(strcmp(input, "QUIT") == 0) {
      break;
    }
    //If user typed an invalid command
    else{
      cout << "STOP PUTTING COMMANDS THAT DON'T WORK" << endl;
    }
  }
}

//Gets the index for the ID
int hashFunction (int ID, int size) {
  int index = ID%size;
  return index;
}

//Adds a new student to the hash table
void ADD(int index, node** &hashTable, student* newStudent) {
  node* current = hashTable[index];
  node* studentNode =  new node();
  studentNode->next = NULL;
  studentNode->data = newStudent;
  //If there is nothing at that index
  if(current == NULL) {
    hashTable[index] = studentNode;
  }
  //Otherwise, we just put it at the front of the linkedList for that spot
  else {
    studentNode->next = hashTable[index];
    hashTable[index] = studentNode;
  }
}

//Checks if we need to rehash based on what was just put in
bool rehashCheck(node** &hashTable, int index) {
  node* current = hashTable[index];
  int counter = 0;//Counter for how many nodes in one index
  //Goes through all the nodes at one index of the array
  while(current != NULL) {
    current = current->next;
    counter++;
  }
  //if there are less than three nodes, return false otherwise return true
  if (counter < 3) {
    return false;
  }
  return true;
}

//Print function
void print(node** &hashTable, int size) {
  cout << "ID\tGPA\tLast Name, First Name" << endl;
  //Goes through each index of the hashTable
  for (int i = 0; i < size; i++) {
    node* current = hashTable[i];
    //Goes through each node at an index
    while(current != NULL) {
      printStudent(current->data);
      current = current->next;
    }
  }
}

//Prints a specific student
void printStudent(student* thisStudent) {
  cout << thisStudent->getStudentID() << "\t";
  cout << thisStudent->getGPA() << "\t";
  cout << thisStudent->getLastName() << ", ";
  cout << thisStudent->getFirstName() << endl;
}

//Function to rehash
void rehash(node** &hashTable, int &size) {
  int newSize = size * 2;//New size for the table
  node* current;
  node** newHashTable = new node*[newSize];//New hash table
  //Sets everything in the new hashtable to null
  for(int i = 0; i < newSize; i++) {
    newHashTable[i] = NULL;
  }

  //Goes through old hashtable and puts it in new hashTable
  for (int i = 0; i < size; i++) {
    current = hashTable[i];
    //Goes through all nodes in a specific index
    while(current != NULL) {
      ADD(hashFunction(current->data->getStudentID(), newSize), newHashTable, current->data);
      current = current->next;
    }
  }
  hashTable = newHashTable;//changes what the normal hashTable is
  size = newSize;
}

//Delete function
void DELETE(node** &hashTable, int index, int ID) {
  node* current = hashTable[index];
  node* previous = NULL;

  //If no students in that index
  if(current == NULL) {
    cout << "STUDENT NOT FOUND" << endl;
    return;
  }

  //Goes through all the nodes at that index
  while(current != NULL) {
    //If the ID for the student at a node matches then ask the user if they want to delete that student
    if(current->data->getStudentID() == ID) {
      cout << "Are you sure you want to delete this student (Y for yes and N for no):" << endl;
      printStudent(current->data);
    
      char* input = new char[20];
      cin.get(input, 19);
      cin.get();
      //If user confirms getting rid of that student, then delete that student
      if(strcmp(input, "Y") == 0) {
	node*temp = current->next;
	//If it is the first node in the index
	if(previous == NULL) {
	  current->~node();//Calls destructure
	  hashTable[index] = temp;
	}
	//If not the first node in the index
	else {
	  current->~node();
	  previous->next = temp;
	}
	cout << "The student has been removed" << endl;
	return;
      }
    }
    //Change temporary Nodes
    previous = current;
    current = current->next;
  }
}
