#include<iostream>
#include <cstring>
#include <fstream>
#include <math.h>

using namespace std;

void buildHeap(int* HEAP, int size);
void swap(int *HEAP, int firstIndex, int secondIndex);
int getParentPosition(int position);
int getLeftPosition(int position);
int getRightPosition(int position);
bool isEnd(int *HEAP, int position, int size);
void maxHeapify(int *HEAP, int position, int size);
void insert(int* HEAP, int &size, int element);
void print(int *HEAP, int size);
int extractElement(int *HEAP, int element, int size);



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
    if(strcmp(input, "ADD") == 0 || strcmp(input, "add") == 0) {
      cout << "How many numbers do you want to add? ";
      int numberOfInputs;
      if(maxSize < (numberOfInputs + size)) {
	cout << "THE HEAP CANNOT STORE THAT MANY NUMBERS" << endl;
      }
      else {
	cin >> numberOfInputs;
	cin.get();
	for (int i = 0; i < numberOfInputs; i++) {
	  cout << "Please type the number you would like to add" << endl;
	  int inputNumber;
	  cin >> inputNumber;
	  cin.get();
	  insert(HEAP, size, inputNumber);
	}
      }
    }
    else if(strcmp(input, "DELETE") == 0 || strcmp(input, "delete") == 0) {
      cout << "What is the element you want to delete? ";
      int delElement;
      cin >> delElement;
      cin.get();
      extractElement(HEAP, delElement, size);
      
    }
    else if(strcmp(input, "PRINT") == 0 || strcmp(input, "print") == 0) {
      print(HEAP, size);
    }
    else if(strcmp(input, "FILE") == 0 || strcmp(input, "file") == 0) {
      int number;
      cout << "What is the file name? " << endl;
      char fileName[100];
      cin.get(fileName, 100);
      cin.get();
      ifstream file;
      file.open(fileName);

      while (file >> number) {
	insert(HEAP, size, number);
      }
      file.close();
    }
    else if(strcmp(input, "QUIT") == 0 || strcmp(input, "quit") == 0) {
      programGoing = false;
    }
    else {
      cout << "INVALID COMMAND" << endl;
    }
  }
}

int getParentPosition(int position) {
  int i = floor(position/2);
  return i;
}

int getLeftPosition(int position) {
  int leftPosition = position * 2;
  return leftPosition;
}

int getRightPosition(int position) {
  int rightPosition = position * 2 + 1;
  return rightPosition;
}

bool isEnd(int *HEAP, int position, int size) {
  int left = getLeftPosition(position);
  int right = getRightPosition(position);
  if(left > size || right > size){
    return true;
  }
  if(HEAP[right] == 0 && HEAP[left] == 0) {
    return true;
  }
  return false; 
}

void buildHeap (int* HEAP, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size - 1; j++) {
      if(HEAP[j] < HEAP[j +  1]) {
	swap(HEAP, j, j+1);
      }
    }
  }
}

void swap(int *HEAP, int firstIndex, int secondIndex) {
  int temp = HEAP[secondIndex];
  HEAP[secondIndex] = HEAP[firstIndex];
  HEAP[firstIndex] = temp;
}

void maxHeapify(int *Heap, int position, int size) {
  /*if(isEnd(Heap, size, position)) {
#ifdef DEBUG
    cout << "First in max Heapify" << endl;
#endif

    return;
  }*/

  if (Heap[position] < Heap[getLeftPosition(position)] ||
      Heap[position] < Heap[getRightPosition(position)]) {

#ifdef DEBUG
    cout << "Second in Max Heapify" << endl;
#endif
    
    
    if (Heap[getLeftPosition(position)] > Heap[getRightPosition(position)]) { 
#ifdef DEBUG
      cout << "Third in Max Heapify" << endl;
#endif
      
      swap(Heap, position, getLeftPosition(position)); 
      maxHeapify(Heap, getLeftPosition(position), size); 
    } 
    else{
#ifdef DEBUG
      cout << "Fourth in Max Heapify" << endl;
#endif
      
      swap(Heap, position, getRightPosition(position)); 
      maxHeapify(Heap, getRightPosition(position), size);
    } 
  }
  
}


void insert(int *HEAP, int &size, int element) {
  size++;
  HEAP[size] = element;
  cout << "SIZE " << size << " element " << element << endl;
  // Traverse up and fix violated property 
  int current = size; 
  while (HEAP[current] > HEAP[getParentPosition(current)]) { 

#ifdef DEBUG_INSERT
    cout << element << endl;
    cout << "Current: " << HEAP[current] << " ";
    cout << "PARENT: " << HEAP[getParentPosition(current)] << " " << endl;
#endif
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

void print(int *HEAP, int size) {
  cout << "DO YOU WANT TO PRINT IN METHOD 1 OR 2? ";
  int input;
  cin >> input;
  cin.get();
  if(input == 1) {
    int index = 1;
    int perRow = 1;
    bool allZero = false;
    while(!allZero) {
      allZero = true;
      for(int i = 0; i < perRow; i++) {
	if(HEAP[index] != 0) {
	  cout << HEAP[index] << '\t';
	  allZero = false;
	}
	else {
	  cout << '\t';
	}
	index++;
      }
      perRow *= 2;
    cout << endl;
    }
  }

  else if(input == 2) {
    bool returnl;
    for (int i = 1; i <= size; i++) { 
      returnl = false;
      if(HEAP[i] != 0) {
	cout << "PARENT: ";
	cout << HEAP[i];
	returnl = true;
      }
      if(HEAP[getLeftPosition(i)] != 0) {
	cout << " LEFT CHILD: ";
	cout << HEAP[getLeftPosition(i)];
	returnl = true;
      }
      if(HEAP[getRightPosition(i)] != 0) {
	cout << " RIGHT CHILD: ";
	cout << HEAP[getRightPosition(i)];
	returnl = true;
      }
      if(returnl) {
	cout << endl;
      }
    }
  }
  else {
    cout << "Invalid input" << endl;
    print(HEAP, size);
    return;
  }
}
  
int extractElement(int *HEAP, int element, int size) {
  int index = -1;
  for(int i = 0; i < size; i++) {
#ifdef DEBUG 
    cout << "ELEMENT: " << element << endl;
    cout << "Heap: " << HEAP[i] << endl;
#endif
    if(HEAP[i] == element) {
      index = i;
    }
  }
  if(index == -1) {
    cout << "Element not found" << endl;
  }
  HEAP[index] = 0;
  maxHeapify(HEAP, index, size);
  return 1;
}
