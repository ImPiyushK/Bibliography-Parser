// String.cpp - Implements custom String (constructors, destructors, copy/assign, comparisons).

#include "String.h"
#include "CustomLib.h"
void String::copyFrom(const char* src) {
    if (!src) { data = NULL; len = 0; return; }
    len = my_strlen(src);
    data = new char[len+1];
    my_strcpy(data, src);
}
void String::cleanup() {
    delete[] data;
    data = NULL;
    len = 0;
}
String::String(): data(NULL), len(0) {}
String::String(const char* s): data(NULL), len(0) { copyFrom(s); }
String::String(const String& other): data(NULL), len(0) { copyFrom(other.data); }
String::~String() { cleanup(); }

String& String::operator=(const String& other) {
    if (this != &other) { cleanup(); copyFrom(other.data); }
    return *this;
}
String& String::operator=(const char* s) {
    cleanup(); copyFrom(s); return *this;
}

const char* String::c_str() const { return data ? data : ""; }
int String::length() const { return len; }

bool String::operator<(const String& other) const {
    return my_strcmp(this->c_str(), other.c_str()) < 0;
}
bool String::operator==(const String& other) const {
    return my_strcmp(this->c_str(), other.c_str()) == 0;
}

int String::compareIgnoreCase(const String& a, const String& b) {
    return my_strcasecmp(a.c_str(), b.c_str());
}
