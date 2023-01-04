// Jubayer Ahmed
/**
 * Hashtable object that implements double hashing. Uses secondary hash function from given R value
 * to compute second hash following a collision.
*/

#ifndef DOUBLE_HASHING_H
#define DOUBLE_HASHING_H

#include <vector>
#include <algorithm>
#include <functional>

// include the namespace for prime number related functions from quadratic_probing.h
#include "quadratic_probing.h"


// Double probing implementation.
template <typename HashedObj>
class HashTableDouble {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  // default R value implemented in constructor
  explicit HashTableDouble(size_t r_val_ = 89, size_t size = 101) : array_(NextPrime(size))
    { MakeEmpty();
      this->r_value_ = r_val_; // set r_value_ with the default R value unless one is passed in
     }
  
  bool Contains(const HashedObj & x) const {
    probes_ = 0; // reset probes to 0 after each time we call contains()
    return IsActive(FindPos(x));
  }
  
  void MakeEmpty() {
    // reset private data members when emptying object
    current_size_ = 0;
    collisions_ = 0;
    probes_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj & x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;
    
    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();    
    return true;
  }
    
  bool Insert(HashedObj && x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();

    return true;
  }

  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }

  // @returns number of elements in the hashtable
  size_t NumElements( ) {
    return current_size_;
  }

  // @returns size of the current hashtable (inluding empty and occupied cells)
  int TableSize( ) {
    return array_.size();
  }

  // @returns private data member representing number of collisions during probing/insertions
  size_t NumCollisions ( ) {
    return collisions_;
  }

  // @returns private data member representing number probes during insertions/searching
  size_t NumProbes ( ) {
    return probes_;
  }

  // @param given_val_ parameter of type size_t which will be used for secondary hash function
  // sets private data member r_value_ to given value
  void SetRValue ( size_t given_val_ ) {
    r_value_ = given_val_;
  }

 private:        
  struct HashEntry {
    HashedObj element_;
    EntryType info_;
    
    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
    :element_{e}, info_{i} { }
    
    HashEntry(HashedObj && e, EntryType i = EMPTY)
    :element_{std::move(e)}, info_{ i } {}
  };
    

  std::vector<HashEntry> array_;
  size_t current_size_; // represents number of elements in the hashtable
  size_t r_value_; // value used for secondary hashing algorithm
  mutable size_t collisions_; // represents number of collisions during probing/insertions
  mutable size_t probes_; // represents number of probes during searching/insertions

  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  size_t FindPos(const HashedObj & x) const {
    size_t current_pos = InternalHash(x);
    probes_++;

    while (array_[current_pos].info_ != EMPTY &&
	   array_[current_pos].element_ != x) {
      probes_++; // increment probes (looking for new open cell)
      collisions_++; // increment collisions (until we break out of while loop, meaning cell was found)

      // increment current position using computed secondary hash value
      current_pos += SecondaryHash(x);  // Compute ith probe.
      
      if (current_pos >= array_.size())
	      current_pos -= array_.size();
    }
    return current_pos;
  }

  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrime(2 * old_array.size()));
    for (auto & entry : array_)
      entry.info_ = EMPTY;
    
    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array)
      if (entry.info_ == ACTIVE)
	Insert(std::move(entry.element_));
  }
  
  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size();
  }

  // secondary hash function used for double probing
  // uses private data member r_value_ to compute hash function
  size_t SecondaryHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return r_value_ - (hf(x) % r_value_);
  }
};

#endif  // DOUBLE_HASHING_H
