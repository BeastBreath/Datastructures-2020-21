#include <iostream>
#include <cstring>
#include <ctype.h>

using namespace std;

//Token struct that makes it easier to work with numbers and operators and precedence and more information
struct token {
  char oper;
  int number;
  bool isNumber;
  int precedence;
  //Constructor that also sets precedence value
  token(char newData) {
    oper = newData;
    isNumber = false;
    number = -1;
    char ch = newData;
    if(ch == '+' || ch == '-') {
      precedence = 1;
    }
    else if(ch == '*' || ch == '/') {
      precedence = 2;
    }
    else if(ch == '^') {
      precedence = 3;
    }
    else if(ch == '(' || ch == ')') {
      precedence = 4;
    }
    
  }
  token(int newData) {
    number = newData;
    isNumber = true;
    precedence = -1;
  }
  /*
    Precedence:
    1 + -
    2 * /
    3 ^
    4 ( )
   */
};

//Struct for stack node that just has a token and a pointer to the next item in the stack
struct stackNode {
  token* data;
  stackNode* next;
  stackNode() {
    data = NULL;
    next = NULL;
  }
  stackNode(token* newData) {
    data = newData;
    next = NULL;
  }
};

//Struct for the queue node. This is the exact same as the stackNode, but it makes it so that logical errors are turned into syntax errors and are easier to debug
struct queueNode {
  token* data;
  queueNode* next;
  queueNode() {
    data = NULL;
    next = NULL;
  }
  queueNode(token* newData) {
    data = newData;
    next = NULL;
  }
};

//Struct for binary tree nodes. They are the same as queue and stack nodes, except it has two child nodes instead of one
struct binaryNode {
  token* data;
  binaryNode* left;
  binaryNode* right;
  binaryNode() {
    data = NULL;
    left = NULL;
    right = NULL;
  }
  binaryNode(token* newData) {
    data = newData;
    left = NULL;
    right = NULL;
  }
};

//Function Prototypes
token* pop(stackNode* &stack);
void push(stackNode* &stack, token* newToken);
token* peak(stackNode* stack);
void enqueue(queueNode* &queue, token* newToken);
token* dequeue(queueNode* &queue);
void print(queueNode* current);
void print(stackNode* current);
void getInput(queueNode* &queue);
void inToPost(queueNode* &infix, queueNode* &postfix, stackNode* &stack);
binaryNode* postToBinaryTree(queueNode* &postfix);
void printInfix(binaryNode* binaryTree);
void printPostfix(binaryNode* binaryTree);
void printPrefix(binaryNode* binaryTree);
void printToken(token* current);
int evaluate(binaryNode* binaryTree);

//Main method
int main() {
  cout << "Welcome to Shunting Yard. In the year 1829, Scotland Yard was made the headquarters for London's Police. The computer science community tried to copy this. At the time, computer scientists were really jelous of people who worked with trains, so they decided to name it shunting yard, after the train shunting yards. Ofcourse, these computer scientists weren't even born yet, so this whole story is made up because I have way too much time on my hand" << endl;
  cout << "Your commands are: CHANGE INFIX POSTFIX PREFIX EVALUATE HELP QUIT" << endl;
  cout << "Please enter your original function in infix notation" << endl;

  //Setting up stacks and queues
  stackNode* stack = NULL;
  queueNode* infix = NULL;
  queueNode* postfix = NULL;

  //Gets input for the first time
  cout << "> ";
  getInput(infix);
  inToPost(infix, postfix, stack);
  cout << "Postfix: ";
  print(postfix);//Prints out the postfix form using the queue
  cout << endl;
  binaryNode* binaryTree = postToBinaryTree(postfix);//Creates the binary tree

  //Loop for the program
  bool going = true;
  while(going) {
    cout << "> ";
    char input[20];
    cin.get(input, 19);
    cin.get();
    //if the user entered change, we get a new input, convert it to postfix, and print the binary tree
    if(strcmp(input, "CHANGE") == 0) {
      cout << "What would you like the new infix to be? ";
      getInput(infix);
      inToPost(infix, postfix, stack);
      binaryTree = postToBinaryTree(postfix);
    }
    //If the user types infix, we print in infix notation
    else if(strcmp(input, "INFIX") == 0) {
      cout << "INFIX: ";
      printInfix(binaryTree);
      cout << endl;
    }
    //If the user types postfix, we print in postfix notation
    else if(strcmp(input, "POSTFIX") == 0) {
      cout << "POSTFIX: ";
      printPostfix(binaryTree);
      cout << endl;
    }
    //If the user types prefix, we print in prefix notation
    else if(strcmp(input, "PREFIX") == 0) {
      cout << "PREFIX: ";
      printPrefix(binaryTree);
      cout << endl;
    }
    //If the user types evaluate, we evaluate the expression
    else if(strcmp(input, "EVALUATE") == 0) {
      cout << "This function evaluates to: ";
      cout << evaluate(binaryTree) << endl;
    }
    //If user types help, we print the help message
    else if(strcmp(input, "HELP") == 0) {
      cout << "HERE ARE YOUR COMMANDS: " << endl;
      cout << "Change - Change your original expression" << endl;
      cout << "Infix - Print the infix expression" << endl;
      cout << "Postfix - Print the postfix expression" << endl;
      cout << "Prefix - Print the prefix expression" << endl;
      cout << "Evaluate - Evaluates your expression" << endl;
      cout << "I hope this helped. If it didn't help, please email: unknown error occured no one wanted to give you thier email because they feel that you are untrustworthy (You can tell that I am really bored writing this program)" << endl;
    }
    //If the user types quit, we quit the program
    else if(strcmp(input, "QUIT") == 0) {
      going = false;
    }
  }
}

