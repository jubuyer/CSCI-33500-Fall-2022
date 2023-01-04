[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=8630860&assignment_repo_type=AssignmentRepo)
# Assignment 2

## Solution and Approach Explanation
My strategy to understanding the assignment was to fully understand the concept of database we were given. I had trouble figuring out how the Restriction enzyme acronym and recognition string connected, but was able to understand it while working on creating the `SequenceMap` class. 

Creating the `SequenceMap` Class
- Implemented the big 5 and then worked on creating the constructor/other methods
- Understanding how the enzyme acronym and recognition sequence went together in the database given (`rebase210.txt`) was the key to implementing both Merge and the constructor correctly.

Modifying the `avl_tree.h` Class
- I spent time reading through the `AvlTree` class and understanding how the `Comparable` type interacted with the class. Doing so allowed me to understand how to implement functions that would be able to work within the tree to calculate tree features (depth, # of nodes, etc) and recursion calls. 
- The strategy I used to find the recursion calls of functions in the `AvlTree` class was to overload the existing methods to allow variables to be passed in by reference. For implementing double rotation, I connected the concepts and code from the single rotation to the given code for double rotations, allowing me to modify the function. 
## What Was Simple
- After spending a good chunk of time understanding how the enzyme acronym and recognition string would interact with the objects (both `SequenceMap` and `AVLTree`), implementing the `SequenceMap` class was simple
    - Although I had a few issues along the way, for example, trying to access private members of the class, which I was able to fix by creating an accessor method, and implementing the Merge correctly, overall, this was the task that I felt was simple.
## What Was Difficult
- Understanding how to interact with the database (`rebase210.txt`)
    - When I began creating the `SequenceMap` class, I initially had trouble understanding why the enzyme acronyms were stored in the vector and why the recognition string would not be stored there (since they were split up by `//`). However, taking time to fully understand the meaning of the object and what we were attempting to code helped me work through implementing the class. Additionally, I was able to work with the class in later problems seamlessly, since I understood how to interact with it.
- Modifying the `AVLTree` class
    - Finding total recursion calls
        - Initially, I had a difficult time figuring out how I would get an accurate value when trying to count recursion calls. After studying the functions, I decided that the best course of action was to use reference paramaters in overloaded functions. I wanted to be completing the same task (finding an element, removing and element, finding the minimum element) while counting at the same time, which would theoretically give me the accurate number of calls.
        - After overloading the calls, I only had minor errors, but they took a little bit of work to fix. When I realized I was trying to access private data members (which I realized when I was iterating my counting parameters and was a previous issue in another part), I created a `const` accessor method. The biggest issue was during part 2b, # 5b, where I realized that my total recursion calls were not accurate. Finding the correct places to iterate the total and current path variables along with accounting for the successful calls took the most time. Referencing the discussion board, and the other methods from `AVLTree` helped me work through the problem. 
    - Implementing double rotations
        - I thought that this would be the hardest part of the assignment, but realized that most of what we needed to know was provided to us in `AVLTree`. After analyzing the code for single rotations and consulting the slides/textbook, I realized how I could modify the code to be able to account for cases where single rotation would fail.
## Edge Cases
- Accounting for user inputting more than 3 sequences for part 1
    - By using a while loop to extract user input from the stream, I'm able to account for more than 3 inputs made by the user. I can then compare each recognition string to see if it exists in the database (and write the respective enzyme acronyms to the stream)
- Preventing total recursion calls including calls for items that don't exist
    - I passed a variable by reference (`current_path_`) that holds the number of times a recursion call occured during an instance of the function call from main. If the recursion reaches the base case, I subtract the number of recursion calls from the total so that the total recursion calls is accurate (in the case of number 5 of part 2b). Before the method returns (and terminates) I set the value equal to zero, resetting the value. This allowed me to get the exact average number of recursion calls when we begin to remove sequences from the `AVLTree` object.
## Efficiency
- Overloaded `>>` and `<<` operator uses `in` and `out` respectively
- Pass variables by reference to prevent the need to initialize or create new variables inside functions during recursive calls

---
You will use this exact `Makefile` for your Homework 2. Failure to do so will result in *deduction* of points. Replace this file with a `README.md` for your own project. You can move these instructions to the bottom of the file if you wish.

To compile on terminal, type:

```bash
make
```

You can compile one program individually by just typing `make <Program Name>`, for example:

```bash
make query_tree
```

To delete executables and object files, type:

```bash
make clean
```
