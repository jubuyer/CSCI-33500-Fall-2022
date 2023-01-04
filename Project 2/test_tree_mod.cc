// <Your name>
// Main file for Part2(c) of Homework 2.
// Code will compile and run after you have completed sequence_map.h.

#include "avl_tree_p2c.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

namespace {

// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType> void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
	// Final Answer Variables
	int two_ = 0;
	int four_a_ = 0;
	int four_successful_reference_ = 0;
	int four_total_reference_ = 0;	
	int five_a_ = 0;
	int five_successful_reference_ = 0;
	int five_total_reference_ = 0;	
	int five_current_path_reference_ = 0;	
	int six_a_ = 0;
	float three_a_ = 0.0;
	float three_b_ = 0.0;
	float four_b_ = 0.0;
	float five_b_ = 0.0;
	float six_b_ = 0.0;
	float six_c_ = 0.0;

	// read database
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
		db_line_ = db_line_.substr(0, db_line_.length() - 1);
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

	two_ = a_tree.numTotalNodes();
	three_a_ = a_tree.findInternalPathLen(0.0) / (float)a_tree.numTotalNodes();
	three_b_ = three_a_ / (float)a_tree.numTotalNodes();


	std::ifstream file_two_in_(seq_filename);
  	if (file_two_in_.fail()) {
    	std::cerr << "File cannot be opened for reading." << std::endl;
    	exit(1); // exit if failed to open the file
  	}


	string another_reco_seq_;
	while(file_two_in_ >> another_reco_seq_) {
		SequenceMap possible_enz_seq_(another_reco_seq_, "");
		a_tree.find(possible_enz_seq_, four_successful_reference_, four_total_reference_);
	}

	file_two_in_.close();

	std::ifstream file_three_in_(seq_filename);
  	if (file_three_in_.fail()) {
    	std::cerr << "File cannot be opened for reading." << std::endl;
    	exit(1); // exit if failed to open the file
  	}

	four_a_ = four_successful_reference_;
	four_b_ = (float) four_total_reference_/ (float) four_successful_reference_;


	string more_reco_seqs_;
	int parity_iterator_ = 1;
	while(file_three_in_ >> more_reco_seqs_) {
		SequenceMap possible_enz_seq_(more_reco_seqs_, "");

		// remove every other sequence from tree
		if((parity_iterator_ % 2) > 0) {
			a_tree.remove(possible_enz_seq_, five_successful_reference_, five_total_reference_, five_current_path_reference_);
		}

		parity_iterator_++;
	}

	file_three_in_.close();

	five_a_ = five_successful_reference_;
	five_b_ = (float) five_total_reference_/ (float) five_successful_reference_;
	
	// cout << five_total_reference_ << '\n';
	// cout << five_successful_reference_ << '\n';
	
	six_a_ = a_tree.numTotalNodes();
	six_b_ = a_tree.findInternalPathLen(0.0) / (float)a_tree.numTotalNodes();
	six_c_ = six_b_ / (float)a_tree.numTotalNodes();

	cout << "2: " << two_ << "\n";
	cout << "3a: " << three_a_ << "\n";
	cout << "3b: " << three_b_ << "\n";
	cout << "4a: " << four_a_ << "\n";
	cout << "4b: " << four_b_ << "\n";
	cout << "5a: " << five_a_ << "\n";
	cout << "5b: " << five_b_ << "\n";
	cout << "6a: " << six_a_ << "\n";
	cout << "6b: " << six_b_ << "\n";
	cout << "6c: " << six_c_ << "\n";
	


}

}  // namespace

// int main(int argc, char **argv) {
// 	if (argc != 3) {
// 		cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
// 		return 0;
// 	}
// 	const string db_filename(argv[1]);
// 	const string seq_filename(argv[2]);
// 	cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
// 	AvlTree<SequenceMap> a_tree;
// 	TestTree(db_filename, seq_filename, a_tree);

// 	return 0;
// }
