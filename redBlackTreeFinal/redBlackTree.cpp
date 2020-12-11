#include <iostream>
#include <string.h>

using namespace std;

#define BLACK true
#define RED false
#define RIGHT 1
#define LEFT 2
#define COUNT 10

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

node* insert (node* &head, int element, int side);
node* callInsert (node* &head, int element);
bool getColor(node* current);
node* getSibling(node*current);
node* getUncle(node* current);
void print(node* head, int size);
void fixTree(node* &head, int element);

int main() {
node* head = NULL;
 
 fixTree(head, 1);
 print(head, 0);
 
}

void fixTree(node* &head, int element) {
  node* current = callInsert(head, element);
  
  if(head == current) {
    current->color = BLACK;
    return;
  }

  if((getColor(current->parent) == RED) && (getColor(getUncle(current)) == BLACK)) {
    //Triangle
    
    if(current->data >= current->parent->data && current->parent->parent->data >= current->parent->data) {
      node* parent = current->parent;
      node* grandparent = current->parent->parent;

      current->left = parent;
      grandparent->left = current;
      parent->right = NULL;
      parent->parent = current;
      current->parent = grandparent;
      current = parent;
    }
    else if(current->data < current->parent->data && current->parent->parent->data < current->parent->data) {
      node* parent = current->parent;
      node* grandparent = current->parent->parent;
      
      current->right = parent;
      grandparent->right = current;
      parent->left = NULL;
      parent->parent = current;
      current->parent = grandparent;
      current = parent;
    }

    /*
      G (B)
            P(R)
	         C(R)

     */
    if(current >= current->parent && current >= current->parent->parent) {
      node* siblingD = getSibling(current);
      node* grandparentB = current->parent->parent;
      node* parentA = current->parent;
      parentA->left = grandparentB;
      grandparentB->right = siblingD;
      siblingD->parent = grandparentB;
      if(grandParentB == head) {
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
