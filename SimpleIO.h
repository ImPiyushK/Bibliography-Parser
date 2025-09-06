#ifndef SIMPLE_IO_H
#define SIMPLE_IO_H

#include "CustomLib.h"

// A class to handle writing to and reading from the console.
class Console {
private:
    void reverse(char* str, int length);
    char* long_to_str(long num, char* buffer);

public:
    void print(const char* str);
    void print(long num);
    long readLine(char* buffer, size_t size);
};

// A class to handle reading from files.
class File {
private:
    int fd;
    char read_buffer[1024];
    long buffer_pos;
    long buffer_end;

public:
    File();
    ~File();

    bool open(const char* path);
    bool readLine(char* line, size_t size);
    void close();
};

#endif // SIMPLE_IO_H