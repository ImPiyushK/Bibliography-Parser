// Publication.h - Defines Publication with private String fields, operator<, and controlled setters.
#ifndef PUBLICATION_H
#define PUBLICATION_H

#include "String.h"

class Publication {
private:
    String year;
    String title;
    String authors;
    String booktitle;
    String pdf;
    String doi;
    String abbreviation;
    String code;
    String presentation;

public:
    Publication();
    Publication(const Publication& other);
    ~Publication();
    Publication& operator=(const Publication& other);

    bool operator<(const Publication& other) const;

    void setYear(const char* s);
    void setTitle(const char* s);
    void setAuthors(const char* s);
    void setBooktitle(const char* s);
    void setPdf(const char* s);
    void setDoi(const char* s);
    void setAbbreviation(const char* s);
    void setCode(const char* s);
    void setPresentation(const char* s);

    void display() const;
};

#endif // PUBLICATION_H