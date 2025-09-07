// Publication.cpp - Implements Publication: safe memory, operator< sorting, display with formatted authors.

#include "Publication.h"
#include "CustomLib.h"
#include "SimpleIO.h"
#include "String.h"

Publication::Publication() {}
Publication::Publication(const Publication& other) { *this = other; }
Publication::~Publication() {}
Publication& Publication::operator=(const Publication& other) {
    if (this != &other) {
        year = other.year;
        title = other.title;
        authors = other.authors;
        booktitle = other.booktitle;
        pdf = other.pdf;
        doi = other.doi;
        abbreviation = other.abbreviation;
        code = other.code;
        presentation = other.presentation;
    }
    return *this;
}

void Publication::setYear(const char* s) { year = s; }
void Publication::setTitle(const char* s) { title = s; }
void Publication::setAuthors(const char* s) { authors = s; }
void Publication::setBooktitle(const char* s) { booktitle = s; }
void Publication::setPdf(const char* s) { pdf = s; }
void Publication::setDoi(const char* s) { doi = s; }
void Publication::setAbbreviation(const char* s) { abbreviation = s; }
void Publication::setCode(const char* s) { code = s; }
void Publication::setPresentation(const char* s) { presentation = s; }

bool Publication::operator<(const Publication& other) const {
    int year_this = my_atoi(year.c_str());
    int year_other = my_atoi(other.year.c_str());
    if (year_this != year_other) return year_this > year_other;
    int cmp = String::compareIgnoreCase(this->title, other.title);
    if (cmp != 0) return cmp < 0;
    cmp = String::compareIgnoreCase(this->authors, other.authors);
    if (cmp != 0) return cmp < 0;
    return false;
}

void Publication::display() const {
    Console console;
    if (year.length()) { console.print("Year: "); console.print(year.c_str()); console.print("\n"); }
    if (title.length()) { console.print("Title: "); console.print(title.c_str()); console.print("\n"); }
    if (authors.length()) {
        String a = authors;
        char* authors_copy = new char[a.length()+1];
        my_strcpy(authors_copy, a.c_str());
        char* current = my_strstr(authors_copy, " and ");
        while (current) {
            current[0] = ';'; current[1] = ' ';
            char* rest = current + 5;
            char* target = current + 2;
            while (*rest) { *target++ = *rest++; }
            *target = '\0';
            current = my_strstr(current + 1, " and ");
        }
        console.print("Authors: "); console.print(authors_copy); console.print("\n");
        delete[] authors_copy;
    }
    if (booktitle.length()) { console.print("Booktitle: "); console.print(booktitle.c_str()); console.print("\n"); }
    if (pdf.length()) { console.print("PDF: "); console.print(pdf.c_str()); console.print("\n"); }
    if (presentation.length()) { console.print("Presentation: "); console.print(presentation.c_str()); console.print("\n"); }
    if (code.length()) { console.print("Code: "); console.print(code.c_str()); console.print("\n"); }
    if (doi.length()) { console.print("DOI: "); console.print(doi.c_str()); console.print("\n"); }
    if (abbreviation.length()) { console.print("Abbreviation: "); console.print(abbreviation.c_str()); console.print("\n"); }
    console.print("\n");
}
