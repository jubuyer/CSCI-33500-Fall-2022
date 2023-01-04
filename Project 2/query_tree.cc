// Jubayer Ahmed
// Main file for Part2(a) of Homework 2.
// Code will compile and run after you have completed sequence_map.h.

#include "avl_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

namespace {


// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {
	// Code for running Part2(a)
	// Parse input file @db_filename and feel tree @a_tree
	// Then prompt the user for exactly three strings (do a loop) and
	// provide the results of find() as described in the assignment.

	string db_line_;
	string copyright_notice_;

	std::ifstream fin(db_filename);
  	if (fin.fail()) {
    	std::cerr << "File cannot be opened for reading." << std::endl;
    	exit(1); // exit if failed to open the file
  	}

	// handle copyright notice (10 lines)
	for(int i = 0; i < 10; i++) {
		getline(fin, copyright_notice_);
	}

	while(getline(fin, db_line_)) {
		stringstream ss(db_line_);
		// cout << db_line_ << "\n";
		
		string an_enz_acro_;
		getline(ss, an_enz_acro_, '/');

		string a_reco_seq_;

		while(getline(ss, a_reco_seq_, '/')) {
			SequenceMap new_sequence_map(a_reco_seq_, an_enz_acro_);
			a_tree.insert(new_sequence_map);
		}

	}

	fin.close();

	string a_reco_seq_;
	while(cin >> a_reco_seq_) {
		SequenceMap possible_enz_seq_(a_reco_seq_, "");
		vector<string> output_ = a_tree.find(possible_enz_seq_);
		for(auto i: output_) {
			cout << i << ' ';
		}

		cout << '\n';
	}
}

}  // namespace

// int
// main(int argc, char **argv) {

// 	// testing part 1
// 	// SequenceMap a_test("GACGT'C", "AatII");
// 	// SequenceMap b_test("CC'TCGAGG", "AbsI");

// 	// cout << a_test << "\n" << b_test << "\n";
// 	// a_test > b_test ? cout << "a_test > b_test\n" : cout << "a_test < b_test\n";

// 	// SequenceMap c_test("CACCTGCNNNN'NNNN", "AarI");
// 	// SequenceMap d_test("'NNNNNNNNGCAGGTG", "AarI");
// 	// c_test.Merge(d_test);
// 	// cout << c_test;

// 	if (argc != 2) {
// 		cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
// 		return 0;
// 	}
// 	const string db_filename(argv[1]);
	
// 	cout << "Input filename is " << db_filename << endl;
// 	AvlTree<SequenceMap> a_tree;
// 	QueryTree(db_filename, a_tree);

// 	return 0;
// }
