/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: <your class>
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			dictionary.cpp
 * Author:			P. Bauer
 * Due Date:		November 25, 2012
 * ----------------------------------------------------------
 * Description:
 * Implementation of dictionary.h.
 * ----------------------------------------------------------
 */
#include "dictionary.h"
#include <stdlib.h>
#include <ctype.h> //for tolower()
#include <strings.h>

struct NodeImplementation{
  const char *word;
  Node next;
};

struct DictionaryImplementation{
  int length;
  Node head;
  Node actualIterating;
  Node tail;
};

Dictionary new_dictionary(){
  Dictionary dictionary = (Dictionary) malloc(sizeof(struct DictionaryImplementation));
  dictionary->length = 0;
  dictionary->head = 0;
  //
  dictionary->actualIterating = 0;
  dictionary->tail = 0;
  //
  return dictionary;
}

void delete_dictionary(Dictionary dictionary){
  Node current = dictionary->head;
  while(current != 0){
    sfree(current);
    current = current->next;
  }
  sfree(dictionary);
}

void add(Dictionary dict, const char *word){
  Node current = dict->head;
  Node new_node = (Node) malloc(sizeof(struct NodeImplementation));
  new_node->word = word;
  new_node->next = 0;
  if(dict->head == 0){
    dict->head = new_node;
    dict->length++;
    return;
  }

  while(current->word != word && current->next != 0){
    current = current->next;
  }

  if(current->word == word){
    return;
  }
  else{
    current->next = new_node;
    dict->length++;
  }

  //
  dict->tail = new_node;
}

int get_size(Dictionary dict){
  return dict->length;
}

bool is_in_dict(Dictionary dict, const char *word){
  if(dict->head == 0){
    return false;
  }
  Node current = dict->head;

  while(strcasecmp(current->word, word) != 0 && current->next != 0){
    current = current->next;
  }
  if(strcasecmp(current->word, word) == 0){
    return true;
  }
  else{
    return false;
  }
  return false;
}

void start_iterating(Dictionary dict){
  dict->actualIterating = dict->head;
}

bool has_next(Dictionary dict){
  // //dict->tail->next = 0;
  // if(dict->actualIterating == dict->tail){  //sollte tail+1 sein, aber core dumped
  //   return false;
  // }

  //lined-in the next 3 Lines
  if(dict->actualIterating != 0){ //change the if-Condition
    return true;
  }

  return false;
}

const char *get_next_entry(Dictionary dict){
  // Node temp = (Node) malloc(sizeof(struct NodeImplementation));
  // temp->word = dict->actualIterating->word;
  // temp->next = 0;
  // dict->actualIterating = dict->actualIterating->next;
  // return temp->word;

  if(has_next(dict)){ //added the if + content
    const char* word = dict->actualIterating->word;
    dict->actualIterating = dict->actualIterating->next;
    return word;
  }

  return 0;
}

void insert_sorted(Dictionary dict, const char *word){
  Node current = dict->head;
  Node new_node = (Node) malloc(sizeof(struct NodeImplementation));
  new_node->word = word;
  new_node->next = 0;
  if(dict->head == 0){ //chaged the content from the if (lined-out one line and added one line)
    //dict->head = new_node;
    add(dict, word);
  }
  else{ //added the else + content
    if(is_in_dict(dict, word)){
      return;
    }

    if(strcasecmp(dict->head->word, word) > 0){
      new_node->next = dict->head;
      dict->head = new_node;
      dict->length++;
    }
    else{
      while(current->next != 0 && strcasecmp(current->next->word, word) < 0){
        current = current->next;
      }
      if(current->next == 0){
        add(dict, word);
      }

      if(strcasecmp(current->next->word, word) > 0){
        new_node->next = current->next;
        current->next = new_node;
        dict->length++;
      }
    }
  }
  /*while(current->next > current){
    Node temp = (Node) malloc(sizeof(struct NodeImplementation));
    temp = current->Next;
    current->next = new_node;
    new_node->next = temp;
    dict->length++;
  }
  */
}
