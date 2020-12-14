/*
  Red-Black Tree
  By: Nividh Singh
  Date: 12/11/20

  This program is a self balancing BST
  Video used for reference for insertion: https://www.youtube.com/watch?v=5IBxA-bZZH8&list=PL9xmBV_5YoZNqDI8qfOZgzbqahCUmUEin&index=3
  Video used for reference for deletion: https://www.youtube.com/watch?v=CTvfzU_uNKE
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
node* search(node* head, int element) ;//Search Function
node* nodeToDelete(node* head, int element);//Finds the next greatest node after a node
void callDelete(node* &head, int element);
int getNumberOfChildren(node* current);
int getSide(node* child, node* parent);
bool deleteNode(node* current);
void doubleBlackFix(node* &head, node* doubleBlack, bool todelete);
int debug(node* head, int count);

//main function
int main() {
  cout << "Welcome to red black tree. This is an advanced version of binary search tree because it self balances. Please enter one of the following commands: ADD READ PRINT DELETE TEST HELP QUIT" << endl;

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
    //If the user says delete, we can delete a node
    else if(strcmp(input, "DELETE") == 0) {
      cout << "What is the number you want to delete? ";
      int inputNumber;
      cin >> inputNumber;
      cin.get();
      callDelete(head, inputNumber);
    }
    //If the user doesn't trust the procces, they can check if the tree is balanced(at user command)
    else if(strcmp(input, "TEST") == 0) {
      //test = search(head, 10);
      if(debug(head, 0) == -1) {
	cout << "Test failed. Tree isn't balanced" << endl;
      }
      else {
	cout << "Test passed. Tree is balanced" << endl;
      }
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
    //If user says quit, we quit
    else if(strcmp(input, "QUIT") == 0) {
      cout << "Sorry to see you go. NOW GET OUT OF MY FACE I AM BREAKING UP WITH YOU" << endl;
      cout << "Sike" << endl;
      break;
    }
    //If user says help, we help them
    else if(strcmp(input, "HELP") == 0) {
      cout << "Here are the commands" << endl;
      cout << "ADD - you can add a number to the tree using the console\nREAD - you can read in a file and put the numbers from the file into the tree\nPRINT - prints the tree\nDELETE - you can delete a number from the tree\nTest - you can tell the program to check if the tree is balanced (meaning the same number of black nodes in every chain)\nHELP - prints help commands\nQUIT - quits the program" << endl;
    }
    else {
      cout << "Invalid command" << endl;
    }
  }
}

//Recursive function to check if the tree is balanced by counting black nodes
int debug(node* head, int count) {
  if(head == NULL) {
    return count;
  }
  if(getColor(head) == BLACK) {
    count++;
  }
  int i = debug(head->left, count);
  int j = debug(head->right, count);

  if(i == j && i != -1) {
    return i;
  }
  return -1;
  
}

//This function deletes a node by finding its parent and setting the parents child in that direction to the current node's child (we assume the node we're trying to delete only has one child)
bool deleteNode(node* current) {
  //If the current is null, then we have a problem
  if(current == NULL) {
    return false;
  }
  //We find the child of our current node
  node* child = NULL;
  if(current->right != NULL) {
    child = current->right;
  }
  else {
    child = current->left;
  }
  
  //We set the parent's child to the child of the current node's child
  if(getSide(current, current->parent) == RIGHT) {
    current->parent->right = child;
  }
  else {
    current->parent->left = child;
  }
  
  //delete current;
  return true;
}

//Funcion to fix the tree if we have a double black node (terminology refering to video linked at the top)
//head is the head, doubleblack is our current node, and toDelete tells us if we should or shouldn't delete the node
void doubleBlackFix(node* &head, node* doubleBlack, bool toDelete) {

  /*
    A listing of the cases and what happens after the cases
    Case 1: Only one without mirror image
    Case 2->3
    Case 3->4
    Case 4->terminal
    Case 5->6
    Case 6->terminal
    
  */

  //If the head is the double black, we check if we have to delete it, and if we don't then we don't do anything else
  if(head == doubleBlack) {
    if(toDelete) {
      deleteNode(doubleBlack);
    }
    return;
  }

  //Sets parent, sibling, and newphew nodes to make our life easier
  node* parent = doubleBlack->parent;
  node* sibling = getSibling(doubleBlack);
  node* nephewRight = getSibling(doubleBlack)->right;
  node* nephewLeft = getSibling(doubleBlack)->left;
    
  
  //This is for all the cases where our double black node is the left sibling
  if(getSide(doubleBlack, doubleBlack->parent) == LEFT) {

    /*
      Case: 2
      Parent: Black
      Sibling: Red
      NephewRight: Black
      NephewLeft: Black
    */
    if(getColor(parent) == BLACK && getColor(sibling) == RED && getColor(nephewRight) == BLACK && getColor(nephewLeft) == BLACK) {
      if(head == parent) {
	head = sibling;
	sibling->parent = NULL;
      }
      else {
	sibling->parent = parent->parent;
	if(getSide(parent, parent->parent) == LEFT) {
	  parent->parent->left = sibling;
	}
	else {
	  parent->parent->right = sibling;
	}
      }  
      parent->color = RED;
      sibling->color = BLACK;

      if(nephewLeft != NULL) {
	nephewLeft->parent = parent;
      }
      sibling->left = parent;
      parent->parent = sibling;
      parent->right = nephewLeft;
      
      doubleBlackFix(head, doubleBlack, toDelete);
      return;
    }
    
    /*
      Case: 3
      Parent: Black
      Sibling: Black
      NephewRight: Black
      NephewLeft: Black
    */
    if(getColor(parent) == BLACK && getColor(sibling) == BLACK && getColor(nephewRight) == BLACK && getColor(nephewLeft) == BLACK) {
  
      sibling->color = RED;
      //if delete, we can delete the doubleBlack
      //Call fix doublblac from doubleBlack->parent with toDelete = false
      if(toDelete) {
	deleteNode(doubleBlack);
      }
      doubleBlackFix(head, doubleBlack->parent, false);
      return;
    }
    
    /*
      Case: 4
      Parent: Red
      Sibling: Black
      NephewRight: Black
      NephewLeft: Black
    */
    
    if(getColor(parent) == RED && getColor(sibling) == BLACK) {
      if(getColor(nephewRight) == BLACK && getColor(nephewLeft) == BLACK) {
	sibling->color = RED;
	parent->color = BLACK;
	if(toDelete) {
	  deleteNode(doubleBlack);
	}
	return;
      }
      else if(getColor(nephewRight) == BLACK && getColor(nephewLeft) == RED) {
        parent->right = nephewLeft;
        nephewLeft->parent = parent;
        node* child = nephewLeft->right;
        if(child != NULL) {
          child->parent = sibling;
        }
        sibling->left = child;
        sibling->parent = nephewLeft;
        nephewLeft->right = sibling;

        nephewLeft->color = BLACK;
        sibling->color = RED;
	doubleBlackFix(head, doubleBlack, toDelete);
        return;
      }
    }

    /*
      Case: 5
      Parent: Black
      Sibling: Black
      NephewRight: Black
      NephewLeft: Red
    */
    if(getColor(parent) == BLACK && getColor(sibling) == BLACK && getColor(nephewRight) == BLACK && getColor(nephewLeft) == RED) {
      node* n4 = nephewLeft->right;
      parent->right = nephewLeft;
      nephewLeft->parent = parent;
      sibling->parent = nephewLeft;
      sibling->left = n4;
      nephewLeft->right = sibling;
      if(n4 != NULL) {
	n4->parent = sibling;
      }
      nephewLeft->color = BLACK;
      sibling->color = RED;
      doubleBlackFix(head, doubleBlack, toDelete);
      return;
    }
    
    /*
      Case: 6
      Parent: Blue
      Sibling: Black
      NephewRight: Blue
      NephewLeft: Red
    */
    if(getColor(sibling) == BLACK && getColor(nephewRight) == RED) {
      if(parent != head) {
	sibling->parent = parent->parent;
	if(getSide(parent, parent->parent) == LEFT) {
	  parent->parent->left = sibling;
	}
	else {
	  parent->parent->right = sibling;
	}
      }
      else {
	head = sibling;
	sibling->parent = NULL;	
      }
    
      parent->parent = sibling;
      parent->right = nephewLeft;
      if(nephewLeft != NULL) {
	nephewLeft->parent = parent;
      }
      sibling->left = parent;
      nephewRight->color = BLACK;
      sibling->color = parent->color;
      parent->color = BLACK;
      
      if(toDelete) {
	deleteNode(doubleBlack);
      }
      return;
    }
  }
  
  else {
    
    /*
      Case: 2
      Parent: Black
      Sibling: Red
      NephewRight: Black
      NephewLeft: Black
    */
    if(getColor(parent) == BLACK && getColor(sibling) == RED && getColor(nephewRight) == BLACK && getColor(nephewLeft) == BLACK) {
      if(head == parent) {
	head = sibling;
        sibling->parent = NULL;
      }
      else {
	sibling->parent = parent->parent;
        if(getSide(parent, parent->parent) == LEFT) {
	  parent->parent->left = sibling;
	}
        else {
	  parent->parent->right = sibling;
        }
      }
      parent->color = RED;
      sibling->color = BLACK;

      if(nephewRight != NULL) {
	nephewRight->parent = parent;
      }
      sibling->right = parent;
      parent->parent = sibling;
      parent->left = nephewRight;
      //call fixdoubleblack from node toDelete = true
      doubleBlackFix(head, doubleBlack, toDelete);
      return;
    }

    /*
      Case: 3
      Parent: Black
      Sibling: Black
      NephewRight: Black
      NephewLeft: Black
    */
    if(getColor(parent) == BLACK && getColor(sibling) == BLACK && getColor(nephewRight) == BLACK && getColor(nephewLeft) == BLACK) {
      sibling->color = RED;
      //if delete, we can delete the doubleBlack
      //Call fix doublblac from doubleBlack->parent with toDelete = false
      if(toDelete) {
	deleteNode(doubleBlack);
      }
      doubleBlackFix(head, doubleBlack->parent, false);
      return;
    }

    /*
      Case: 4
      Parent: Red
      Sibling: Black
      NephewRight: Black or Red
      NephewLeft: Black
    */    
    if(getColor(parent) == RED && getColor(sibling) == BLACK) {
      if(getColor(nephewRight) == BLACK && getColor(nephewLeft) == BLACK) {
	sibling->color = RED;
	parent->color = BLACK;
	if(toDelete) {
	  deleteNode(doubleBlack);
	}
	return; 
      }
      else if(getColor(nephewRight) == RED && getColor(nephewLeft) == BLACK) {
	parent->left = nephewRight;
	nephewRight->parent = parent;
	node* child = nephewRight->left;
	if(child != NULL) {
	  child->parent = sibling;
	}
	sibling->right = child;
	sibling->parent = nephewRight;
	nephewRight->left = sibling;
	
	nephewRight->color = BLACK;
	sibling->color = RED;
	doubleBlackFix(head, doubleBlack, toDelete);
	return;
      }
    }
    
    /*
      Case: 5
      Parent: Black
      Sibling: Black
      NephewRight: Red
      NephewLeft: Black
    */
    if(getColor(parent) == BLACK && getColor(sibling) == BLACK && getColor(nephewLeft) == BLACK && getColor(nephewRight) == RED) {
      node* n4 = nephewRight->left;
      parent->left = nephewRight;
      nephewRight->parent = parent;
      sibling->parent = nephewRight;
      sibling->right = n4;
      nephewRight->left = sibling;
      if(n4 != NULL) {
        n4->parent = sibling;
      }
      
      nephewRight->color = BLACK;
      sibling->color = RED;
      //Call fixdouble black with the same thing
      doubleBlackFix(head, doubleBlack, toDelete);
      return;
    }
    
    /*
      Case: 6
      Parent: Blue
      Sibling: Black
      NephewRight: Red
      NephewLeft: Blue
    */
    if(getColor(sibling) == BLACK && getColor(nephewLeft) == RED) {
      if(parent != head) {
        sibling->parent = parent->parent;
        if(getSide(parent, parent->parent) == RIGHT) {
          parent->parent->right = sibling;
        }
        else{
          parent->parent->left = sibling;
        }
      }
      else {
        head = sibling;
	sibling->parent = NULL;
      }

      parent->parent = sibling;
      parent->left = nephewRight;
      if(nephewRight != NULL) {
	nephewRight->parent = parent;
      }
      sibling->right = parent;
      nephewLeft->color = BLACK;
      sibling->color = parent->color;
      parent->color = BLACK;
      if(toDelete) {
        deleteNode(doubleBlack);
      }
      return;
    }
  }
}

