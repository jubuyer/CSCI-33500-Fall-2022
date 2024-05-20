# Assignment-4-Code

## Solution and Approach Explanation
- I began by first reading over the Sort.h code and the accompanying material in the textbook so that I could better understand how the code was structured. I noticed some parts of the code would cause compiler errors so I worked on fixing that first.
  - My first step was to move around code so that I could prevent any future issues (mainly relating the merge sort functions, a helper function was in the incorrect order). 
  - I then worked towards understanding how I could modify the sorting functions, eventually going with the choice to overload the helper functions and driver functions.
- After understanding how we should incorporate the `Comparator` type, I was able to quickly figure out where it should be used. I ran into some problems with using it in places I shouldn't be, but constantly compiling and testing my code, along with printing out the vector I should be sorting allowed me to fix my code.
## What Was Simple
- Creating the initial methods like `VerifyOrder()` and the vector generating methods were simple since I was used to the process of building them from previous assignments. I knew I could use a for loop and have the most efficient solution just by keeping it simple.
- Adding in the `Comparator` type to the overloaded functions was pretty simple as well since I took the time to understand how the program and functions were structured before starting any actual coding. However incorporating the `less_than` parameter was a bit confusing only because of the name and choosing where we should substitute it.
## What Was Difficult
- Quicksort 2 and 3 gave me the most difficulty. I was extremely confused as to why my vectors were not sorted until printing out my vectors multiple times. Throughout my testing I found that I was only a few numbers off from sorting the entire vector. This led me to making the modifications I did to the code:
    - I first modified my bounds since I assumed that there was a section at the start that wasn't being accounted for. I figured this out since I noticed that a very small number and a very large number had their positions swapped at the end of the sorting algorithm. I tested using the smaller_to_larger flag along with a size of 100 so that I could quickly diagnose where the issues were coming from. 
    - After modifying my bounds I realized that there was still more to change, so I moved to the insertion sort next. This took the most time to figure out, but after reading the textbook for a while and changing around some of the code that was given to us (and a little bit of guessing and playing around with the function) I was able to change the way I incremented and swapped, allowing me to get the insertion sort to function properly in the different quicksort algorithms
## Edge Cases
- I prevented typecast warnings by creating variables of type `Comparable` and passing those into functions. By doing so, I prevented compiler warnings when comparing `int`'s to type `Comparable` later on in the helper functions, even if the `Comparable` type was able to be compared to an int.
- By adding modified bounds, I made sure to prevent segmentation faults and helper functions from accessing data that didn't exist beyond the vector sizes
## Efficiency
- I didn't create multiple temporary variables when working within the helper functions, instead passing in by reference. 
- I overloaded functions instead of creating functions with new names or declarations, allowing for efficient usage and ease of understanding code.
