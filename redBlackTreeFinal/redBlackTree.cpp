/*
  Red-Black Tree
  By: Nividh Singh
  Date: 12/11/20

  This program is a self balancing BST
  Video used for reference: https://www.youtube.com/watch?v=5IBxA-bZZH8&list=PL9xmBV_5YoZNqDI8qfOZgzbqahCUmUEin&index=3
*/




#include <iostream>
#include <string.h>
#include <fstream>


using namespace std;

//Constants
#define BLACK true
#define RED false
#define RIGHT 1
#define LEFT 2
#define COUNT 10

//Node struct
struct node {
  node* left;
  node* right;
  node* parent;
  int data;
  bool color;
  node(int element) {
    left = NULL;
    right = NULL;
    parent = NULL;
    data = element;
    color = RED;
  }
};

//Prototypes
node* insert (node* &head, int element, int side);//Inserts a new element without fixing
node* callInsert (node* &head, int element);//Calls insert function
bool getColor(node* current);//Gets the color of a node
node* getSibling(node*current);//Gets a sibling of a node
node* getUncle(node* current);//Gets an uncle of a node
void print(node* head, int size);//Prints the tree
void fixTree(node* &head, node* current);//Fixes the tree (this calls insert and runs through the cases)

//main function
int main() {
  //Node pointer for the top
  node* head = NULL;

  //Loop for the program to keep going
  char input[20];
  while(true) {
    cout << "> ";
    cin.get(input, 20);
    cin.get();
    //If the user says add, then we get an input and we simply add it to our binary tree
    if(strcmp(input, "ADD") == 0) {
      cout << "Enter any number in the relm of integers (0-2^31) to be added to the tree: ";
      int newNumber;
      cin >> newNumber;
      cin.get();
      fixTree(head, callInsert(head, newNumber));
    }
    //If the user says print, we print
    else if(strcmp(input, "PRINT") == 0) {
      print(head, 0);
    }
    //If the user wants us to read from a file, we ask for the file name and read from the file, one number at a time adding to our red-black tree
    else if(strcmp(input, "READ") == 0) {
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
	fixTree(head, callInsert(head, number));
      }
      file.close();
    }
  }
}

//This function fixes the tree
void fixTree(node* &head, node* current) {
  
  //If our node is the first root/top/head node, we make it black 
  //This is case 0
  if(head == current) {
    current->color = BLACK;
    return;
  }

  //Parent and uncle are both red
  //This is case 1
  if(getColor(current->parent) == RED && getColor(getUncle(current)) == RED) {
    current->parent->color = BLACK;
    getUncle(current)->color = BLACK;
    current->parent->parent->color = RED;
    fixTree(head, current->parent->parent);
    return;
  }

  //Uncle is black and parent is red
  //This is case 2/3
  if((getColor(current->parent) == RED) && (getColor(getUncle(current)) == BLACK)) {

    /*We go into this if statemenet if we form a triangle like:
           G(B)
       P(R)
           C(R)

       Case 2
     */
    if(current->data >= current->parent->data && current->parent->parent->data >= current->parent->data) {
      node* parent = current->parent;
      node* grandparent = current->parent->parent;

      current->left = parent;
      grandparent->left = current;
      parent->right = NULL;
      parent->parent = current;
      current->parent = grandparent;
      fixTree(head, parent);
      return;
    }
    /*This is if the triangle is the other way around
      G(B)
           P(R)
      C(R)

      Case 2
     */
    
    else if(current->data < current->parent->data && current->parent->parent->data < current->parent->data) {
      node* parent = current->parent;
      node* grandparent = current->parent->parent;
      
      current->right = parent;
      grandparent->right = current;
      parent->left = NULL;
      parent->parent = current;
      current->parent = grandparent;
      fixTree(head, parent);
      return;
    }


    /*THis is if we form a line as follows
                 G (B)
            P(R)
      C(R)

      Case 3
      The letter after the variable (like the D in siblingD) is refering to the example in video linked at the very top that I used as reference 
     */

    if(current->data >= current->parent->data && current->data >= current->parent->parent->data) {
      node* siblingD = getSibling(current);
      node* grandparentB = current->parent->parent;
      node* parentA = current->parent;
      parentA->left = grandparentB;
      grandparentB->right = siblingD;
      if(siblingD != NULL) {
	siblingD->parent = grandparentB;
      }
      if(grandparentB == head) {
	head = parentA;
	parentA->parent = NULL;
	grandparentB->parent = parentA;
      }
      else {
	parentA->parent = grandparentB->parent;
	grandparentB->parent = parentA;
	node* greatGrandparent = parentA->parent;
	if(parentA->data >= greatGrandparent->data) {
	  greatGrandparent->right = parentA;
	}
	else {
	  greatGrandparent->left = parentA;
	}
      }
      parentA->color = BLACK;
      grandparentB->color = RED;
    }
    /*
      This is if we form a line as follows
      G (B)
            P(R)
                 C(R)

       Case 3
       The letter after the variable (like the D in siblingD) is refering to the example in video linked at the very top that I used as reference
     */
    if(current->data < current->parent->data && current->data < current->parent->parent->data) {
      node* siblingD = getSibling(current);
      node* grandparentB = current->parent->parent;
      node* parentA = current->parent;
      parentA->right = grandparentB;
      grandparentB->left = siblingD;
      if(siblingD != NULL) {
	siblingD->parent = grandparentB;
      }
      if(grandparentB == head) {
      head = parentA;
        parentA->parent = NULL;
        grandparentB->parent = parentA;
      }
      else {
        parentA->parent = grandparentB->parent;
        grandparentB->parent = parentA;
        node* greatGrandparent = parentA->parent;
        if(parentA->data < greatGrandparent->data) {
          greatGrandparent->left = parentA;
        }
        else {
          greatGrandparent->right = parentA;
        }
      }
      parentA->color = BLACK;
      grandparentB->color = RED;
    }    
  }
}


