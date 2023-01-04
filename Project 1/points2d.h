// Jubayer Ahmed
// Points2D is a template class that allows the user to create and object that holds 
// a sequence of 2D points. The class has overloaded functions that allow points to be printed
// to the stream, for points to be added, and for the user to input a sequence of points. 

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project {

// Place comments that provide a brief explanation of the class,
// and its sample usage.
template<typename Object>
class Points2D {
  public:
    // Default "big five" -- you have to alter them for your assignment.
    // That means that you will remove the "= default" statement.
    //  and you will provide an implementation.

    /* 
        Zero-parameter constructor.
        Set size to 0.
        Removed: use of initialization list (allowing data members to be initialized directly.)
        Removed: explicit is used to prevent type-conversions (in one parameter constructor)
    */
    Points2D () { 
        this->size_ = 0;
        // this->sequence_ = nullptr; not needed, leads to errors in program
    } 

    // Copy-constructor.
    // We want a deep copy of the sequence 
    Points2D(const Points2D &rhs) {
        this->size_ = rhs.size_;
        this->sequence_ = new std::array<Object,2>[this->size_];

        // deep copy of sequence
        // if we only did this->sequence = rhs.sequence we could end up with shallow copy
        for(size_t i = 0; i < this->size_; i++) {
            this->sequence_[i][0] = rhs.sequence_[i][0];
            this->sequence_[i][1] = rhs.sequence_[i][1];
        }
    }

    // Copy-assignment. If you have already written
    // the copy-constructor and the move-constructor
    // you can just use:
    // {
    // Points2D copy = rhs;
    // std::swap(*this, copy);
    // return *this;
    // }
    Points2D& operator=(const Points2D &rhs) {
        Points2D copy = rhs;
        std::swap(*this, copy);
        return *this;
    };

    // Move-constructor.
    Points2D(Points2D &&rhs) {
        this->size_ = rhs.size_;
        this->sequence_ = rhs.sequence_;

        // point rhs to null, set size to 0 (finishes "moving data members to new object")
        rhs.sequence_ = nullptr;
        rhs.size_ = 0;
    }

    // Move-assignment.
    // Just use std::swap() for all variables.
    Points2D& operator=(Points2D &&rhs) {
        if(this != &rhs) { //accounts for the object being the same as rhs
            std::swap(this->size_, rhs.size_);
            std::swap(this->sequence_, rhs.sequence_);
        }

        return *this;
    }

    // destructor
    // if sequence has any items, delete sequence
    ~Points2D() {
        if(this->size_ > 0) {
            delete this->sequence_;
        }
    }

    // End of big-five.

    // One parameter constructor.
    Points2D(const std::array<Object, 2>& item) {
        // initialize data members of object
        this->size_ = 1;
        this->sequence_ = new std::array<Object, 2>[size_];

        // copy values inside of 'item' sequence
        this->sequence_[0][0] = item[0];
        this->sequence_[0][1] = item[1];
    }

    // getter method for size_ data member from Points2D object
    size_t size() const {
        return this->size_;
    }

    // @location: an index to a location in the sequence.
    // @returns the point at @location.
    // const version.
    // abort() if out-of-range.
    const std::array<Object, 2>& operator[](size_t location) const {
        // if location is out of bounts, abort
        if(location > this->size_) {
            abort();
        }

        return this->sequence_[location];
    }

    //  @c1: A sequence.
    //  @c2: A second sequence.
    //  @return their sum. If the sequences are not of the same size, append the
    //    result with the remaining part of the larger sequence.
    friend Points2D operator+(const Points2D &c1, const Points2D &c2) {
        Points2D output;
        size_t larger, smaller;

        // set variables for larger and smaller sequence
        c1.size_ < c2.size_ ? larger = c2.size_ : smaller = c2.size_;
        c1.size_ < c2.size_ ? smaller = c1.size_ : larger = c1.size_;

        // initialize data members of output Points2D object
        output.size_ = larger;
        output.sequence_ = new std::array<Object, 2>[larger];
        
        // std::cout << smaller << " TESTING\n";
        // std::cout << larger << " TESTING TWO\n";

        // add points together (from smaller sequence and larger sequence)
        for(size_t i = 0; i < smaller; i++) {
            output.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
            output.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
        } 

        //append points from larger sequence to smaller sequence
        for(size_t i = smaller; i < larger; i++) {
            if(c1.size() > c2.size()) {
                output.sequence_[i][0] = c1.sequence_[i][0];
                output.sequence_[i][1] = c1.sequence_[i][1];

            } else {
                output.sequence_[i][0] = c2.sequence_[i][0];
                output.sequence_[i][1] = c2.sequence_[i][1];

            }
        }

        return output;

    }

    // Overloading the << operator.
    friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points) {
        //base case, size_ is 0
        if(some_points.size_ == 0) {
            out << "()" << std::endl;
            return out;
        }

        int size = (int)some_points.size();
        for(int i = 0; i < size; i++) {
            // if(i != 0) {
            //     out << " ";
            // } unnecessary procedure, each point has a space afterwards
            out << "(" << some_points.sequence_[i][0] << ", " << some_points.sequence_[i][1] << ") ";
        }

        out << "\n";

        return out;
    }

    // Overloading the >> operator.
    // Read a chain from an input stream (e.g., standard input).
    friend std::istream &operator>>(std::istream &in, Points2D &some_points) {
        if(some_points.sequence_ != nullptr) {
            some_points.~Points2D();
        }

        std::string sequence_size;
        in >> sequence_size;

        // input validation to confirm that the first input (that should represent size) is a digit
        // prevents exception thrown prior to converting string to integer
        try {
            // if the conversion from string to integer fails, exception is thrown 
            // (e.g. sequence_size holds a character instead of a digit)
            std::stoi(sequence_size);
        } catch (int e) {
            std::cerr << "ERROR";
            abort();
        }

        int size = std::stoi(sequence_size);

        // testing
        // std::cout << "INPUT SIZE IS: " << sequence_size << "\n";

        // initialize the Points2D object's sequence
        some_points.sequence_ = new std::array<Object, 2>[size];
        some_points.size_ = size;

        // object to handle the input from the stream, matches type of Template
        Object input;
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < 2; j++) {

                // If not at end of file/input, store in sequence, otherwise abort
                if(!in.eof()) {
                    in >> input; // get the point 

                    //account for input not working (e.g. not same as Object)
                    if(in.fail()) {
                        std::cerr << "ERROR";
                        abort();
                    }
                    
                    some_points.sequence_[i][j] = input;
                } else {
                    std::cerr << "ERROR";
                    abort();
                }
            }
        }

        //flush stream at the end of each input sequence
        std::cout << "\n";
        
        return in;
    }

  private:
    // Sequence of points.
    std::array<Object, 2> *sequence_;
    // Size of sequence.
    size_t size_;
};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_Points2D_H_

