#include "AppManager.h"
#include "Bibliography.h"
#include "SimpleIO.h"

void AppManager::run(int argc, char* argv[]) {
    Console console;
    if (argc < 2) {
        console.print("Usage: ");
        console.print(argv[0]);
        console.print(" <bib_file_1>\n");
        return;
    }

    Bibliography myBib(argv[1]);

    char response_buffer[4] = {0};
    console.print("Do you want to merge another file? (y/n): ");
    console.readLine(response_buffer, sizeof(response_buffer));
    char response = response_buffer[0];

    if (response == 'y' || response == 'Y') {
        char next_file[256] = {0};
        console.print("Enter filename to merge: ");
        console.readLine(next_file, sizeof(next_file));
        // Remove trailing newline from input
        char* newline = my_strchr(next_file, '\n');
        if (newline) *newline = '\0';
        
        Bibliography anotherBib(next_file);
        myBib = myBib + anotherBib;
    }
    
    console.print("\nSorted entries:\n\n");
    myBib.sort();
    myBib.displayAll();
}