//This gets the color of the current node (so that everytime we don't have to check for NULL)
bool getColor(node* current) {
  if(current == NULL) {
    return BLACK;
  }
  return current->color;
}

//This gets the sibling of the current node
node* getSibling(node* current) {
  node* parent = current->parent;
  if(parent->data >= current->data) {
    return parent->right;
  }
  else {
    return parent->left;
  }
}

//This gets the uncle of the current node
node* getUncle(node* current) {
  if(current->parent == NULL){
    return NULL;
  }
  return getSibling(current->parent);
}

//This is the same print function as BST, but it also prints R or B for red or black
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
  cout<<head->data;
  if(getColor(head) == BLACK) {
    cout << "B"; 
  }
  else {
    cout << "R";  
  }
  
  cout << endl;
  //Finally we print everything to the left of our node
  print(head->left, space);
}

//This calls insert, so that the previous function doesn't have to figure out if they have to put left or right
node* callInsert (node* &head, int element) {
  if(head == NULL) {
    head = new node(element);
    return head;
  }
  if(head->data >= element) {
    return insert(head, element, LEFT);
  }
  else{
    return insert(head, element, RIGHT);
  }
}


//Function to insert - Its built like this so we can set parent nodes easily
node* insert (node* &head, int element, int side) {

  //If the previous repititon said to go to the right side, we check the right side
  if(side == RIGHT){
    //If it is null, we change it to a new node with the element and set the parent of the new node to the parent(head)
    if(head->right == NULL) {
      head->right = new node(element);
      head->right->parent = head;
      return head->right;
    }
    //Otherwise if we have to go to the left, we tell the next repetition to go to the left (so that the next repetition has acces to the parent function)
    else if(head->right->data >= element) {
      return insert(head->right, element, LEFT);
    }
    //Same thing if it has to go right
    else {
      return insert(head->right, element, RIGHT);
    }
  }
  //We do the same thing if the side is left, and its self explanitory based on the previous section
  else {
    if(head->left == NULL) {
      head->left = new node(element);
      head->left->parent = head;
      return head->left;
    }
    else if(head->left->data >= element) {
      return insert(head->left, element, LEFT);
    }
    else {
      return insert(head->left, element, RIGHT);
    }
  }
}
