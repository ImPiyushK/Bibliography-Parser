// main.cpp - Entry point using Console I/O; loads, merges, sorts, and displays Bibliography.

#include "Bibliography.h"
#include "SimpleIO.h"

int main(int argc, char* argv[]) {
    Console console;
    if (argc < 2) {
        console.print("Usage: ");
        console.print(argv[0]);
        console.print(" <bib_file_1> [bib_file_2] ...\n");
        return 1;
    }

    Bibliography myBib(argv[1]);

    char response_buffer[16] = {0};
    console.print("Do you want to merge another file? (y/n): ");
    console.readLine(response_buffer, sizeof(response_buffer));
    char response = response_buffer[0];

    if (response == 'y' || response == 'Y') {
        char next_file[1024] = {0};
        console.print("Enter filename to merge: ");
        console.readLine(next_file, sizeof(next_file));
        char* newline = my_strchr(next_file, '\n');
        if (newline) *newline = '\0';
        Bibliography anotherBib(next_file);
        myBib = myBib + anotherBib;
    }

    console.print("\nSorted entries:\n\n");
    myBib.sort();
    myBib.displayAll();

    return 0;
}
