/*

Made By Nividh Singh
Max heap for numbers
Date: 12/2/20
Use -D DEBUG when compiling if you want to see debug messages
*/

#include<iostream>
#include <cstring>
#include <fstream>
#include <math.h>

using namespace std;

//Function Prototypes
void swap(int *HEAP, int firstIndex, int secondIndex);
int getParentPosition(int position);
int getLeftPosition(int position);
int getRightPosition(int position);
bool isEnd(int *HEAP, int position, int size);
void maxHeapify(int *HEAP, int position, int size);
void insert(int* HEAP, int &size, int element);
void print(int *HEAP, int size);
void extractElement(int *HEAP, int element, int size);

//Main function
int main() {
  cout << "Welcome to heap. Please type ADD, FILE, DELETE, PRINT, QUIT to get started" << endl;

  //creating array for heap
  int size = 1;
  int maxSize = 301;
  int HEAP[maxSize];
  for (int i = 0; i < maxSize; i++) {
    HEAP[i] = 0;
  }

#ifdef DEBUG
  insert(HEAP, size, 5);
  insert(HEAP, size, 1);
  insert(HEAP, size, 4);
  insert(HEAP, size, 52);
  insert(HEAP, size, 7);
  insert(HEAP, size, 6);
  insert(HEAP, size, 6);
  insert(HEAP, size, 512);
  insert(HEAP, size, 4);
  print(HEAP, size);
#endif
  
  bool programGoing = true;
  
  //loop for game
  while(programGoing) {
    cout << "> ";
    //Gets input from the user
    char input[20];
    cin.get(input, 20);
    cin.get();
    //If user says add, ask how many people and add those many people
    if(strcmp(input, "ADD") == 0 || strcmp(input, "add") == 0) {
      cout << "How many numbers do you want to add? ";
      int numberOfInputs;
      //If too many numbers, give an error message
      if(maxSize < (numberOfInputs + size)) {
	cout << "THE HEAP CANNOT STORE THAT MANY NUMBERS" << endl;
      }
      //Otherwise, start getting and adding inputs
      else {
	cin >> numberOfInputs;
	cin.get();
	//Loop to get the number of inputs from the user
	for (int i = 0; i < numberOfInputs; i++) {
	  cout << "Please type the number you would like to add" << endl;
	  int inputNumber;
	  cin >> inputNumber;
	  cin.get();
	  insert(HEAP, size, inputNumber);
	}
      }
    }
    //If the user says delete
    else if(strcmp(input, "DELETE") == 0 || strcmp(input, "delete") == 0) {
      //Get the number person wants to delete
      cout << "What is the number you want to delete? ";
      int delElement;
      cin >> delElement;
      cin.get();
      extractElement(HEAP, delElement, size);
      
    }
    //If user says pring
    else if(strcmp(input, "PRINT") == 0 || strcmp(input, "print") == 0) {
      print(HEAP, size);
    }
    //If user wants file input 
    else if(strcmp(input, "FILE") == 0 || strcmp(input, "file") == 0) {
      int number;
      cout << "What is the file name? " << endl;
      char fileName[100];
      cin.get(fileName, 100);
      cin.get();
      //Sets up file
      ifstream file;
      file.open(fileName);
      //Goes through the file and inserts everything into the heap
      while (file >> number) {
	insert(HEAP, size, number);
      }
      file.close();
    }
    //If user wants to quit
    else if(strcmp(input, "QUIT") == 0 || strcmp(input, "quit") == 0) {
      int constSize = size;
      for (int i = 0; i < constSize - 1; i++) {
	cout << HEAP[1] << ' ';
	extractElement(HEAP, HEAP[1], size);
	size--;
	
      }
      programGoing = false;
    }
    //If user types an invalid command
    else {
      cout << "INVALID COMMAND" << endl;
    }
  }
}

//Returns parent position
int getParentPosition(int position) {
  int i = floor(position/2);
  return i;
}

//Returns left child position
int getLeftPosition(int position) {
  int leftPosition = position * 2;
  return leftPosition;
}

//Returns right child position
int getRightPosition(int position) {
  int rightPosition = position * 2 + 1;
  return rightPosition;
}

//Checks if the node is a end, meaning no more nodes after
bool isEnd(int *HEAP, int position, int size) {
  int left = getLeftPosition(position);
  int right = getRightPosition(position);
  //Checks if the left and right children are small enough to fit in the heap
  if(left > size || right > size){
    return true;
  }
  //Also checks if the child nodes are both zero
  if(HEAP[right] == 0 && HEAP[left] == 0) {
    return true;
  }
  return false; 
}

//Swaps two indexs of the heap
void swap(int *HEAP, int firstIndex, int secondIndex) {
  int temp = HEAP[secondIndex];
  HEAP[secondIndex] = HEAP[firstIndex];
  HEAP[firstIndex] = temp;
}

