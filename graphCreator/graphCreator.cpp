/*
Made by Nividh Singh
Date: 12/16/20

Just creates a simple graph using user input

*/


#include <string.h>
#include <iostream>
#include <limits>

using namespace std;

#define SIZE 20

//struct for the vertex (just has a name)
struct vertex {
  char* name;
  vertex(char* newName) {
    name = newName;
  }
};

//Struct for items (for dijkstra's algorithm
struct item {
  bool visited;
  vertex* vert;
  int value;
  item() {
    visited = false;
    vert = NULL;
    value = numeric_limits<int>::max();
  }
  item(vertex* newVert) {
    visited = false;
    vert = newVert;
    value = numeric_limits<int>::max();
  }
};

//Function Prototypes
void addVertex(vertex** vertexList);
void addEdge(vertex** vertexList, int** adjacencyTable);
void deleteVertex(vertex** vertexList, int** adjacencyTable);
void deleteEdge(vertex** vertexList, int** adjacencyTable);
int getIndex(char* name, vertex** vertexList);
void print(vertex** vertexList, int** adjacencyTable);
int callDijkstra(vertex** vertexList, int** adjacencyTable);
int Dijkstra(item** itemList, int** adjacencyTable, int endIndex);

//Main method
int main() {

  cout << "Welcome to graph creator. Type help for help with commands" << endl;

  //Creating adjacency table and vertex list and intializing them
  int* adjacencyTable[SIZE];
  vertex* vertexList[SIZE];
  for(int i = 0; i < SIZE; i++) {
    adjacencyTable[i] = new int[SIZE];
    for(int j = 0; j < SIZE; j++) {
      adjacencyTable[i][j] = -1;
    }
    vertexList[i] = NULL;
  }

  
  char input[20];
  //Loop for if we are going
  while(true) {
    cout << "> ";
    cin.get(input, 20);
    cin.get();

    if(strcmp("ADD VERTEX", input) == 0) {
      addVertex(vertexList);
    }
    else if(strcmp("ADD EDGE", input) == 0) {
      addEdge(vertexList, adjacencyTable);
    }
    else if(strcmp("DELETE VERTEX", input) == 0) {
      deleteVertex(vertexList, adjacencyTable);
    }
    else if(strcmp("DELETE EDGE", input) == 0) {
      deleteEdge(vertexList, adjacencyTable);
    }
    else if(strcmp("PRINT", input) == 0) {
      print(vertexList, adjacencyTable);
    }
    else if(strcmp("PATH", input) == 0) {
      int length = callDijkstra(vertexList, adjacencyTable);
      if(length != -1) {
	cout << "The shortest path is: " << length << endl;
      }
    }
    else if(strcmp("HELP", input) == 0) {
      cout << "Here are your commands: " << endl;
      cout << "'ADD VERTEX' - ADDS A VERTEX" << endl;
      cout << "'ADD EDGE' - ADDS AN EDGE" << endl;
      cout << "'DELETE VERTEX' - DELETES A VERTEX" << endl;
      cout << "'DELETE EDGE' - DELETES AN EDGE" << endl;
      cout << "'PATH' - FINDS THE SHORTEST PATH" << endl;
      cout << "'HELP' - PRINTS ALL COMMANDS" << endl;
      cout << "'QUIT' - ENDS PROGRAM" << endl;
    }
    else if(strcmp("QUIT", input) == 0) {
      break;
    }
    else {
      cout << "Invalid command" << endl;
    }
  }
}

//This function calls the dijkstra algorithm
int callDijkstra(vertex** vertexList, int** adjacencyTable)  {
  //We get the user input about where to start and end in the next few lines
  cout << "What is the name of the node you want to start at? ";
  char input[20];
  cin.get(input, 20);
  cin.get();
  int startIndex = getIndex(input, vertexList);
  if(startIndex == -1) {
    cout << "Node not found" << endl;
    return -1;
  }
  cout << "What is the name of the node you want to end at? ";
  cin.get(input, 20);
  cin.get();
  int endIndex = getIndex(input, vertexList);
  if(endIndex == -1) {
    cout << "Node not found" << endl;
    return -1;
  }

  //We create a new itemList and initialize it using the vertex list
  item* itemList[SIZE];
  for(int i = 0; i < SIZE; i++) {
    itemList[i] = new item(vertexList[i]);
  }
  itemList[startIndex]->value = 0;

  //Call and return the value from the dijkstra function
  return Dijkstra(itemList, adjacencyTable, endIndex);
  
}

