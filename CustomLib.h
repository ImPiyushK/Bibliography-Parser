#ifndef CUSTOM_LIB_H
#define CUSTOM_LIB_H

// --- Custom definitions to avoid including standard headers ---
#ifndef NULL
    #define NULL 0
#endif
typedef unsigned long size_t;

// Custom implementations of <cstring> functions
size_t my_strlen(const char* str);
char* my_strcpy(char* dest, const char* src);
int my_strcmp(const char* s1, const char* s2);
char* my_strchr(const char* str, int c);
char* my_strrchr(const char* str, int c);
char* my_strstr(const char* haystack, const char* needle);
char* my_strtok(char* str, const char* delim);
int my_strcasecmp(const char* s1, const char* s2); // <-- ADD THIS LINE

// Custom implementations of <cctype> functions
int my_isspace(int c);
int my_isdigit(int c);
int my_tolower(int c); // <-- ADD THIS LINE

// Custom implementations of <cstdlib> functions
int my_atoi(const char* str);

#endif // CUSTOM_LIB_H