// Jubayer Ahmed
/**
 * Contains wrapper functions with general functionality to test hashtables that implement linear
 * probing, quadratic probing, and double hashing. 
*/

#include <fstream>
#include <iostream>
#include <string>

#include "linear_probing.h"
#include "double_hashing.h"

#include "quadratic_probing.h"

using namespace std;

// @hash_table: a hash table (can be linear, quadratic, or double)
// @words_filename: a filename of input words to construct the hash table
// @query_filename: a filename of input words to test the hash table
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table,
			      const string &words_filename,
			      const string &query_filename) {
    hash_table.MakeEmpty();
    
    // account for non-existent file - covering edge case of file error
    std::ifstream fin(words_filename);
  	if (fin.fail()) {
    	std::cerr << "File cannot be opened for reading." << std::endl;
    	exit(1); // exit if failed to open the file
  	}

    string word_line_; // String to store word string
    while(getline(fin, word_line_)) {
        hash_table.Insert(word_line_); // insert words into hashtable
    }

    // follows expected output and variable type
    // functionality general across multiple Hashtable object types (e.g. Linear, Quadratic, Double)
    cout << "number_of_elements: " << hash_table.NumElements() << '\n';
    cout << "size_of_table: " << hash_table.TableSize() << '\n';
    cout << "load_factor: " << ((float)hash_table.NumElements() / (float)hash_table.TableSize()) << '\n';
    cout << "collisions: " << hash_table.NumCollisions() << '\n';
    cout << "avg_collisions: " << ((float)hash_table.NumCollisions() / (float)hash_table.NumElements()) << '\n';

    // account for non-existent file - covering edge case of file error
    std::ifstream fin_two_(query_filename);
  	if (fin_two_.fail()) {
    	std::cerr << "File cannot be opened for reading." << std::endl;
    	exit(1); // exit if failed to open the file
  	}

    cout << '\n';

    // get queries from file, check if they exist in the hashtable
    // print out the number of probes necessary to find if it exists or not
    string query_line_;
    while(getline(fin_two_, query_line_)) {
        cout << query_line_ << " ";
        hash_table.Contains(query_line_) ? cout << "Found " : cout << "Not_Found ";
        cout << hash_table.NumProbes() << '\n';
    }
}

// @argument_count: argc as provided in main
// @argument_list: argv as provided in imain
// Calls the specific testing function for hash table (linear, quadratic, or double).
int testHashingWrapper(int argument_count, char **argument_list) {
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    int R = 89;
    if (argument_count == 5) {
	const string rvalue(argument_list[4]);
	R = stoi(rvalue);
    }

    if (param_flag == "linear") {
    //   Uncomment below when you have implemented linear probing.
      HashTableLinear<string> linear_probing_table;
      TestFunctionForHashTable(linear_probing_table, words_filename,
      			 query_filename);
    } else if (param_flag == "quadratic") {
	HashTable<string> quadratic_probing_table;
	TestFunctionForHashTable(quadratic_probing_table, words_filename,
				 query_filename);
    } else if (param_flag == "double") {
	cout << "r_value: " << R << endl;
        // Uncomment below when you have implemented double hashing.
	HashTableDouble<string> double_probing_table;
    double_probing_table.SetRValue(R); // Set R value in hashtable used for secondary hashing
	TestFunctionForHashTable(double_probing_table, words_filename,
				 query_filename);
    } else {
	cout << "Unknown tree type " << param_flag
	     << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

// Sample main for program create_and_test_hash. DO NOT CHANGE IT.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testHashingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv) {
    if (argc != 4 and argc != 5) {
	cout << "Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag>" << endl;
	cout << "or Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
	return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}
