// String.h - Custom dynamic String class (replaces std::string and raw char*).

#ifndef STRING_H
#define STRING_H

class String {
private:
    char* data;
    int len;
    void copyFrom(const char* src);
    void cleanup();

public:
    String();
    String(const char* s);
    String(const String& other);
    ~String();

    String& operator=(const String& other);
    String& operator=(const char* s);

    const char* c_str() const;
    int length() const;

    bool operator<(const String& other) const;
    bool operator==(const String& other) const;

    static int compareIgnoreCase(const String& a, const String& b);
};

#endif
