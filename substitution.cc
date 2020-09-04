#include <cstdlib>
#include <iostream>
using namespace std;

// a struct to hold the substitutions
struct subs{
  string old = "";
  string replacement = "";
};

// a list node
struct node{
  subs * sub  = NULL;
  node * next = NULL;
};

// implement a list
// this should be a class but im lazy
struct slist{
  node* head = NULL;
  node* tail = NULL;

  // remove the first node in the list
  void pop(){
    // save the next head value
    node * tmp = this->head->next;

    // delete the substitution in the head
    delete this->head->sub;

    // delete the struct at the head
    delete this->head;

    // move the head pointer to the first node in the list
    this->head = tmp;
  }

  // add a new node to the front of the list
  void add(subs * sub){
    // make a new node
    node * new_head = new node;

    // set the necessary values
    new_head->next = this->head;
    new_head->sub = sub;

    // set the head of the list to be the
    this->head = new_head;
  }
};

// delete the singly linked list and all the substitution structs within it
void delete_list(slist * & list){
  for (; list->head; list->pop());
}

// =============================================================================
// =============================== FUNCTIONS ===================================
// =============================================================================

// replace a word at index i with the substitution
void replace(const subs *& sub, string & src, const size_t & i){}

// find a word that needs to be replaced
void find_word(string & src){}

// apply all changes to the source text
void apply(slist * replacements, string & src){}

// split a string at the token
string split(string src, const char & tok){
  // the string up to the token
  string sp = "";

  for (size_t i = 0; i < src.length(); i++){
    // if we are looking at the token
    if (src[i] == tok)
      break;

    // add the character to the string
    sp += src[i];
  }

  return sp;
}

// make a subs struct from the provided string
subs * make_sub(string sub){
  // make the struct
  subs * new_sub = new subs;

  // save the old sub
  string old = split(sub, '/');

  // assign the old and replacement strings
  new_sub->old = old;
  new_sub->replacement = sub.substr(old.length() + 1);

  return new_sub;
}

// separate the substitutions into structs and return the list of substitutions
slist * get_subs(string substitutions){
  // make a list
  slist * list = new slist;

  // get the first substitution to make
  string sub = split(substitutions, ':');

  // run until there is only one substitution pair left to make
  while (sub != substitutions){
    // make and add the substitution to the list
    list->add(make_sub(sub));

    // remove the old substitution
    substitutions = substitutions.substr(sub.length() + 1);

    // get a new substitution
    sub = split(substitutions, ':');
  }

  // add the last substitution
  list->add(make_sub(sub));

  // return the list
  return list;
}

// get an input that includes newlines
void get_input(string & target){
  // the last and second to last characters
  char last = cin.get();
  char slast;

  // end on 2 newlines
  while (last != slast || slast != '\n'){
    target += last;
    slast = last;
    last = cin.get();
  }
}

int main(){
  string substitutions = "";
  string src = "";

  cin >> substitutions;

  get_input(src);

  // get the replacements
  slist * replacements = get_subs(substitutions);

  // delete the replacements
  delete_list(replacements);

  // print the replacements
  for (node * f = replacements->head; f; f = f->next)
    cout << f->sub->old << " " << f->sub->replacement << endl;
}
