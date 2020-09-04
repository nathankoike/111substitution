#include <cstdlib>
#include <iostream>
using namespace std;


// a struct to hold the substitutions
struct subs{
  string old;
  string replace;
};

// a list node
struct node{
  subs * sub;
  node * next;
};

struct slist{
  node* head;
  node* tail;

  void pop(){
    // save the next head value
    node * tmp = this -> head -> next;

    // delete the substitution in the head
    delete this -> head -> sub;

    // delete the struct at the head
    delete this -> head;

    // move the head pointer to the first node in the list
    this -> head = tmp;
  }
};

// delete the singly linked list and all the substitution structs within it
void delete_list(slist * list){
  for (; list; list = NULL);
}

// apply all changes to the source text
void apply(){}

int main(){}
