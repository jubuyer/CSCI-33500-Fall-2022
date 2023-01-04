// Homework 4
// Testing Sorting Algorithms
// YOUR NAME

#include "Sort.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
using namespace std;

// Computes duration given a start time and a stop time in nano seconds.
// Keep it in.
auto ComputeDuration(chrono::high_resolution_clock::time_point start_time, 
			  chrono::high_resolution_clock::time_point end_time) {
  return chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
}

// Test function that shows how you can time a piece of code.
// Just times a simple loop. Remove for final submission.

void TestTiming() {
  cout << "Test Timing" << endl;
  const auto begin_time = chrono::high_resolution_clock::now();
  // Time this piece of code.
  int sum = 0;
  for (int i = 1; i < 10000; ++i) sum ++;
  // End of piece of code to time.
  const auto end_time = chrono::high_resolution_clock::now();    
  cout << ComputeDuration(begin_time, end_time) << "ns" << endl;

}

// Generates and returns random vector of size @size_of_vector.
vector<int> GenerateRandomVector(size_t size_of_vector) {
  // Use rand() to generate random integer
  // Add code
  vector<int> output_;
  for(size_t i = 0; i < size_of_vector; i++) {
    output_.push_back(rand() % size_of_vector);
  }

  return output_;
}

// Generates and returns sorted vector of size @size_of_vector.
// If @smaller_to_larger is true, returns vector sorted from small to large.
// Otherwise returns vector sorted from large to small
vector<int> GenerateSortedVector(size_t size_of_vector, bool smaller_to_larger) {
  // Add code
  vector<int> output_;
  if(smaller_to_larger) {
    for(size_t i = 0; i < size_of_vector; i++) { // start at 0 and push in number up to size
      output_.push_back(i);
    }
  } else {
      for(int i = size_of_vector; i > 0; i--) { // start at size and push in number up to 0
        output_.push_back(i);
      }
  }

  return output_;
}

// Verifies that a vector is sorted given a comparator.
// I.e. it applies less_than() for consecutive pair of elements and returns true
// iff less_than() is true for all pairs.
template <typename Comparable, typename Comparator>
bool VerifyOrder(const vector<Comparable> &input, Comparator less_than) {
  // Add code
  size_t length_ = input.size();
  bool output_ = true;
  for(size_t i = 0; i < length_ - 1; i++) {
    if(!less_than(input[i], input[i+1])) {
      if(input[i] != input[i+1]) 
        output_ = false;
    }
  }

  return output_;
}