//Evaluate function
int evaluate(binaryNode* binaryTree) {
  //If there is nothing in the tree, we return zero
  if(binaryTree == NULL) {
    return 0;
  }
  //If there is a number (meaning it is a leaf), we return the number
  else if(binaryTree->data->isNumber) {
    return (binaryTree->data->number);
  }
  //If it is a operator, we simply use recursion to follow the right and left childs down
  int leftValue = evaluate(binaryTree->left);
  int rightValue = evaluate(binaryTree->right);
  char oper = binaryTree->data->oper;
  //If the operator is a +, we add what we got from both children
  if(oper == '+') {
    return (leftValue + rightValue);
  }
  //If the operator is a -, we subtract what we got from both children
  if(oper == '-') {
    return (leftValue - rightValue);
  }
  //If the operator is a /, we divide what we got from both children
  if(oper == '/') {
    return (leftValue / rightValue);
  }
  //If the operator is a *, we multiply what we got from both children
  if(oper == '*') {
    return (leftValue * rightValue);
  }
  //If the operator is ^, we multiply 1 by the left child the right child number of times
  if(oper == '^') {
    int ans = 1;
    for(int i = 0; i < rightValue; i++) {
      ans *= leftValue;
    }
    return ans;
  }
}

//This prints the tree in infix notation
void printInfix(binaryNode* binaryTree) {
  //If the binary tree isn't empty, we keep going
  if(binaryTree != NULL){
    //If the node is an operator, we print an open parenthesis
    if(!(binaryTree->data->isNumber)) {
      cout << "( ";
    }
    printInfix(binaryTree->left);//We print everything to the left of the node
    printToken(binaryTree->data);//We print the current operator or number
    printInfix(binaryTree->right);//We print everything to the right of the node
    //We print a close parenthesis if it is an operator
    if(!(binaryTree->data->isNumber)) {
      cout << ") ";
    }
  }
}

//This prints the tree in postfix notation
void printPostfix(binaryNode* binaryTree) {
  if(binaryTree != NULL) {
    printPostfix(binaryTree->left);//Prints everything to the left
    printPostfix(binaryTree->right);//Prints everything to the right of the node
    printToken(binaryTree->data);//Prints the operator or number
  }
}

//Prints in prefix form
void printPrefix(binaryNode* binaryTree) {
  if(binaryTree != NULL) {
    printToken(binaryTree->data);//Prints the current operator or number
    printPrefix(binaryTree->left);//Prints everything to the left
    printPrefix(binaryTree->right);//Prints everything to the right
  }
}

//Prints what is at a token. We need this because a different variable stores numbers and a different variable stores operators
void printToken(token* current) {
  if(current->isNumber) { cout << current->number << ' ';}
  else { cout << current->oper << ' ';}
}

//Converts postfix notation to binary tree
binaryNode* postToBinaryTree(queueNode* &postfix) {
  //We implement a stack using a array for this for simplicity's sake
  int size = 50;//Size of the whole stack
  int currentSize = 0;//Size that the stack currently is
  binaryNode** stack = new binaryNode*[size];//Creates a stack for the binary nodes
  //While the postfix queue isn't empty, we keep reading
  while(postfix != NULL) {
    token* current = dequeue(postfix);//Takes the token and dequeues a node from the queue
    //If it is a number, we put it straight into the stack (first by creating a binaryNode for it)
    if(current->isNumber) {
      stack[currentSize] = new binaryNode(current);
      currentSize++;
    }
    //Otherwise, we take the first two items on the stack, and put make them the left and right children of a new binary tree, and make our operator a new node and push our new operator into the tree
    else {
      binaryNode* newNode = new binaryNode(current);
      newNode->right = stack[currentSize-1];
      currentSize--;
      newNode->left = stack[currentSize-1];
      currentSize--;
      stack[currentSize] = newNode;
      currentSize++;
    }
  }
  //If the size of the stack isn't one, then we have an error but this should never happen, so who knows whats happening if the program goes here
  if(currentSize != 1) {
    cout << "Unknown error this sucks" << endl;
  }
  return stack[0];//We return the one head node
}

