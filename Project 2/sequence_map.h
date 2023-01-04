// Jubayer Ahmed
// SequenceMap is a non-templated class that has a vector that holds the name of a restriction 
// enzyme and a string containing possible DNA sites that the enzyme may cut at. The Object's 
// functionality allows for a method to merge an enzyme acronym into the vector holding the any
// acronyms that cut at the same DNA sequence, if the recognition sequences of both are the same.

#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H

#include <iostream>
#include <vector>
using namespace std;

class SequenceMap
{
public:
    // Zero-parameter constructor.
    SequenceMap() = default;

    // Copy-constructor.
    SequenceMap(const SequenceMap &rhs) = default;

    // Copy-assignment
    SequenceMap& operator=(const SequenceMap &rhs) = default;

    // Move-constructor.
    SequenceMap(SequenceMap &&rhs) = default;

    // Move-assignment.
    SequenceMap& operator=(SequenceMap &&rhs) = default;

    //destructor
    ~SequenceMap() = default;

    /**
     * Constructor for SequenceMap object
     * 
     * @param a_rec_seq String that holds possible DNA sequence sites where enzyme can cut
     * @param an_enz_acro String that holds the name of the restriction enzyme
     */
    SequenceMap(const string &a_rec_seq, const string &an_enz_acro) {
        this->recognition_sequence_ = a_rec_seq;
        std::vector<string> enz_acro_temp_ (1, an_enz_acro);
        this->enzyme_acronyms_ = enz_acro_temp_;
    }

    // lexicographically compare recognition sequence strings
    bool operator<(const SequenceMap &rhs) const {
        return this->recognition_sequence_ < rhs.recognition_sequence_;
    }

    // lexicographically compare recognition sequence strings
    bool operator>(const SequenceMap &rhs) const {
        return this->recognition_sequence_ > rhs.recognition_sequence_;
    }

    friend std::ostream &operator<<(std::ostream &out, const SequenceMap &some_sequence) {
        for(auto i : some_sequence.enzyme_acronyms_) {
            out << i << " ";
        }
        // out << some_sequence.recognition_sequence_ << "/";

        out << "\n";

        return out;
    }

    // Overloading the >> operator.
    // Read a chain from an input stream (e.g., standard input).
    friend std::istream &operator>>(std::istream &in, SequenceMap &some_sequence) {
        string temp_enz_acro_ = "";
        
        if(!some_sequence.enzyme_acronyms_.empty()) {
            some_sequence.~SequenceMap();
        }

        cout << "Enter an enzyme acronym: ";
        in >> temp_enz_acro_;

        some_sequence.enzyme_acronyms_.push_back(temp_enz_acro_);

        cout << "Enter the recognition sequence string: ";
        in >> some_sequence.recognition_sequence_;

        std::cout << "\n";
        
        return in;
    }

    /**
     * Accessor method to get private data member of SequenceMap object
     * 
     * @returns enzyme_acronyms_ vector of strings that hold enzyme acronyms of the object
     */
    vector<string> getAcronyms() {
        return this->enzyme_acronyms_;
    }

    /**
     * Merges the vector of enzyme acronyms of other_sequence to the current object's vector. 
     * other_sequence Object remain's untouched
     * 
     * @param other_sequence SequenceMap object whose private enzyme acronyms will be merged to
     * current object
     */
    void Merge(const SequenceMap &other_sequence) {
        for(auto i : other_sequence.enzyme_acronyms_) {
            this->enzyme_acronyms_.push_back(i);
        }
    }

private:
    string recognition_sequence_;
    std::vector<string> enzyme_acronyms_;
};

#endif