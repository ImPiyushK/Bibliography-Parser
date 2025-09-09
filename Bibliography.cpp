// Bibliography.cpp - Implements Bibliography: manages list of Publications, parsing, + operator, validation.
#include "Bibliography.h"
#include "CustomLib.h"
#include "SimpleIO.h"

Bibliography::Bibliography() : publications(NULL), count(0), capacity(0) {}

Bibliography::Bibliography(const char* filename) : publications(NULL), count(0), capacity(0) {
    parseFile(filename);
}

Bibliography::Bibliography(const Bibliography& other) : publications(NULL), count(0), capacity(0) {
    capacity = other.capacity;
    count = other.count;
    if (capacity > 0) {
        publications = new Publication[capacity];
        for (int i = 0; i < count; ++i) {
            publications[i] = other.publications[i];
        }
    }
}

Bibliography::~Bibliography() {
    delete[] publications;
}

Bibliography& Bibliography::operator=(const Bibliography& other) {
    if (this != &other) {
        delete[] publications;

        publications = NULL;
        capacity = other.capacity;
        count = other.count;

        if (capacity > 0) {
            publications = new Publication[capacity];
            for (int i = 0; i < count; ++i) {
                publications[i] = other.publications[i];
            }
        }
    }
    return *this;
}

void Bibliography::resize() {
    int newCapacity = (capacity == 0) ? 10 : capacity * 2;
    Publication* newPublications = new Publication[newCapacity];
    for (int i = 0; i < count; ++i) {
        newPublications[i] = publications[i];
    }
    delete[] publications;
    publications = newPublications;
    capacity = newCapacity;
}

void Bibliography::addPublication(const Publication& pub) {
    if (count == capacity) {
        resize();
    }
    publications[count++] = pub;
}

char* Bibliography::trim(char* str) {
    char* end;
    while (*str && my_isspace((unsigned char)*str)) str++;
    if (*str == 0) return str;
    end = str + my_strlen(str) - 1;
    while (end > str && my_isspace((unsigned char)*end)) end--;
    end[1] = '\0';
    return str;
}

char* Bibliography::extractValue(char* line) {
    char* valueStart = my_strchr(line, '{');
    if (!valueStart) valueStart = my_strchr(line, '"');
    if (!valueStart) return NULL;

    valueStart++;

    char* valueEnd = my_strrchr(valueStart, '}');
    if (!valueEnd) valueEnd = my_strrchr(valueStart, '"');
    if (!valueEnd) return NULL;
    
    *valueEnd = '\0';
    return trim(valueStart);
}

void Bibliography::parseFile(const char* filename) {
    Console console;
    File file;
    if (!file.open(filename)) {
        console.print("Error: Cannot open file ");
        console.print(filename);
        console.print("\n");
        return;
    }

    int entry_count = 0;
    char line_buffer[4096];
    bool inEntry = false;
    Publication currentPub;

    while (file.readLine(line_buffer, sizeof(line_buffer))) {
        char* trimmedLine = trim(line_buffer);
        if (my_strlen(trimmedLine) == 0) continue;
        
        if (trimmedLine[0] == '@') {
            if (inEntry) addPublication(currentPub);
            entry_count++;
            inEntry = true;
            currentPub = Publication();
            continue;
        }

        if (!inEntry) continue;
        
        if (trimmedLine[0] == '}') {
            addPublication(currentPub);
            inEntry = false;
            continue;
        }

        char* equalsPos = my_strchr(trimmedLine, '=');
        if (equalsPos) {
            *equalsPos = '\0';
            char* key = trim(trimmedLine);
            char* value = extractValue(equalsPos + 1);

            if (!value) continue;

            if (my_strcmp(key, "year") == 0) currentPub.setYear(value);
            else if (my_strcmp(key, "title") == 0) currentPub.setTitle(value);
            else if (my_strcmp(key, "author") == 0) currentPub.setAuthors(value);
            else if (my_strcmp(key, "booktitle") == 0) currentPub.setBooktitle(value);
            else if (my_strcmp(key, "pdf") == 0) currentPub.setPdf(value);
            else if (my_strcmp(key, "doi") == 0) currentPub.setDoi(value);
            else if (my_strcmp(key, "abbr") == 0) currentPub.setAbbreviation(value);
            else if (my_strcmp(key, "code") == 0) currentPub.setCode(value);
        }
    }
    
    console.print("Parsed ");
    console.print((long)entry_count);
    console.print(" entries from first file.\n");
    file.close();
}

void Bibliography::sort() {
    for (int i = 1; i < count; i++) {
        Publication key = publications[i];
        int j = i - 1;
        while (j >= 0 && key < publications[j]) {
            publications[j + 1] = publications[j];
            j = j - 1;
        }
        publications[j + 1] = key;
    }
}

void Bibliography::displayAll() const {
    for (int i = 0; i < count; ++i) {
        publications[i].display();
    }
}

Bibliography Bibliography::operator+(const Bibliography& other) const {
    Bibliography result;
    for (int i = 0; i < this->count; ++i) {
        result.addPublication(this->publications[i]);
    }
    for (int i = 0; i < other.count; ++i) {
        result.addPublication(other.publications[i]);
    }
    return result;
}