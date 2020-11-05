/*******************
  Gary Allen
  grallen117
*******************/
#include <iostream>
#include <string.h>
#include <assert.h>
#include "stringset.h"

using namespace std;

/* Return a hash for the string s in the range 0..table_size-1 */
int myhash(string s, int table_size)
{
  unsigned int i, h = 0;
  for (i=0; i<s.length(); i++)
    h = (h * 2917 + (unsigned int)s[i]) % table_size;
  return h;
}

Stringset::Stringset()
{
  size = 4; // initial size of table
  table = new Node *[size]; // allocate table, initialize head ptrs all to NULL
  for (int i=0; i<size; i++)
    table[i] = NULL;
  num_elems = 0;
}

Stringset::~Stringset()
{
  for (int i=0; i<size; i++) {
    while (table[i] != NULL) {
      Node *temp = table[i];
      table[i] = table[i]->next;
      delete temp;
    }
  }
  delete[] table;
}

/* Return true if key is in the set */
bool Stringset::find(string key)
{
  int h = myhash(key, size);
  Node *n = table[h];
  while (n != NULL) {
    if (n->key == key) return true;
    n = n->next;
  }
  return false;
}

/* Inserts a new key.  It is an error if key is already in the set. */
void Stringset::insert(string key)
{
  assert (!find(key));
  num_elems++;
  Node *curr, *prev;
  if (num_elems == size) {
    Node ** temp;
    //create a new table called temp, with double the size allocated
    //relative to the size of the original table
    temp = new Node *[size * 2];
    //loop through the original table
    for (int i=0; i<size; i++) {
      //set curr equal to the head node at each position
      curr = table[i];
      //loop through each linked list to generate new hash for new list, as
      //size will be different and thusly will distribute the old strings
      //in new positions
      while (curr != NULL) {
        //generate new hash key based on current positions key and new size
        int z = myhash(curr->key, size*2);
        //if there is already a head of a LL in that position
        if (temp[z] != NULL) {
          //create a new node, set its key equal to the key in the original
          //table, and make its next equal to the previous head
          temp[z] = new Node(curr->key, temp[z]);
        }
        //if there is not a head of a LL in that position
        else {
          //create a new node, set its key equal to the key in the original
          //table, and make its next NULL
          temp[z] = new Node(curr->key, NULL);
        }
        //set prev equal to curr (the old head)
        prev = curr;
        //set curr to next to continue to loop through curr LL
        curr = curr -> next;
        //now delete prev as it is no longer needed
        delete(prev);
      }
    }
    //now done hashing to table with new size, delete table
    delete[] table;
    //make table equal to the new table created previously
    table = temp;
    //make size larger to account for new size of array
    size = size * 2;



  }
  //hash based on size of array and the key desired
  int h = myhash(key, size);
  //insert that key at the hashed position as a new head, effectively pushing
  //the list back
  table[h] = new Node(key, table[h]);
  //cout << "inserting " << key << " at position " << table[h] << "\n";

}


void Stringset::remove(string key)
{
  assert (find(key));
  num_elems--;
  //ensure the key actually exists in structure before running through process
  if (find(key) == true) {
    //get hash of the key using size of table and the key itself
    int h = myhash(key, size);
    //curr will be equal to the head of the linked list at the hash position
    //prev will be the position behind curr so we can replace its next
    Node *curr = table[h], *prev;
    //if the key is the head, the basic condition, no need to loop if so
    if (curr->key == key) {
      table[h] = curr->next;
      delete (curr);
    }
    else {
      //if key is not head, continue down the LL
      while (curr!=NULL && curr->key!=key) {
        prev = curr;
        curr = curr -> next;
      }
      //if statement to ensure the key has been found by the while loop
      //this condition will be entered if the found string is in the middle
      //of the linked list
      if (curr->key == key && curr->next != NULL) {
        prev->next = curr->next;
        delete (curr);
      }
      //if statement again, but this one is for the last condition being that
      //the found string is at the end of the list. If it is at the end of the
      //list, all we have to do is say the previous position's next is NULL
      //rather than being pointed to current's next. It still probably would
      //work with the previous comparison, but this will ensure that no bugs
      //happen
      else if (curr->key == key && curr ->next == NULL) {
        prev->next = NULL;
        delete(curr);
      }
    }

  }
  else {
    //do nothing if key is not in list
  }




}

void Stringset::print(void)
{

  //initialize current to NULL
  Node * current = NULL;
  //loop for the size of the hash table
  for (int i = 0; i < size; i++) {
    //set current equal to head of position i of hash table
    current = table[i];
    //while current is not NULL, meaning it has not reached the end of hash
    //table
    while (current != NULL) {
      //print current key
      cout << current->key << "\n";
      //send current onwards down the LL until it reaches NULL, then restart
      current = current -> next;
    }
  }




}
