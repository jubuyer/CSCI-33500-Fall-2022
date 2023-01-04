[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=8306502&assignment_repo_type=AssignmentRepo)
# Assignment 1

## Solution and Approach Explanation
My approach consisted of trying to connect the overall example of Big 5 concepts from the textbook
to the problem we were given. I began with forming the constructors (zero and one-parameter), which helped me understand the data types and nuances of the Points2D object. 

Approaching Big 5 methods
- I began with the initialization constructors for Points2D and then moved on to the copy constructor and assignment operator. I found that understanding the initial constructor for building the object helped me understand how the data members could be moved and copied further down the line

- Understanding how the lvalues/rvalues were passed as parameters cleared up confusion for how to correctly move/copy one object into another object 

Approaching Operator Overloading
- I began with overloading the stream insertion `<<` operator and then moved on to other the `>>`, `+`, and `[]` operators. More detail in the [What Was Difficult](#what-was-difficult) section.
## What Was Simple
- The getter methods were the most simple and accounting for any possible errors, like out of bounds or null objects was easy.
- I found that overloading the `+` operator was simple since I left that for last after understanding how to overload the stream extraction operator.
## What Was Difficult
- Overloading the stream extraction operator was the most difficult because testing whether or not the other constructors and methods would work depending on reading the sequence from the input file correctly. Multiple small errors, which included not accounting for eof led to alot of difficulty understanding the overloading. Additionally, I didn't flush the stream after finishing extracting, which led to further problems and time to understand what I did wrong. Following the Basics of I/O document made the process smoother, but was still the most difficult. 
- With my current input validation, I'm still not sure if my code would be able to recognize point values after on new lines or to throw an error if there are more points than the sequence size specifies. 
## Edge Cases
The overloaded stream insertion operator accounts for input validation.
- A try/catch clause in the begining of the method checks if the first item input that is supposed to represent the size of the sequence will pass the `std::stoi` method. If there is a character or non-digit, the program will abort
- The `if(!in.fail())` clause allows my code to check if the rest of the items from the sequence match the Template class type (Object) in the for loop as it parses through the sequence. If the type does not match, the program aborts after a std::cerr clause. This should similarly account for new lines added to sequences.
- the `if(!in.eof())` clause helps to check if the stream extraction method has reached the end of the user input, or has not gone beyond the bounds of the input sequence.
## Efficiency
- I was able to keep my code efficient by using the given parameters and not creating unnecessary variables to hold them temporarily
- ex. `operator+` overload: instead of creating instances to hold the size of `c1` and `c2` to compare the larger/smaller sequence, I took advantage of c1 and c2 being passed in by reference and directly manipulated the information to overload the method.
- ex. `operator>>` overload: Used `&in` parameter directly to read in the sequence allowing me to save memory. If I were to use `std::cin`, the program would have to allocate memory for the cin object. Although miniscule, saving the memory allows the program to be more efficient.
    - Similarly, in my `operator<<` overload, I used the &out parameter to be able to save memory on the allocation of an `std::cout` object
---
## Information about the repository

This repository contains the following:
- Starter code: `points2d.h`, `points2d.cc`, `test_points2d.cc`,`test_input_file.txt`, `expected_output.txt`, `Makefile` and `README.md`
- Assignment specification: `Fall22-Assignment1.pdf`
- Testing Document: `Testing_Document.pdf`

## Running the assignment

You will use this exact `Makefile` for your Assignment 1. Failure to do so will result in *deduction* of points.

To compile on terminal, type:

```bash
make clean
make all
```

To delete executables and object files, type:

```bash
make clean
```

To run, type:

```bash
./test_points3d
```

## Providing Input from Standard Input

To run with a given file that is redirected to standard input:

```bash
./test_points3d < test_input_file.txt
```
