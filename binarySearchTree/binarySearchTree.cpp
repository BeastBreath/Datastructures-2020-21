/*
Made by: Nividh Singh
Date: 12/4/20
This program stores numbers using a binary search tree

https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/

Compile using -D DEBUG if you want to see the debug messages
*/


#include<iostream>
#include<cstring>
#include<fstream>
#include<array>

//Node struct
struct node {
  node* left;
  node* right;
  int data;

  node() {
    left = NULL;
    right = NULL;
    data = -1;
  }
  node(int i) {
    left = NULL;
    right = NULL;
    data = i;
  }
  ~node() {
    //delete data;
  }
};


using namespace std;
const int COUNT = 10;

node** search(node* &head, int element);
void insert(node* &head, int element);
void deleteElement(node* &head, int element);
void print(node* root, int size);
void printDebugStatement(auto);

//Main method
int main() {
  cout << "Welcome to Binary Search Tree. Your commands are ADD, DELETE, SEARCH, PRINT, FILE, and QUIT" << endl;

  //Variables for the head node pointer, the input, and if the program is going
  node* head = NULL;
  char input[20];
  bool going = true;

#ifdef DEBUG
  //If we are trying to debug, we put some constant values in so that we don't have to keep adding and also so its the same everytime and we can debug a lot better
  insert(head, 84);
  insert(head, 2);
  insert(head, 8);
  insert(head, 6);
  insert(head, 31);
  insert(head, 9);
  insert(head, 523);
  insert(head, 55);
  insert(head, 54);
  insert(head, 51);
  insert(head, 43);
  insert(head, 423);
  insert(head, 434);
  insert(head, 176);
  insert(head, 16);
  insert(head, 15);
  insert(head, 433);
  insert(head, 70);
  insert(head, 59);
  insert(head, 32);

  print(head, 0);
  int inputs;
  cin >> inputs;
  cin.get();
  deleteElement(head, inputs);
  print(head, 0);
#endif


  //Goes until user wants to stop
  while(going){
    cout << "> ";
    cin.get(input, 19);
    cin.get();

    //If the user says add, then we get the element the user wants to add and call the insert function
    if(strcmp(input, "ADD") == 0) {
      cout << "What is the element you want to add? ";
      int element;
      cin >> element;
      cin.get();
      insert(head, element);
    }
    //If the user inputs search, we ask the user what they want to search for and call search
    //If search returns NULL, we tell the user that the element wasn't found, otherwise we say it was found
    else if(strcmp(input, "SEARCH") == 0) {
      cout << "What do you want to search for? ";
      int element;
      cin >> element;
      cin.get();
      if(search(head, element) == NULL) {
	cout << "Element not found" << endl;
      }
      else{
	cout << "Element found" << endl;
      }
    }
    //If the user says delete, we ask what element they want to delete and call the delete function
    else if(strcmp(input, "DELETE") == 0) {
      cout << "What do you want to delete? ";
      int element;
      cin >> element;
      cin.get();
      deleteElement(head, element);
    }
    //If the user wants to print, we call the print function
    else if(strcmp(input, "PRINT") == 0) {
      print(head, 0);
    }
    //If the user wants to quit, we make going false and end the program
    else if(strcmp(input, "QUIT") == 0) {
      going = false;
    }
    //If user wants to add from file 
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
	insert(head, number);
      }
      file.close();
    }
    else {
      cout << "ELEMENT NOT FOUND" << endl;
    }
  }
}

//Search function
//The reason it returns a node** not a bool is because we also use it in the delete function
node** search(node* &head, int element) {
  //If we are searching when the head is NULL, we return NULL to show that the element isn't found
  if (head == NULL) {
    return NULL;
  }
  //If the data at that node is equal to the element, we return the address of the node pointer, so we can use it in the delete function
  if(head->data == element) {
    return (&head);
  }
  //If the number at the node is smaller than the element, we search the tree to the right of the node
  if(head->data < element) {
    return search(head->right, element);
  }
  //If the number at the node is bigger than the element, we search the tree to the left of the node
  if(head->data > element) {
    return (search(head->left, element));
  }
  //It should never go down here, but if it does, then we just print a message and pretend it didn't happen
  cout << "Unknown error occurred" << endl;
  return NULL;
}

