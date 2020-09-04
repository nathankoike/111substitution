#include <cstdlib>
#include <iostream>
using namespace std;


// a struct to hold the substitutions
struct subs{
  string old = "";
  string replace = "";
};

// a list node
struct node{
  subs * sub  = NULL;
  node * next = NULL;
};

// implement a list
struct slist{
  node* head = NULL;
  node* tail = NULL;

  // remove the first node in the list
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

  // add a new node to the front of the list
  void add(subs * sub){
    // make a new node
    node * new_head =new node;

    // set the necessary values
    new_head -> next = this -> head;
    new_head -> sub = sub;

    // set the head of the list to be the
    this -> head = new_head;
  }
};

// delete the singly linked list and all the substitution structs within it
void delete_list(slist * list){
  for (; list; list->pop());
}

// apply all changes to the source text
void apply(){}

int main(){}
