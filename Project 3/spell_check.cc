// Jubayer Ahmed
/**
 * Simple spell checker that stores a subset of the english dictionary in a hashtable that implements
 * double hashing. A given document is passed in, parsed via file input and procsesed by supplmentary
 * functions. Given a word, the program will return whether it is correct (contained in dictionary)
 * or if it is incorrect. If it is incorrect, it will attempt 3 cases to find a word that matches
 * a word in the dictionary, by adding a letter (in each position), removing a letter (in each position),
 * or by swapping adjacent letters.
*/

#include <fstream>
#include <iostream>
#include <string>

// You can change to quadratic probing if you
// haven't implemented double hashing.
#include "double_hashing.h"
using namespace std;

// @param input_ string that holds word to be processed
// @returns word with all lowercase letters
string toLowerCaseWord(string input_) {
  string output_ = "";
  int string_length_ = input_.length(); // mitigate type casting errors in for loop comparison and compiler warnings
  
  for(int i = 0; i < string_length_; i++) {
    output_ += std::tolower(input_[i]);
  }

  return output_;
}

// @param input_ string that holds word to be processed
// @returns true if the string has a number, false if it doesn't have any digits
bool hasNumber(string input_) {
  int string_length_ = input_.length();

  for(int i = 0; i < string_length_; i++) {
    if(isdigit(input_[i])) {
      return true;
    }
  }

  return false;
}

// @param input_ string that holds word to be processed
// @returns true if the string has a dash, false if it doesn't have any dashes
bool hasDash(string input_) {
  int string_length_ = input_.length();

  for(int i = 0; i < string_length_; i++) {
    if(input_[i] == '-' || input_[i] == '_') {
      return true;
    }
  }

  return false;
}

// Creates and fills double hashing hash table with all words from
// dictionary_file
HashTableDouble<string> MakeDictionary(const string &dictionary_file) {
  HashTableDouble<string> dictionary_hash;

    string dict_line_;

    // account for non-existent file - covering edge case of file error
    std::ifstream fin(dictionary_file);
  	if (fin.fail()) {
    	std::cerr << "File cannot be opened for reading." << std::endl;
    	exit(1); // exit if failed to open the file
  	}

    while(getline(fin, dict_line_)) {
        dictionary_hash.Insert(dict_line_);
    }

  return dictionary_hash;
}

// For each word in the document_file, it checks the 3 cases for a word being
// misspelled and prints out possible corrections
void SpellChecker(const HashTableDouble<string>& dictionary,
		  const string &document_file) {

    string doc_line_; // string that holds original word from document
    string lower_doc_line_ = ""; // string that will hold the word processed to lowercase
    string final_word_ = ""; // string to print to stream and check if it is contained in hashtable
    // letters to insert for case A, alternatively can use ASCII codes
    vector<char> letters_ = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    
    std::ifstream fin(document_file);
  	if (fin.fail()) {
    	std::cerr << "File cannot be opened for reading." << std::endl;
    	exit(1); // exit if failed to open the file
  	}
    
    while(fin >> doc_line_) {
      // testing purposes
      // cout << doc_line_ << '\n';

      doc_line_ = toLowerCaseWord(doc_line_);
      
      // remove punctuation from first position of word/string, if any exist
      if(!isalnum(doc_line_[0]) ) {
        // testing purposes
        // cout << "before__\n"; 
        // cout << doc_line_[doc_line_.length()-1];
        doc_line_ = doc_line_.substr(1);
      }

      // remove punctuation from last position of word/string, if any exist
      if(!isalnum(doc_line_[doc_line_.length()-1]) ) {
        // testing purposes
        // cout << "before__\n"; 
        // cout << doc_line_[doc_line_.length()-1];
        doc_line_ = doc_line_.substr(0, doc_line_.length()-1);
      }

      // testing purposes
      // cout << doc_line_ << '\n';

      if(dictionary.Contains(doc_line_)) {
        cout << doc_line_ << " is CORRECT\n";
      }

      if(!dictionary.Contains(doc_line_) || hasNumber(doc_line_) || hasDash(doc_line_)) {
        cout << doc_line_ << " is INCORRECT\n";
      }

      // boolean value representing if it should be processed or not (only if it has no numbers or dashes)
      bool need_to_parse_ = (!hasNumber(doc_line_) || !hasDash(doc_line_));
      int string_length_ = doc_line_.length();

      if(need_to_parse_ && !dictionary.Contains(doc_line_)) {
        // case a - place letter in each position
        // nested for loops to go through each position of string, and every letter of alphabet
        for(int i = 0; i < string_length_ + 1; i++) {
          for(int j = 0; j < 26; j++) {
              final_word_ = doc_line_.substr(0,i) + letters_[j] + doc_line_.substr(i);
              if(dictionary.Contains(final_word_)) {
               cout << "** " << doc_line_ << " -> " << final_word_ << " ** case A\n";
              }
            }
          }
        // case b - remove a letter from each position
        // for loop to go through each position of word, use substring to take part of the
        // string excluding the selected character
        for(int i = 0; i < string_length_; i++) {
          final_word_ = doc_line_.substr(0,i) + doc_line_.substr(i+1, string_length_);
          if(dictionary.Contains(final_word_)) {
            cout << "** " << doc_line_ << " -> " << final_word_ << " ** case B\n";
          }
        }
        // case c - swap adjacent characters
        for(int i = 0; i < string_length_ - 1; i++) {
          final_word_ = doc_line_.substr(0,i) + doc_line_[i+1] + doc_line_[i] + doc_line_.substr(i+2, string_length_);
          if(dictionary.Contains(final_word_)) {
            cout << "** " << doc_line_ << " -> " << final_word_ << " ** case C\n";
          }
        }
      }      
    }

}

// @argument_count: same as argc in main
// @argument_list: save as argv in main.
// Implements
int testSpellingWrapper(int argument_count, char** argument_list) {
    const string document_filename(argument_list[1]);
    const string dictionary_filename(argument_list[2]);

    // Call functions implementing the assignment requirements.
    HashTableDouble<string> dictionary = MakeDictionary(dictionary_filename);
    SpellChecker(dictionary, document_filename);

    return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char** argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
         << endl;
    return 0;
  }
  
  testSpellingWrapper(argc, argv);
  
  return 0;
}