//Insert function
//We pass it in by reference, so we can change the pointer thats in the previous node and that way we don't have to store the previous node
void insert(node* &head, int element) {
  printDebugStatement("IN INSERT");
  //if the head is null, we make the previous node's pointer to a new node with the element
  if(head == NULL) {
    printDebugStatement("IN INSERT NULL");
    head = new node(element);
  }
  //if the number at the node is bigger than the element, we use recurssion and insert it into the left tree
  else if(head->data > element) {
    printDebugStatement("IN INSERT data>element");
    insert(head->left, element);
  }
  //Otherwise we insert it into the right tree under that node
  else {
    printDebugStatement("IN INSERT data>= element");
    insert(head->right, element);
  }
}

//Delete function
/*
This function is really messy because I was trying something to use pointers and addresses, but I screwed some stuff up and thats where we're at now
headA is the node thats passed in by reference that we use for searching
headR is the address of the pointer that points to the node we want to delete
head is the pointer to the node that we want to delete
*/
void deleteElement(node* &headA, int element) {
  node** headR = search(headA, element);
  //If we have a null value for headR, it means that search returned NULL which means the element is not in the tree
  if(headR == NULL) {
    cout << "NODE NOT FOUND" << endl;
    return;
  }
  node* head = (*headR);
  //Head shoudn't be NULL unless we ran out of memory on the computer so we check for that
  if(head == NULL) {
    cout << "Unkown error" << endl;
  }
  printDebugStatement("BREAK POINT 1");
  //If both the children are NULL, we set the pointer to that node to NULL (which sets the parent node's pointer to null
  if(head->right == NULL && head->left == NULL) {
    printDebugStatement("Delete element end");
    (*headR) = NULL;
    return;
  }
  printDebugStatement("breakpoint 2");
  //If the right is null, we just pull up the left into the spot of the node
  if(head->right == NULL) {
    printDebugStatement("RIGHT NULL");
    (*headR) = head->left;
    return;
  }
  printDebugStatement("BREAKPOINT 3");
  //If the left is NULL, we just pull up the right to take the spot of the node
  if(head->left == NULL) {
    printDebugStatement("LEFT NULL");
    (*headR) = head->right;
    return;
  }
  printDebugStatement("Breakpoint 4");

  //If none of this happens, then we want to find the next smallest, and then put that there
  node* replaceElement = head->left;//replaceElement is the node to the left (because the first time we go to the left) We know that this isn't null because of the previous if statements
  node** previous = &(head->left);//Previous is the address of replaceElement, but its the address of the parent node's pointer, so we can directely change the parent node's pointer
  printDebugStatement("Breakpoint 5");
  if(replaceElement == NULL) {
    printDebugStatement("NNNUULLL");
  }
  printDebugStatement(replaceElement->data);

  //We keep going right in the tree until we reach the 'end' which finds the number thats the closest and smaller than the number we are deleting
  while(replaceElement->right != NULL) {
    replaceElement = replaceElement->right;
    previous = &((*previous)->right);
  }
  printDebugStatement((*previous)->data);
  (*previous) = ((*previous)->left);//We set the node we're at to the node thats to the left of the one we are at
  (*headR)->data = replaceElement->data;//We don't actually move around the nodes, we just change the data
}

//Print function
void print(node *head, int space)  
{
  //if the node pointer is null, we just return
  if (head == NULL) {
    return;
  }
  //This increases indentation by however much we want (which is a constant called count)  
  space += COUNT;  
  
  //First we print the right sequence  
  print(head->right, space);
  
  //Then we print out a new line
  cout<<endl;
  //Next we print out the number of spaces that we need (based on our variable called space
  for (int i = COUNT; i < space; i++){
    cout<<" ";
  }
  //Then we print out the number
  cout<<head->data<<"\n";
  
  //Finally we print everything to the left of our node
  print(head->left, space);
}

void printDebugStatement(auto toPrint) {
  #ifdef DEBUG
    cout << toPrint << endl;
  #endif
}