# Assignment-3-Code

## Solution and Approach Explanation
- I began by reading through the code of `quadratic_probing.h` and understanding how each data member interacted with each other. Following that, I studied the `FindPos()` functions specifically to be able to understand how the probing was working. From there I was able to build the other hashtables with different probing methods, and find the necessary data points, including probes, collisions, and load factor.

- I used the textbook as a guide when I was confused, which allowed me to better understand how the probes were working, and allowed me to see where each probing technique built off of the other (preventing primary/secondary clustering)

- For `spell_check.cc`, I took the time to look through `wordsEn.txt` and the documents to understand what my program would have to do, in terms of pre and post processing. From there I was able to understand how to harness the `substr()` method to be able to implement each case.
## What Was Simple
- Implementing linear and quadratic probing was relatively simple since I understood the idea of it after reading the textbook and slides. I was able to quickly implement the probes and collision data members, but had a slight issue when I tried to increment them in a `const` function. However, the `mutable` keyword allowed me to do so, and calculate the load factor and other data points easily.
## What Was Difficult
- I found that implementing double hashing in `double_hashing.h` was the most difficult, simply due
to the fact that I had to rethink about how I was handling collisions, and calculating them. However, I realized that it was actually simpler than I thought and had to use the secondary hash
function to be able to increment positions.

- Considering how to pre-process words prior to checking each case was the most difficult for me. After some preliminary tests where I check what each line will print after getting it from the file, I was able to tell that some words had punctuation and other symbols attached (inluding numbers). From there I was able to create my plan of action: Change all the letters to lowercase to prevent any issues down the line (and in comparison with the hashtable elements), and then clean the word of numbers and dashes.
## Edge Cases
- Accounted for file reading errors through the `.fail()` method from `std::ifstream`

- In `spell_check.cc` I account for words that have numbers or dashes in the document,
preventing them from being passed into the parts of the program that process the words and
mitigating and unnecessary errors

- Accounted for punctuation attached to words (before and after) before beginning word
processing

- Set default R value in `HashtableDouble` object to allow secondary hashing to occur
even when a value is not specified/passed in by the user

- I accounted for multiple cases finding a word that fit from an Incorrect word, allowing me to consider all possible outcomes and not leave any words out
## Efficiency
- I minimized the necessary time to clean words in `spell_check.cc` by reducing loops as much as possible and combining boolean statements in `if` statements whereever possible. Additonally, I created boolean flags that would let the program know whether or not it needs to be processed and checked for each case. 