#include <iostream>
#include <cstring>

using namespace std;

struct token {
  char value;
  bool isNumber;
  int precedence;
  token(char newData) {
    value = newData;
    isNumber = false;
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
    data = data;
    left = NULL;
    right = NULL;
  }
};

token* createToken(char ch);
token* pop(stackNode* &stack);
void push(stackNode* &stack, token* newToken);
token* peak(stackNode* stack);
void enqueue(queueNode* &queue, token* newToken);
token* dequeue(queueNode* &queue);
void print(queueNode* current);
void print(stackNode* current);
void getInput();

int main() {
  cout << "START" << endl;
  stackNode* stack = NULL;
  queueNode* queue = NULL;
  queueNode* infix = NULL;
  queueNode* postfix = NULL;
  queueNode* prefix = NULL;
  print(queue);
  cout << endl;
  
}


void getInput() {
  char* input = new char[100];
  cin.get(input, 100);
int length = strlen(input);
}



























void print(queueNode* queue) {
  while(queue != NULL) {
    cout << queue->data->value << ' ';
    queue = queue->next;
  }
}

void print(stackNode* stack) {
  while(stack != NULL) {
    cout << stack->data->value << ' ';
    stack = stack->next;
  }
}

token* peak(stackNode* stack) {
  return stack->data;
}

token* pop(stackNode* &stack) {
  token* popToken = stack->data;
  stackNode* toDelete = stack;
  stack = stack->next;
  delete toDelete;
  return popToken;
}

void push(stackNode* &stack, token* newToken) {
  stackNode* newNode = new stackNode(newToken);
  newNode->next = stack;
  stack = newNode;
}

void enqueue(queueNode* &queue, token* newToken) {
  if(queue != NULL) {
    enqueue(queue->next, newToken);
  }
  else {
    queueNode* newNode = new queueNode(newToken);
    queue = newNode;
  }
}

token* dequeue(queueNode* &queue) {
  queueNode* toDelete = queue;
  token* out = queue->data;
  queue = queue->next;
  delete toDelete;
  return out;
}



token* createToken(char ch) {
  token* newToken = new token(ch);
  if(ch == '+' || ch == '-') {
    //newToken->isNumber = false;
    newToken->precedence = 1;
  }
  else if(ch == '*' || ch == '/') {
    newToken->precedence = 2;
  }
  else if(ch == '^') {
    newToken->precedence = 3;
  }
  else if(ch == '(' || ch == ')') {
    newToken->precedence = 4;
  }
  else {
    newToken->isNumber = true;
  }
  return newToken;

}











