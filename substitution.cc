using namespace std;

// a struct to hold the substitutions
struct subs{
  string old;
  string new;
};

// a list node
struct node{
  subs * sub;
  node * next;
};

struct slist{
  node* head;
  node* tail;
};

// delete the singly linked list and all the substitution structs within it
void delete_list(slist * list){
  for (; list; list = )
}

// apply all changes to the source text
void apply(){}

int main(){}