//Function to start off the delete (if there isn't a double black, the deletion also finishes here
void callDelete(node* &head, int element) {
  //If the head dis null, that means the tree is empty so we return
  if(head == NULL) {
    return;
  }
  
  node* elementNode = search(head, element); //The node containing the number

  //If the elementNode is null it means there isn't a node with the number so we return
  if(elementNode == NULL) {
    return;
  }

  //If the only node is the head and we're trying to delete the head, we just set head to NULL, delete the node and return
  if(elementNode == head && getNumberOfChildren(elementNode) == 0) {
    head = NULL;
    delete elementNode;
    return;
  }
  
  node* toDelete = nodeToDelete(head, element);//Todelete stores the node we are trying to delete (after we swap the values, the one we're trying to delete is the one thats node->right->left->left->left...

  //If the node we want to delete is red and doesn't have two children (it cannot have just one child)
  if(getNumberOfChildren(elementNode) == 0 && getColor(elementNode) == RED) {
    //We just delete the node
    if(getSide(elementNode, elementNode->parent) == RIGHT) {
      elementNode->parent->right = NULL;
      //delete elementNode;
      return;
    }
    else {
      elementNode->parent->left = NULL;
      //delete elementNode;
      return;
    }
  }


  //If the node is black and there aren't two kids, we go into here
  if((getNumberOfChildren(elementNode) != 2 && getColor(elementNode) == BLACK) /*&& (getColor(elementNode->right) == BLACK) && (getColor(elementNode->left) == RED)*/) {

    //If there are zero children, we call the doubleBlackFix function, telling it to delete the current node
    if(getNumberOfChildren(elementNode) == 0) {
      doubleBlackFix(head, elementNode, true);
      return;
    }

    //Otherwise, we create a child node and set it to the 1 child of the Black Node we want to delete
    node* child;
    if(elementNode->right != NULL) {
      child = elementNode->right;
    }
    else {
      child = elementNode->left;
    }

    //If the element isn't the head, we go into this loop
    if(elementNode != head) {

      //If the element is the right child we do this, or we do the same thing except in reverse
      if(getSide(elementNode, elementNode->parent) == RIGHT) {

	//We delete the current node
	elementNode->parent->right = child;
	child->parent = elementNode->parent;
	//If the child is red, we just make it black and its fixed
	if(getColor(child) == RED) {
	  child->color = BLACK;
	  return;
	}
	//Other wise, we have to call the doubleBLackFix method
	else {
	  doubleBlackFix(head, child, false);
	  return;
	}
      }
      //We do the same thing except in reverse for the opposite case
      else {
	elementNode->parent->left = child;
	child->parent = elementNode->parent;
	if(getColor(child) == RED) {
	  child->color = BLACK;
	  return;
	}
	else {
	  doubleBlackFix(head, child, false);
	  return;
	}
      }
    }
    else {
      head = child;
      head->color = BLACK;
      child->parent = NULL;
      return;
    }
  }

  //If none of that happens, then we set the element node's data to what the next biggest one is
  elementNode->data = toDelete->data;
  
  //If the number of children of toDelte is 1, we do the same thing we did with element node in the last if statement
  if(getNumberOfChildren(toDelete) == 1) {
    node* child;
    if(toDelete->right != NULL) {
      child = toDelete->right;
    }
    else {
      child = toDelete->left;
    }
    if(getColor(toDelete) != getColor(child)) {
      if(getSide(toDelete, toDelete->parent) == RIGHT) {
	toDelete->parent->right = child;
      }
      else {
	toDelete->parent->left = child;
      }
      child->parent = toDelete->parent;
      child->color = BLACK;
    }
    return;
  }

  //If the node we are deleting (bottom one) is RED, we just delete it
  if(getColor(toDelete) == RED) {
    
    if(getSide(toDelete, toDelete->parent) == RIGHT) {
      toDelete->parent->right = toDelete->right;
      if(toDelete->right != NULL) {
	toDelete->right->parent = toDelete->parent;
      }
    }
    else {
      toDelete->parent->left = toDelete->right;
      if(toDelete->left != NULL) {
	toDelete->left->parent = toDelete->parent;
      }
    }
    return;
  }

  //If the node to delete is black and the child of it is red, we move the red up and change the color to black
  if(getColor(toDelete) == BLACK && getColor(toDelete->right) == RED) {
    if(toDelete->data >= toDelete->parent->data) {
      toDelete->parent->right = toDelete->right;
      if(toDelete->right != NULL) {
	toDelete->right->color = BLACK;
	toDelete->right->parent = toDelete->parent;
      }
    }
    else {
      toDelete->parent->left = toDelete->right;
      if(toDelete->left != NULL) {
	toDelete->left->color = BLACK;
	toDelete->left->parent = toDelete->parent;
      }
    }
    //delete toDelete;
    return;
  }

  //If none of these cases work, we go into the doubleBlackFix cases
  doubleBlackFix(head, toDelete, true);
}