//Converts from infix form to post fix form
void inToPost(queueNode* &infix, queueNode* &postfix, stackNode* &stack) {
  //We keep going while there are tokens to be read
  while(infix !=NULL) {
    token* current = dequeue(infix);
    //If it is a number, then we just add the token to the postfix queue
    if(current->isNumber) {
      enqueue(postfix, current);
    }
    //Otherwise, if its an operator (not a parentheis), we keep going until we find something with an equal or lower precdence (and some other rules), and take it out of the stack and put it into the queue
    else if(current->precedence >= 1 && current->precedence <= 3) {
      while((stack != NULL) && ((peak(stack)->precedence != 4) && ((peak(stack)->precedence > current->precedence) || ((peak(stack)->precedence == current->precedence) && (current->oper != '^'))))) {
	enqueue(postfix, pop(stack));
      }
      push(stack, current);//Finally we push the current operator into the stack
    }
    //If its a left parenthesis, we just push it to the stack
    else if(current->oper == '(') {
      push(stack, current);
    }
    //If its a right parenthesis, we keep moving stuff from the stack to the queue until we reach the other parnethesis and we discard both parenthesis
    else if (current->oper == ')') {
      while(peak(stack)->oper != '(') {
	enqueue(postfix, pop(stack));
      }
      if(peak(stack)->oper == '(') {
	delete pop(stack);
	delete current;
      }
    }
  }
  //Finally, we clear the stack and move everything to the queue
  if(infix == NULL) {
    while(stack != NULL) {
      enqueue(postfix, pop(stack));
    } 
  }
}

//This function gets the input from the user
void getInput(queueNode* &infix) {
  char* input = new char[100];
  cin.get(input, 100);
  cin.ignore();
  int length = strlen(input);
  //We keep going through the array while we have more charectors to read
  for (int i = 0; ((input[i] != '\0') && (i < length)); i++) {
    //If it's a charector and not a space, we create a new token and add it to the queue
    if(!isdigit(input[i]) && input[i] != ' ') {
      enqueue(infix, new token(input[i]));
    }
    //Otherwise if its a number, we: keep reading until we reach something thats not a number, and we put the charectors together into a number
    else if(input[i] != ' ') {
      int number = 0;
      while(input[i] != ' ' && input[i] != '\0') {
	number *=10;
	int temp = ((int)input[i]) - '0';
	number += temp;
	i++;
      }
      enqueue(infix, new token(number));
    }
  }
}

//Print function for the queue (used for debugging and printing the postfix notation in the beggining)
void print(queueNode* queue) {
  //We keep going in the queue and print tokens while we have nodes to read
  while(queue != NULL) {
    printToken(queue->data);
    queue = queue->next;
  }
}

//Print function for the stack (used for debugging)
void print(stackNode* stack) {
  //We keep going while we have more nodes and print the token, and we go to the next node
  while(stack != NULL) {
    printToken(stack->data);
    stack = stack->next;
  }
}

//Peak function for stacks
token* peak(stackNode* stack) {
  //We just return the token of the first node
  return stack->data;
}

//Pop function for stacks
token* pop(stackNode* &stack) {
  //We set the stack pointer to the second node, delete the old first node, and return the token
  token* popToken = stack->data;
  stackNode* toDelete = stack;
  stack = stack->next;
  delete toDelete;
  return popToken;
}

//Push function for stacks
void push(stackNode* &stack, token* newToken) {
  //We create a new node and put it in front of the line
  stackNode* newNode = new stackNode(newToken);
  newNode->next = stack;
  stack = newNode;
}

//Enqueue Function for queues
void enqueue(queueNode* &queue, token* newToken) {
  //If there is something in the queue, we call the function again, except with the next node in the list
  if(queue != NULL) {
    enqueue(queue->next, newToken);
  }
  //If we have reached the last node, then we just create a new node and set the previous node's pointer to point to this node
  else {
    queueNode* newNode = new queueNode(newToken);
    queue = newNode;
  }
}

//Dequeue function for queues
token* dequeue(queueNode* &queue) {
  //We want to delete the first one in the list, so first we store that one, then we change our queue pointer to point to the second one, and then we save the token, and last we delete the node
  queueNode* toDelete = queue;
  token* out = queue->data;
  queue = queue->next;
  delete toDelete;
  return out;
}
