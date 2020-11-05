/*******************
  Gary Allen
  grallen117
  Lab #2
  Lab Section: CPSC 2121-003
  Completed On: 9/3/19
*******************/
#include <string>
#include <fstream>
#include <iostream>
#include "stringset.h"

using namespace std;

void spellcheck(void)
{
  Stringset S;
  string word;

  ifstream wordfile("words.txt");
  while (wordfile >> word)
    S.insert(word);
  wordfile.close();

  cout << "Dictionary loaded.  Please enter words to spell check.\n";

  while (cin >> word) {

    string pword = "abcdefghijklmnopqrstuvwxyz";
    string tempword;
    cout << "Possible alternatives for word '" << word << "':\n";

    for (int i = 0; i < word.length(); i++) {
      tempword = word;
      for (int j = 0; j < pword.length(); j++) {
        //changing tempword, which is word, one character at a time to all of
        //the lowercase letters of the alphabet from the variable pword
        tempword[i] = pword[j];
        //if a word with a single difference is found
        if (S.find(tempword)) {
          //first make sure it isn't the same word
          if (tempword == word) {
            //do nothing
          }
          //print out the word that was found
          else {
            cout << tempword << "\n";
          }
        }
      }
    }
  }
}

void test(void)
{
  Stringset S;
  string key, command;

  while(cin >> command) {

    if (command == "insert") {

      cin >> key;
      if (S.find(key))
	cout << "Error!  Key " << key << " already in structure!\n";
      else
	S.insert(key);

    } else if (command == "remove") {

      cin >> key;
      if (!S.find(key))
	cout << "Error!  Key " << key << " not in structure!\n";
      else
	S.remove(key);

    } else if (command == "find") {

      cin >> key;
      if (S.find(key))
	cout << "Key " << key << " present.\n";
      else
	cout << "Key " << key << " absent.\n";

    } else if (command == "print") {

      cout << "Contents of structure:\n";
      S.print();

    } else if (command == "quit") {

      break;

    } else {

      cout << "Error!  Unknown command '" << command << "'!\n";

    }
  }
}

int main(void)
{
  //test();
  spellcheck();
  return 0;
}
