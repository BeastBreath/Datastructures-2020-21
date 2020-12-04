#include<iostream>
#include<cstring>
#include<fstream>


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
#define COUNT 10

node** search(node* &head, int element);
void insert(node* &head, int element);
void deleteElement(node* &head, int element);
void printDUtil(node* root, int size);
void print2D(node* root);


int main() {
  cout << "Welcome to Binary Search Tree. Your commands are ADD, DELETE, SEARCH, PRINT, and QUIT" << endl;

  node* head = NULL;
  char input[20];
  bool going = true;

#ifdef DEBUG
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



  
  print2D(head);
  int inputs;
  cin >> inputs;
  cin.get();
  deleteElement(head, inputs);
  print2D(head);

#endif
  
  while(true){
    cout << "> ";
    cin.get(input, 19);
    cin.get();
    
    if(strcmp(input, "ADD") == 0) {
      cout << "ADD" << endl;
      int element;
      cin >> element;
      cin.get();
      insert(head, element);
    }
    else if(strcmp(input, "SEARCH") == 0) {
      cout << "SEARCH" << endl;
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
    else if(strcmp(input, "DELETE") == 0) {
      cout << "DELETE" << endl;
      int element;
      cin >> element;
      cin.get();
      deleteElement(head, element);
    }
    else if(strcmp(input, "PRINT") == 0) {
      cout << "PRINT" << endl;
      print2D(head);
    }
    else if(strcmp(input, "QUIT") == 0) {
      cout << "QUIT" << endl;
      going = false;
    }

    
  }
    

}


node** search(node* &head, int element) {
  if(head == NULL) {
    return NULL;
  }
  if(head->data == element) {
    return (&head);
  }
  if(head->data < element) {
    node** ret = search(head->right, element);
    return (ret);
  }
  if(head->data > element) {
    return (search(head->left, element));
  }
  cout << "Unknown error occurred" << endl;  
}

void insert(node* &head, int element) {
#ifdef DEBUG
  cout << "IN INSERT" << element << endl;
#endif
  if(head == NULL) {
#ifdef DEBUG
    cout << "IN INSERT NULL" << endl;
#endif

    head = new node(element);
  }
  else if(head->data > element) {
#ifdef DEBUG
    cout << "IN INSERT data>element" << endl;
#endif

    insert(head->left, element);
  }
  else {
#ifdef DEBUG
    cout << "IN INSERT data >=element" << endl;
#endif
    insert(head->right, element);
  }
}


void deleteElement(node* &headA, int element) {

  node** headR = search(headA, element);
  if(headR == NULL) {
    cout << "NODE NOT FOUND" << endl;
    return;
  }
  node* head = (*headR);
  if(head == NULL) {
    cout << "SDF" << endl;
  }
#ifdef DEBUG
  cout << "BREAK POINT 1" << endl;
#endif
  if(head->right == NULL && head->left == NULL) {
#ifdef DEBUG
    cout << "Delete element end" << endl;
#endif
    (*headR) = NULL;
    return;
  }
#ifdef DEBUG
  cout << "breakpoint 2" << endl;
#endif
  if(head->right == NULL) {
#ifdef DEBUG
    cout << "RIGHT NULL" << endl;
#endif
    (*headR) = head->left;
    return;
  }
#ifdef DEBUG
  cout << "BREAKPOINT 3" << endl;
#endif
  if(head->left == NULL) {
#ifdef DEBUG
    cout << "LEFT NULL" << endl;
#endif
    (*headR) = head->right;
    return;
  }
  #ifdef DEBUG
  cout << "Breakpoint 4" << endl;
#endif



  node* replaceElement = head->left;
  node** previous = &(head->left);
#ifdef DEBUG
  cout << "Breakpoint 5" << endl;
  if(replaceElement == NULL) {
    cout << "NNNUULLL" << endl;
  }
  cout << replaceElement->data << endl;
#endif
  
  while(replaceElement->right != NULL) {
    replaceElement = replaceElement->right;
    previous = &((*previous)->right);
  }
  cout << (*previous)->data << endl;
  (*previous) = ((*previous)->left);
  (*headR)->data = replaceElement->data;
}

void print2DUtil(node *root, int space)  
{  
    // Base case  
    if (root == NULL)  
        return;  
  
    // Increase distance between levels  
    space += COUNT;  
  
    // Process right child first  
    print2DUtil(root->right, space);  
  
    // Print current node after space  
    // count  
    cout<<endl;  
    for (int i = COUNT; i < space; i++)  
        cout<<" ";  
    cout<<root->data<<"\n";  
  
    // Process left child  
    print2DUtil(root->left, space);  
}  
  
// Wrapper over print2DUtil()  
void print2D(node *root)  
{  
    // Pass initial space count as 0  
    print2DUtil(root, 0);  
}  
