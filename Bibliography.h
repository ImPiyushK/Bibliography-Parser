#ifndef BIBLIOGRAPHY_H
#define BIBLIOGRAPHY_H

#include "Publication.h"

class Bibliography {
private:
    Publication* publications;
    int count;
    int capacity;

    // Private helpers
    void resize();
    void addPublication(const Publication& pub);
    char* trim(char* str);
    char* extractValue(char* line);
    void parseFile(const char* filename);

public:
    // Constructors and Destructor
    Bibliography();
    explicit Bibliography(const char* filename); // 'explicit' prevents implicit conversions
    Bibliography(const Bibliography& other);
    ~Bibliography();

    // Operators
    Bibliography& operator=(const Bibliography& other);
    Bibliography operator+(const Bibliography& other) const;

    // Public interface
    void sort();
    void displayAll() const;
};

#endif // BIBLIOGRAPHY_H