// Wrapper function to test different sorting algorithms. See homework's PDF for details.
void testSortingWrapper(int argc, char **argv) {
  const string input_type = string(argv[1]);
  const int input_size = stoi(string(argv[2]));
  const string comparison_type = string(argv[3]);
  bool sort_by_small_;
  if (input_type != "random" && input_type != "sorted_small_to_large" && input_type != "sorted_large_to_small") {
    cout << "Invalid input type" << endl;
    return;
  }
  if (input_size <= 0) {
    cout << "Invalid size" << endl;
    return;
  }
  if (comparison_type != "less" && comparison_type != "greater") {
    cout << "Invalid comparison type" << endl;
    return;
  }

  if (input_type != "sorted_small_to_large") {
    sort_by_small_ = true;
  } else if (input_type != "sorted_large_to_small") {
    sort_by_small_ = false;
  }

  // This block of code to be removed for your final submission.
  // TestTiming();

  cout << "Running sorting algorithms: " << input_type << " " << input_size << " numbers " << comparison_type << endl;
  
  vector<int> input_vector;
  
  if (input_type == "random") {
    // Generate random vector @input_vector.
    input_vector = GenerateRandomVector(input_size);
  } else {
    // Generate sorted vector @input_vector.
    input_vector = GenerateSortedVector(input_size, sort_by_small_);
  }

  vector<int> original_vector = input_vector;

  // Call HeapSort / MergeSort / QuickSort  using appropriate input.
  // ...
  // if comparison type is "less" then call 
  // MergeSort(input_vector, less<int>{})
  // otherwise call
  // MergeSort(input_vector, greater<int>{})
  // ...
  // ^^SAME for HeapSort & QuickSort
  if(comparison_type == "less") {
    const auto begin_time = chrono::high_resolution_clock::now();
    
    std::cout << "Heapsort\n";
    HeapSort(input_vector, less<int>{});
    const auto end_time = chrono::high_resolution_clock::now();    
    cout << "Runtime: " << ComputeDuration(begin_time, end_time) << "ns" << endl;
    std::cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << "\n";

    // reset vector
    input_vector = original_vector;
    const auto begin_time2 = chrono::high_resolution_clock::now();
    
    std::cout << "\nMergeSort\n";
    MergeSort(input_vector, less<int>{});
    const auto end_time2 = chrono::high_resolution_clock::now();    
    cout << "Runtime: " << ComputeDuration(begin_time2, end_time2) << "ns" << endl;
    std::cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << "\n";

    // for(auto i : input_vector) {
    //   std::cout << i << " ";
    // }
    // std::cout << "\n";

    // reset vector for QuickSort
    input_vector = original_vector;
    const auto begin_time3 = chrono::high_resolution_clock::now();
    
    std::cout << "\nQuickSort\n";
    QuickSort(input_vector, less<int>{});
    const auto end_time3 = chrono::high_resolution_clock::now();    
    cout << "Runtime: " << ComputeDuration(begin_time3, end_time3) << "ns" << endl;
    std::cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << "\n";

    // Quicksort implementations
    std::cout << "\nTesting Quicksort Pivot Implementations\n";

    input_vector = original_vector;
    const auto begin_time4 = chrono::high_resolution_clock::now();
    
    std::cout << "\nMedian of Three\n";
    QuickSort(input_vector, less<int>{});
    const auto end_time4 = chrono::high_resolution_clock::now();    
    cout << "Runtime: " << ComputeDuration(begin_time4, end_time4) << "ns" << endl;
    std::cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << "\n";

    // qsort 2
    input_vector = original_vector;
    const auto begin_time5 = chrono::high_resolution_clock::now();
    
    std::cout << "\nMiddle\n";
    QuickSort2(input_vector, less<int>{});
    const auto end_time5 = chrono::high_resolution_clock::now();    
    cout << "Runtime: " << ComputeDuration(begin_time5, end_time5) << "ns" << endl;
    std::cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << "\n";
    
    // for(auto i : input_vector) {
    //   std::cout << i << " ";
    // }
    // std::cout << "\n";

    // qsort 3
    input_vector = original_vector;
    const auto begin_timeA = chrono::high_resolution_clock::now();
    
    std::cout << "\nFirst\n";
    QuickSort3(input_vector, less<int>{});
    const auto end_timeA = chrono::high_resolution_clock::now();    
    cout << "Runtime: " << ComputeDuration(begin_timeA, end_timeA) << "ns" << endl;
    std::cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << "\n";

    // for(auto i : input_vector) {
    //   std::cout << i << " ";
    // }
    // std::cout << "\n";

  } else {
    const auto begin_time6 = chrono::high_resolution_clock::now();

    std::cout << "Heapsort\n";
    HeapSort(input_vector, greater<int>{});
    const auto end_time6 = chrono::high_resolution_clock::now();    
    cout << "Runtime: " << ComputeDuration(begin_time6, end_time6) << "ns" << endl;
    std::cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << "\n";
  
    input_vector = original_vector;
    const auto begin_time7 = chrono::high_resolution_clock::now();
    
    std::cout << "\nMergeSort\n";
    MergeSort(input_vector, greater<int>{});
    const auto end_time7 = chrono::high_resolution_clock::now();    
    cout << "Runtime: " << ComputeDuration(begin_time7, end_time7) << "ns" << endl;
    std::cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << "\n";

    // reset vector for QuickSort
    input_vector = original_vector;
    const auto begin_time8 = chrono::high_resolution_clock::now();
    
    std::cout << "\nQuickSort\n";
    QuickSort(input_vector, greater<int>{});
    const auto end_time8 = chrono::high_resolution_clock::now();    
    cout << "Runtime: " << ComputeDuration(begin_time8, end_time8) << "ns" << endl;
    std::cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << "\n";

    // Quicksort implementations
    std::cout << "\nTesting Quicksort Pivot Implementations\n";

    input_vector = original_vector;
    const auto begin_time9 = chrono::high_resolution_clock::now();
    
    std::cout << "\nMedian of Three\n";
    QuickSort(input_vector, greater<int>{});
    const auto end_time9 = chrono::high_resolution_clock::now();    
    cout << "Runtime: " << ComputeDuration(begin_time9, end_time9) << "ns" << endl;
    std::cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << "\n";

    // qsort 2
    input_vector = original_vector;
    const auto begin_time10 = chrono::high_resolution_clock::now();
    
    std::cout << "\nMiddle\n";
    QuickSort2(input_vector, greater<int>{});
    const auto end_time10 = chrono::high_resolution_clock::now();    
    cout << "Runtime: " << ComputeDuration(begin_time10, end_time10) << "ns" << endl;
    std::cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << "\n";

    // qsort 3
    input_vector = original_vector;
    const auto begin_time11 = chrono::high_resolution_clock::now();
    
    std::cout << "\nFirst\n";
    QuickSort3(input_vector, greater<int>{});
    const auto end_time11 = chrono::high_resolution_clock::now();    
    cout << "Runtime: " << ComputeDuration(begin_time11, end_time11) << "ns" << endl;
    std::cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << "\n";

}
  // Call quicksort with median of three as pivot / middle as pivot / first as pivot using appropriate input.
  // ...
  // if comparison type is "less" then call 
  // QuickSort(input_vector, less<int>{})
  // otherwise call
  // QuickSort(input_vector, greater<int>{})
  // ...
  // ^^SAME for QuickSort2 & QuickSort3

}

int main(int argc, char **argv) {
  // DO NOT CHANGE or ADD ANY CODE in this function.
  if (argc != 4) {
    cout << "Usage: " << argv[0] << "<input_type> <input_size> <comparison_type>" << endl;
    return 0;
  }
  
  testSortingWrapper(argc, argv);

  return 0;
}
