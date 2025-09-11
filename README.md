Assignment 2: 
Bibliography Parser in C++

Description:
------------
This project implements a bibliography manager in C++, converted from a basic C parser.
It is designed to read and parse .bib files, store publication details, and
display them in a sorted order.

Key requirements and how they are satisfied:
1. Use of Object-Oriented Principles:
   - Classes: Publication, Bibliography, String, AppManager.
   - Data abstraction and data hiding: all fields are private, access via setters.
   - Controlled interfaces: only necessary functions are public.

2. Removal of C-style strings and fixed buffers:
   - All publication fields (year, title, authors, pdf, code, presentation, etc.)
     use a custom String class (dynamic allocation).
   - No use of std::string or STL containers.
   - No <cstdio>, <cstring>, <string>, or <vector> headers.

3. Additional publication details:
   - Each Publication retains URL of PDF, URL of source code, and URL of presentation.

4. Sorting requirement:
   - operator< is overloaded in Publication to sort by:
       - Year (descending order).
       - Title (lexicographic, case-insensitive).
       - Authors (tie-breaker).

5. Merging bibliographies:
   - operator+ is overloaded in Bibliography to merge entries from two .bib files.

6. Constructors and destructors:
   - Rule of Three implemented in String, Publication, and Bibliography classes.
   - Proper cleanup of dynamically allocated memory.

7. Input validation:
   - Year is checked to ensure it is numeric.
   - Invalid years are set to 0 with a warning.

8. Compliance with restrictions:
   - No standard C++ libraries or templates used.
   - All I/O handled by custom Console class (SimpleIO), no printf/scanf.

Technique of Building:
----------------------
- Ensure you have g++ installed.
- Run `make` in the project root directory. This compiles all source files and
  produces the executable `bib_manager`.

Usage:
------
./bib_manager <bib_file_1> [bib_file_2]

- The program will parse the first .bib file.
- It prompts if you want to merge another file (using + operator).
- It sorts the combined list and displays all publications.

Example:
--------
$ ./bib_manager ref.bib_doi.bib

Output:
Parsed 27 entries from first file.
Do you want to merge another file? (y/n): n

Sorted entries:
Year: 2025
Title: CLOUD-CODEC: A New Way of Storing Traffic Cameras Footage at Scale
Authors: Kim, Hoyoung; Khudoyberdiev, Azimbek; ...
Booktitle: ACM Transactions on Multimedia Computing, Communications, and Applications
PDF: https://faculty.iiitd.ac.in/~arani/assets/pdf/tomm25.pdf
...

Submission Notes:
-----------------
- Only source files, headers, Makefile, and README are included.
- No object files or binaries are committed (per instructions).
