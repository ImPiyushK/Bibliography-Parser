# Bibliography Parser

This project is a small bibliography manager written in C++. It started from a
basic C parser and was converted into an object-oriented design. The program
reads .bib files, extracts publication details, and prints them in sorted order.

How the requirements were met:
- OOP principles: the code is split into classes (Publication, Bibliography,
  String, AppManager). Fields are private, and only a limited public interface
  is exposed.
- No fixed-length C strings: instead of raw char*, a custom String class was
  created which manages dynamic memory safely. This avoids the problems of
  buffer sizes and also removes the need for <string> or STL containers.
- Extra fields: each publication keeps the PDF URL, code URL, and presentation
  URL, as asked in the assignment.
- Sorting: operator< is implemented in Publication so that the list is ordered
  first by year (descending), then by title in lexicographic order, and finally
  by authors if needed.
- Adding entries: operator+ is implemented in Bibliography to merge entries
  from two different .bib files into a single list.
- Constructors and destructors: the “rule of three” is followed in String,
  Publication and Bibliography to make sure copies and clean-up work correctly.
- Input validation: years are checked to be numeric; if not, they are replaced
  with 0 and a warning is printed.
- Restrictions: no standard C++ library classes or templates are used. All I/O
  is done with the custom Console class from SimpleIO instead of printf/scanf.

Building and running:
- To build, just run `make` in the project folder. This will compile all the
  sources and create the executable `bib_manager`.
- To run, use:
    ./bib_manager <bib_file_1> [bib_file_2]

The program will read the first bib file, ask whether you want to merge another
file, and then print all entries in sorted order.

Example run:
    $ ./bib_manager ref.bib_doi.bib
    Parsed 27 entries from first file.
    Do you want to merge another file? (y/n): n

    Sorted entries:
    Year: 2025
    Title: CLOUD-CODEC: A New Way of Storing Traffic Cameras Footage at Scale
    Authors: Kim, Hoyoung; Khudoyberdiev, Azimbek; ...
    Booktitle: ACM Transactions on Multimedia Computing, Communications, and Applications
    PDF: https://faculty.iiitd.ac.in/~arani/assets/pdf/tomm25.pdf
    ...