//Dijkstra function
int Dijkstra(item** itemList, int** adjacencyTable, int endIndex) {
  //Variables for storing the smallest value and index
  int smallValue =  numeric_limits<int>::max();
  int smallIndex = -1;

  //We go through the itemList and find the item with the smallest value (or distance to it from the original)
  for(int i = 0; i < SIZE; i++) {
    if(itemList[i]->vert != NULL && itemList[i]->value < smallValue && itemList[i]->visited == false) {
      smallValue = itemList[i]->value;
      smallIndex = i;
    }
  }

  //If the smallestIndex is -1, that means something went wrong and we return that
  if(smallIndex == -1) {
    return -1;
  }

  //If this is the end index, we don't need to keep going
  if(smallIndex == endIndex) {
    return smallValue;
  }
  //We set the visitied variable to true so we don't come back here
  itemList[smallIndex]->visited = true;

  //We loop through the column of the adjacency list, and if for any of the vertex's the distance from the current node + the current vertex's value is less than that vertex's, we change that vertex's value
  for(int i = 0; i < SIZE; i++) {
    if(adjacencyTable[smallIndex][i] != -1) {
      if((itemList[smallIndex]->value + adjacencyTable[smallIndex][i]) < itemList[i]->value) {
	itemList[i]->value = itemList[smallIndex]->value + adjacencyTable[smallIndex][i];
      }
    }
  }
  return Dijkstra(itemList, adjacencyTable, endIndex);
}

//Print command only used for debugging (don't worry about it IGNORE IT)
void print(vertex** vertexList, int** adjacencyTable) {
  for(int i = 0; i < SIZE; i++) {
    if(vertexList[i] != NULL) {
      cout << i << " " << vertexList[i]->name << endl;
    }
  }
  cout << endl;
  bool newLine;
  for(int i = 0; i < SIZE; i++) {
    newLine = false;
    for (int j = 0; j < SIZE; j++) {
      if(adjacencyTable[i][j] != -1) {
	cout << adjacencyTable[i][j] << "\t";
	newLine = true;
      }
      else if(vertexList[j] != NULL) {
	cout << "\t";
      }
    }
    if(newLine = true) {
      cout << endl;
    }
  }
}

//Add vertex adds a vertex to the tree
void addVertex(vertex** vertexList) {
  //The next few lines get input from the user
  cout << "What is the name of the vertex you want to add? ";
  char* name = new char[20];
  cin.get(name, 20);
  cin.get();

  //The next lines figure out where the first empty spot in the array is
  int index = 0;
  while(index < SIZE && (vertexList[index] != NULL)) {
    index++;
  }
  
  //If there are no empty spots, we don'tdo anything, otherwise we add a new vertex to that spot
  if(index == SIZE) {
    cout << "No more space in memeory" << endl;
    return;
  }

  else {
    vertexList[index] = new vertex(name);
  }
  
}

//Add's an edge
void addEdge(vertex** vertexList, int** adjacencyTable) {
  //Most of the following lines get the input from the user
  cout << "What is the name of the first vertex of the edge? ";
  char* first = new char[20];
  cin.get(first, 20);
  cin.get();
  int firstN = getIndex(first, vertexList);
  if(firstN == -1) {
    cout << "Vertex not found" << endl;
    return;
  }
  cout << "What is the name of the second vertex of the edge? ";
  char* second = new char[20];
  cin.get(second, 20);
  cin.get();
  int secondN = getIndex(second, vertexList);
  if(secondN == -1) {
    cout << "Vertex not found" << endl;
    return;
  }
  cout << "What is the weight you want for this edge? ";
  int weight;
  cin >> weight;
  cin.get();

  //We set that spot on the adjacencytable to the weight the user specified
  adjacencyTable[firstN][secondN] = weight;

}

//Delete's a vertex
void deleteVertex(vertex** vertexList, int** adjacencyTable) {
  //The next lines are input from the user
  cout << "What is the name of the vertex you want to delete? ";
  char name[20];
  cin.get(name, 20);
  cin.get();  
  int index = getIndex(name, vertexList);
  if(index == -1) {
    cout << "Vertex not found" << endl;
    return;
  }

  //We go through the adjacency table and set any edge with that vertex on either side to -1
  for(int i = 0; i < SIZE; i++) {
    adjacencyTable[index][i] = -1;
    adjacencyTable[i][index] = -1;
  }

  //we set that spot in the vertexlist to null
  vertexList[index] = NULL;
  
}

//Deletes an edge off the graph
void deleteEdge(vertex** vertexList, int** adjacencyTable) {
  //The next few lines just get the information from the user
  cout << "What is the name of the first vertex of the edge you want to delete? ";
  char first[20];
  cin.get(first, 20);
  cin.get();
  int firstN = getIndex(first, vertexList);
  if(firstN == -1) {
    cout << "Vertex not found" << endl;
    return;
  }  
  cout << "What is the name of the second vertex of the edge you want to delete? ";
  char second[20];
  cin.get(second, 20);
  cin.get();
  int secondN = getIndex(second, vertexList);
  if(secondN == -1) {
    cout << "Vertex not found" << endl;
    return;
  }
  
  adjacencyTable[firstN][secondN] = -1;//We set that spot in the adjacency table to -1 to show that there isn't an edge
}

//Gets the index of a vertex based on the name
int getIndex(char* name, vertex** vertexList) {
  //goes through all the vertex's until we find one
  for (int i = 0; i < SIZE; i++) {
    if(vertexList[i] != NULL && strcmp(vertexList[i]->name, name) == 0) {
      return i;
    }
  }
  return -1;//Otherwise we return -1 to simbolize that we didn't find the node
}