//This justs pulls child nodes up if a node is deleted, using recurssion
void maxHeapify(int *Heap, int position, int size) {

  //If either of the two child nodes are bigger, we pull them up
  if (Heap[position] < Heap[getLeftPosition(position)] ||
      Heap[position] < Heap[getRightPosition(position)]) {

#ifdef DEBUG
    cout << "Second in Max Heapify" << endl;
#endif
    
    //If the left is bigger than the right child, the left takes the spot of the parent node
    if (Heap[getLeftPosition(position)] > Heap[getRightPosition(position)]) { 
#ifdef DEBUG
      cout << "Third in Max Heapify" << endl;
#endif
      
      swap(Heap, position, getLeftPosition(position)); 
      maxHeapify(Heap, getLeftPosition(position), size); 
    }
    //Otherwise, the right takes the place of the parent node
    else{
#ifdef DEBUG
      cout << "Fourth in Max Heapify" << endl;
#endif
      swap(Heap, position, getRightPosition(position)); 
      maxHeapify(Heap, getRightPosition(position), size);
    } 
  }
}

//Inserts something into the heap
void insert(int *HEAP, int &size, int element) {
  size++;
  HEAP[size] = element;//Inserts it into the end
  int current = size; 
  //Loop keeps going while the number we inputed is bigger than the number at the parent node position
  while (HEAP[current] > HEAP[getParentPosition(current)]) { 
#ifdef DEBUG_INSERT
    cout << element << endl;
    cout << "Current: " << HEAP[current] << " ";
    cout << "PARENT: " << HEAP[getParentPosition(current)] << " " << endl;
#endif
    //If the parent position is zero, we break and don't continue
    if(getParentPosition(current) == 0){
      break;
    }
    swap(HEAP, current, getParentPosition(current)); 
#ifdef DEBUG_INSERT
    cout << element << endl;
    cout << "Current: " << HEAP[current] << " ";
    cout << "PARENT: " << HEAP[getParentPosition(current)] << " " << endl;
#endif
    current = getParentPosition(current);
  }
}

//Prints the heap
void print(int *HEAP, int size) {
  //There are two methods, one resembles more of a tree, and the other is just a bunch of information
  cout << "DO YOU WANT TO PRINT IN METHOD 1 OR 2? ";
  int input;
  cin >> input;
  cin.get();
  //If user picks the first method of displaying data, we just go through the array one by one and print stuff out
  if(input == 1) {
    int index = 1;//Variable for which index we are at
    int perRow = 1;//Variable for how many numers are supposed to be in a row
    bool allZero = false;//Variable to keep track of if all the numbers at a certain level are zeros, and then we stop printing
    //Goes until we have all zeros
    while(!allZero) {
      allZero = true;
      //Goes through the row amount and prints out that many numbers
      for(int i = 0; i < perRow; i++) {
	//If number is not zero, we print it
	if(HEAP[index] != 0) {
	  cout << HEAP[index] << '\t';
	  allZero = false;
	}
	//Otherwise we just tab
	else {
	  cout << '\t';
	}
	index++;//Increases index
      }
      perRow *= 2;//Increases how many per row
      cout << endl;
    }
  }

  //If user selects the other method of input
  else if(input == 2) {
    bool returnl;
    //Loop for going through the array
    for (int i = 1; i <= size; i++) { 
      returnl = false;
      //If number isn't zero, we print it
      if(HEAP[i] != 0) {
	cout << "PARENT: ";
	cout << HEAP[i];
	returnl = true;
      }
      //If left child isn't zero, we print it
      if(HEAP[getLeftPosition(i)] != 0) {
	cout << " LEFT CHILD: ";
	cout << HEAP[getLeftPosition(i)];
	returnl = true;
      }
      //If right child isn't zero, we print it
      if(HEAP[getRightPosition(i)] != 0) {
	cout << " RIGHT CHILD: ";
	cout << HEAP[getRightPosition(i)];
	returnl = true;
      }
      //If the parent was there, we make a new line (So if the parent wasn't a zero)
      if(returnl) {
	cout << endl;
      }
    }
  }
  //If the user types something other than 1 or 2, error message
  else {
    cout << "Invalid input" << endl;
    print(HEAP, size);
    return;
  }
}

//Cool way of saying delete an element
void extractElement(int *HEAP, int element, int size) {
  int index = -1;
  //Goes through each spot to find where the element is
  for(int i = 0; i < size; i++) {
#ifdef DEBUG 
    cout << "ELEMENT: " << element << endl;
    cout << "Heap: " << HEAP[i] << endl;
#endif
    //IF we found the element, we keep track of the index
    if(HEAP[i] == element) {
      index = i;
    }
  }
  //If we didn't find the element, error message
  if(index == -1) {
    cout << "Element not found" << endl;
  }
  //We just delete the element and let maxHeapify clean up our mess (maxHeapify is sponsered by max encorperations)
  HEAP[index] = 0;
  maxHeapify(HEAP, index, size);
}