//This returns the side that the child is of the parent
int getSide(node* child, node* parent) {
  if(parent->right == child) {
    return RIGHT;
  }
  else {
    return LEFT;
  }
}

//This returns the number of children of a node
int getNumberOfChildren(node* current) {
  int returnValue = 2;
  if(current->left == NULL) {
    returnValue --;
  }
  if(current->right == NULL) {
    returnValue--;
  }
  return returnValue;
}

//This finds the node we have to delete (it finds the next biggest node after the first node
node* nodeToDelete(node* head, int element) {
  node* current = search(head, element);
  if(current->right == NULL) {
    return NULL;
  }
  else {
    current = current->right;
  }
  while(current->left != NULL) {
    current = current->left;
  }
  return current;
}

//Search Function
node* search(node* head, int element) {
  //If the head is NULL, that means we reached a dead end and the element wasn't in the tree
  if(head == NULL) {
    return NULL;
  }
  //If the head is equal to the element, return head
  else if (head->data == element) {
    return head;
  }
  //If head is greater, then search right side
  else if(head->data < element) {
    return search(head->right, element);
  }
  //If head is less, then search left side
  else {
    return search(head->left, element);
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
      node* swapChild = current->right;

      current->right = parent;
      grandparent->right = current;
      parent->left = swapChild;
      if(swapChild != NULL) {
	swapChild->parent = parent;
      }
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
  if(parent->left == current) {
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
