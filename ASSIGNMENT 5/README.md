# Comprehensive System Design and Implementation Challenge
## District Blood Bank Network

**Subject:** C Programming  
**Assignment:** Comprehensive System Design and Implementation Challenge  
**Total Marks:** 50  
**Case Study:** District Blood Bank Network

## 1. Project Description

The District Blood Bank Network is a C programming project designed to manage donor details and blood stock information across a central blood bank and multiple hospital storage units.

The system maintains donor information such as donor ID, name, blood group, age, phone number and last donation date. It also manages the available blood units for different blood groups.

The main objective of this project is to develop an efficient and reliable system using functions, recursion, pointers, dynamic memory allocation and file handling. The system helps register donors, identify eligible donors, update blood stock and store information permanently in files.

## 2. Objectives

- To divide the blood bank system into smaller functions.
- To implement recursive algorithms for digital root and power calculation.
- To understand pointer operations and pointer-based functions.
- To manage donor records using dynamic memory allocation.
- To store donor and stock details using text and binary files.
- To test program performance using different input sizes.
- To identify and prevent memory errors and invalid inputs.

## 3. Tasks Covered

### Part A – Design and Pseudocode (25 Marks)

**Task A1 – Decompose the Program into Functions**
- Identify the functions required for the blood bank system.
- Design function prototypes and parameter passing methods.
- Implement alternative methods to return multiple values.
- Analyse global variables, coupling and function reuse.

**Task A2 – Design with Recursion**
- Design a recursive digital root function.
- Implement recursive linear power and fast power calculation.
- Trace recursive calls and analyse the call stack.
- Explain recursion risks and complexity.

**Task A3 – Design with Pointers**
- Understand pointer arithmetic and array access.
- Design a function to find the blood group with the lowest stock.
- Develop a command-line interface using `argc` and `argv`.
- Compare pointer-returning and index-returning approaches.

**Task A4 – Design Dynamic Memory Use**
- Create a growable donor list using `malloc()` and `realloc()`.
- Double the capacity when the donor list becomes full.
- Handle memory allocation failures.
- Understand memory leaks, dangling pointers and double free errors.

**Task A5 – Design the File Storage**
- Store donor information in a text file using `fprintf()`.
- Store stock information in a binary file using `fwrite()`.
- Read records using `fread()`.
- Update stock records using `fseek()` without rewriting the entire file.

### Part B – Implementation and Experimental Investigation (25 Marks)

**Task B1 – Implement and Instrument Recursive Functions**
- Implement digital root and power functions.
- Test ordinary values, zero and one.
- Count recursive calls for different exponent values.
- Compare linear recursion, fast recursion and iterative methods.

**Task B2 – Engineer Adversarial Inputs**
- Test long donor names using input functions.
- Handle missing or read-only data files.
- Validate incorrect command-line arguments.
- Detect memory errors using AddressSanitizer or Valgrind.

**Task B3 – Text File vs Binary File**
- Write and read donor records in both formats.
- Compare file sizes and execution times.
- Measure the time required to update a binary record and rewrite a text file.
- Analyse the advantages and limitations of both formats.

**Task B4 – Final Engineering Decision**
- Implement a growable donor list.
- Generate a report of donors expected to become eligible within the next week.
- Measure memory usage and execution time.
- Verify memory safety and recommend a suitable storage strategy.

## 4. Technologies Used

- **Programming Language:** C
- **Compiler:** GCC
- **Editor:** Visual Studio Code / Code::Blocks
- **Concepts:** Functions, Structures, Recursion, Pointers, Dynamic Memory Allocation and File Handling
- **Testing Tools:** AddressSanitizer / Valgrind

## 5. Files Included

The project contains the following C source files:

1. `Task_A1_Function_Decomposition.c`
2. `Task_A2_Recursive_Design.c`
3. `Task_A3_Pointers_and_CLI.c`
4. `Task_A4_Dynamic_Donor_List.c`
5. `Task_A5_File_Storage.c`
6. `Task_B1_Recursive_Instrumentation.c`
7. `Task_B2_Adversarial_Input_Tests.c`
8. `Task_B3_Text_Binary_Comparison.c`
9. `Task_B4_Final_Growable_Report.c`

## 6. Compilation and Execution

Compile an individual C program using GCC:

```bash
gcc -std=c11 -Wall -Wextra Task_A1_Function_Decomposition.c -o task_a1
```

Run the compiled program:

```bash
./task_a1
```

Change the source filename and executable name when compiling other tasks.

## 7. Expected Outcomes

- Successful registration and management of donor records.
- Correct identification of eligible donors.
- Accurate blood stock updates.
- Proper implementation of recursive algorithms.
- Efficient use of pointers and dynamic memory.
- Successful storage and retrieval of records from files.
- Comparison of text and binary file performance.
- Improved program reliability through input validation and memory safety testing.

## 8. Conclusion

This project provides practical experience in designing and implementing a District Blood Bank Network using C programming. It demonstrates the use of functions, recursion, pointers, dynamic memory allocation and file handling to solve a real-world problem.

Through implementation and experimental investigation, the project helps improve programming skills, memory management, file operations, debugging and performance analysis. The developed system provides a basic model for managing donor information and blood stock efficiently.
