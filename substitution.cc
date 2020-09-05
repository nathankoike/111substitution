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

// convert a string entirely to lowercase letters
string to_lower(const string & s){
  // this will be or lowercase string
  string lower = "";

  // get the distance between uppercase and lowercase letters
  int distance = 'a' - 'A';

  // index the string
  for (size_t i = 0; i < s.length(); i++){
    if (s[i] <= 'Z') // if s[i] is an uppercase letter
      lower += (s[i] + distance); // add the distance and make it lowercase
    else
      lower += s[i];
  }

  return lower;
}

// replace a word while also respecting capitalization
void replace(string & sentence, string word, subs * & sub, bool & r){
  // if we need to replace the word exactly
  if (word == sub->old){
    sentence += sub->replacement;
    r = true; // mark the word as replaced
    return;
  }

  // we need to do some capitalization checking
  if (to_lower(word) == sub->old){
    // this will be or lowercase string
    string replacement = "";

    // get the distance between uppercase and lowercase letters
    int distance = 'a' - 'A';

    // we need to consider a difference in length
    size_t i = 0;

    // if the word is shorter than the replacement
    if (word.size() < sub->replacement.size()){
      // index the word
      for (; i < word.length(); i++){
        // if s[i] is an uppercase letter
        if (word[i] <= 'Z')
          // add the distance and make it uppercase
          replacement += (sub->replacement[i] - distance);
        else
          replacement += sub->replacement[i];
      }

      // add the rest of the replacement
      for (; i < sub->replacement.size(); i++)
        replacement += sub->replacement[i];
    }

    else{
      // index the replacement
      for (; i < sub->replacement.length(); i++){
        // if s[i] is an uppercase letter
        if (word[i] <= 'Z')
          // add the distance and make it uppercase
          replacement += (sub->replacement[i] - distance);
        else
          replacement += sub->replacement[i];
      }
    }

    // add the replacement to the sentence
    sentence += replacement;
    r = true; // mark the word as replaced
  }
}

// apply all changes to a sentence
string apply_sentence(const slist * replacements, string src){
  // the sentence with replacements
  string sentence = "";

  // this is where we will store the first word in the sentence
  string word = "";

  // while there is a leading space, add the space to the returned sentence
  for (; src[0] == ' '; src = src.substr(1))
    sentence += ' ';

  // while the source is not empty
  for (; src != ""; src = src.substr(word.length())){
    // get the first word in the source
    word = split(src, ' ');

    // track replacement
    bool replaced = false;

    // for every possible substitution
    for (node * p = replacements->head; p; p = p->next){
      // potentially replace a word
      replace(sentence, word, p->sub, replaced);
    }

    // if the word hasnt been replaced, simply add it
    if (!replaced)
      sentence += word;

    // add a trailing space and remove the leading space from the source
    if (word != src){
      sentence += ' ';
      src = src.substr(1);
    }
  }

  return sentence;
}

// apply all changes to a line
string apply_line(const slist * replacements, string src){
  // this is the final result of the replacements
  string final = "";

  // this is where we will store the sentence
  string sentence = "";

  // while there is a leading period, add the space to the returned string
  for (; src[0] == '.'; src = src.substr(1))
    final += '.';

  // while the source is not empty
  for (; src != ""; src = src.substr(sentence.length())){
    // get the first word in the source
    sentence = split(src, '.');

    // aply all changes to the sentence
    final += apply_sentence(replacements, sentence);

    // add a trailing period
    if (sentence != src)
      final += '.';
  }

    return final;
}

// apply all changes to the source text
string apply(const slist * replacements, string src){
  // this is the final result of the replacements
  string final = "";

  // this is where we will store the sentence
  string line = "";

  // while the source is not empty
  for (; src != ""; src = src.substr(line.length() + 1)){
    // get the first word in the source
    line = split(src, '\n');

    // aply all changes to the sentence
    final += apply_line(replacements, line);

    // add a trailing newline
    if (line != src)
      final += '\n';
  }

  return final;
}

int main(){
  string substitutions = "";
  string src = "";

  cin >> substitutions;

  get_input(src);

  // get the replacements
  slist * replacements = get_subs(substitutions);

  // replace all the words
  src = apply(replacements, src);

  cout << src << endl;

  // delete the replacements
  delete_list(replacements);
}
