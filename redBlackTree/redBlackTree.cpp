#include <iostream>
#include <cstring>

using namespace std;

#define BLACK true
#define RED false

struct node {
  node* left, right, parent;
  int data;
  bool color;
  
  node(int newData){
    color = RED;
    data = newData;
    left = NULL;
    right = NULL;
    parent = NULL;
  }
  node() {
    color = RED;
    data = -1;
    left = NULL;
    right = NULL;
    parent = NULL;
  }
};

struct family {
  node* greatgrandparent;
  node* grandparent;
  node* parent;
  node* uncle;
  node* sibling;
  node* current;
  family(node* newCurrent) {
    greatgrandparent = NULL;
    grandparent = NULL;
    parent = NULL;
    uncle = NULL;
    sibling = NULL;
    current = newCurrent;
  }
};

int main() {
  node* head = NULL;
}
