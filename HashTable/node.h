File Edit Options Buffers Tools C++ Help
#include <iostream>
#include <cstring>
#include "student.h"

using namespace std;

#ifndef NODE_H
#define NODE_H

class node {
 public:
  node();
  node(student* newStudent);
  student* getStudent();
  void getStudent(student* newStudent);
  node* getNext();
  void setNext(node* newNext);
  ~node();
 private:
  student* data;
  node* next;
};
#endif
