#include <iostream>
#include <string.h>
#include <fstream>


using namespace std;

#define BLACK true
#define RED false
#define RIGHT 1
#define LEFT 2
#define COUNT 10

//Node struct
struct node {
  //node* left, right, parent;
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
  
  char input[20];
  while(true) {
    cout << "> ";
    cin.get(input, 20);
    cin.get();
    if(strcmp(input, "ADD") == 0) {
      cout << "Enter any number in the relm of integers (0-2^31) to be added to the tree: ";
      int newNumber;
      cin >> newNumber;
      cin.get();
      fixTree(head, callInsert(head, newNumber));
    }
    else if(strcmp(input, "PRINT") == 0) {
      print(head, 0);
    }
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

void fixTree(node* &head, node* current) {
  
  //If our node is the first top node 
  if(head == current) {
    current->color = BLACK;
    return;
  }

  cout << "CASE PRE" << endl;
  //Parent and uncle are both red
  if(getColor(current->parent) == RED && getColor(getUncle(current)) == RED) {
    cout << "IN PRE" << endl;
    current->parent->color = BLACK;
    getUncle(current)->color = BLACK;
    current->parent->parent->color = RED;
    cout << "GOING INTO FIXTREE" << endl;
    //current = current->parent->parent
    fixTree(head, current->parent->parent);
    return;
  }

  cout << "GOING INTO CASES" << endl;
  //Uncle is black and parent is red
  if((getColor(current->parent) == RED) && (getColor(getUncle(current)) == BLACK)) {
    cout << "IN CASES" << endl;
    //Triangle
    /*
           G(B)
       P(R)
           C(R)
     */
    if(current->data >= current->parent->data && current->parent->parent->data >= current->parent->data) {
      cout << "CASE: 0" << endl;
      node* parent = current->parent;
      node* grandparent = current->parent->parent;

      current->left = parent;
      grandparent->left = current;
      parent->right = NULL;
      parent->parent = current;
      current->parent = grandparent;
      //current = parent;
      fixTree(head, parent);
      return;
    }
    /*
      G(B)
           P(R)
      C(R)
     */
    
    else if(current->data < current->parent->data && current->parent->parent->data < current->parent->data) {
      cout << "CASE: 1" << endl;
      node* parent = current->parent;
      node* grandparent = current->parent->parent;
      
      current->right = parent;
      grandparent->right = current;
      parent->left = NULL;
      parent->parent = current;
      current->parent = grandparent;
      //current = parent;
      fixTree(head, parent);
      return;
    }

    /*
      G (B)
            P(R)
	         C(R)

     */
    if(current->data >= current->parent->data && current->data >= current->parent->parent->data) {
      cout << "CASE 2" << endl;
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
                 G (B)
            P(R)
      C(R)

     */
    if(current->data < current->parent->data && current->data < current->parent->parent->data) {
      cout << "CASE 3" << endl;
      node* siblingD = getSibling(current);
      node* grandparentB = current->parent->parent;
      node* parentA = current->parent;
      cout << "CASE 3a" << endl;
      parentA->right = grandparentB;
      cout << "Case 3a1" << endl;
      grandparentB->left = siblingD;
      cout << "Case 3a2" << endl;
      if(siblingD != NULL) {
	siblingD->parent = grandparentB;
      }
      cout << "CASE 3b" << endl;
      if(grandparentB == head) {
	cout << "CASE 3c" << endl;
        head = parentA;
        parentA->parent = NULL;
        grandparentB->parent = parentA;
      }
      else {
	cout << "CASE 3d" << endl;
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









































bool getColor(node* current) {
  if(current == NULL) {
    return BLACK;
  }
  return current->color;
}

node* getSibling(node* current) {
  node* parent = current->parent;
  if(parent->data >= current->data) {
    return parent->right;
  }
  else {
    return parent->left;
  }
}

node* getUncle(node* current) {
  if(current->parent == NULL){
    return NULL;
  }
  return getSibling(current->parent);
}

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


node* insert (node* &head, int element, int side) {
  if(side == RIGHT){
    //node* current = head->right;
    
    if(head->right == NULL) {
      head->right = new node(element);
      head->right->parent = head;
      return head->right;
    }
    else if(head->right->data >= element) {
      return insert(head->right, element, LEFT);
    }
    else {
      return insert(head->right, element, RIGHT);
    }
    
  }
  else {
    //node* current = head->left;
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
