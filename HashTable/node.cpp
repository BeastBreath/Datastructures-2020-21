#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

node::node() {
  data = NULL;
  next = NULL;
}

node::node(student* newStudent) {
  data = newStudent;
  next = NULL;
}

student* node::getStudent() {
  return data;
}

void node::getStudent(student* newStudent) {
  data = newStudent;
}

node* node::getNext() {
  return next;
}

void node::setNext(node* newNext) {
  next = newNext;
}

node::~node() {
  delete data;
  delete next;
}
