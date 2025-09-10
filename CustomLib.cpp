#include "CustomLib.h"

// A large enough value for size_t
#if defined(SIZE_MAX)
#else
#define SIZE_MAX ((size_t)-1)
#endif

// A null pointer constant
#if defined(NULL)
#else
#define NULL 0
#endif


// ===============================================
// Custom implementations of <cstring> functions
// ===============================================

size_t my_strlen(const char* str) {
    if (!str) return 0;
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

char* my_strcpy(char* dest, const char* src) {
    if (!dest || !src) return dest;
    char* original_dest = dest;
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return original_dest;
}

int my_strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

char* my_strchr(const char* str, int c) {
    while (*str != '\0') {
        if (*str == c) {
            return (char*)str;
        }
        str++;
    }
    if (c == '\0') return (char*)str;
    return NULL;
}

char* my_strrchr(const char* str, int c) {
    const char* last_occurrence = NULL;
    while (*str != '\0') {
        if (*str == c) {
            last_occurrence = str;
        }
        str++;
    }
    if (c == '\0') return (char*)str;
    return (char*)last_occurrence;
}

char* my_strstr(const char* haystack, const char* needle) {
    if (!*needle) return (char*)haystack;
    const char* p1 = haystack;
    while (*p1) {
        const char* p1_begin = p1;
        const char* p2 = needle;
        while (*p1 && *p2 && *p1 == *p2) {
            p1++;
            p2++;
        }
        if (!*p2) return (char*)p1_begin;
        p1 = p1_begin + 1;
    }
    return NULL;
}

char* my_strtok(char* str, const char* delim) {
    static char* last_token = NULL;
    if (str) {
        last_token = str;
    }
    if (!last_token || *last_token == '\0') {
        return NULL;
    }

    // Skip leading delimiters
    char* token_start = last_token;
    const char* d;
    while (*token_start) {
        d = delim;
        int is_delim = 0;
        while (*d) {
            if (*token_start == *d) {
                is_delim = 1;
                break;
            }
            d++;
        }
        if (!is_delim) break;
        token_start++;
    }

    if (*token_start == '\0') {
        last_token = token_start;
        return NULL;
    }

    // Find the end of the token
    char* token_end = token_start;
    while (*token_end) {
        d = delim;
        while (*d) {
            if (*token_end == *d) {
                *token_end = '\0';
                last_token = token_end + 1;
                return token_start;
            }
            d++;
        }
        token_end++;
    }
    
    last_token = token_end;
    return token_start;
}

// ===============================================
// Custom implementations of <cctype> functions
// ===============================================

int my_isspace(int c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
}

int my_isdigit(int c) {
    return c >= '0' && c <= '9';
}

// ===============================================
// Custom implementations of <cstdlib> functions
// ===============================================

int my_atoi(const char* str) {
    if (!str) return 0;
    
    int result = 0;
    int sign = 1;

    // Skip leading whitespace
    while (my_isspace(*str)) {
        str++;
    }

    // Handle sign
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // Convert digits
    while (my_isdigit(*str)) {
        result = result * 10 + (*str - '0');
        str++;
    }

    return result * sign;
}

// ... (keep all existing function implementations) ...

// --- Add these new functions at the end of the file ---

// Converts an uppercase character to lowercase.
int my_tolower(int c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

// Compares two strings, ignoring case.
int my_strcasecmp(const char* s1, const char* s2) {
    if (s1 == s2) return 0;
    if (!s1) return -1;
    if (!s2) return 1;

    // Loop until characters differ or the end of a string is reached.
    while (my_tolower((unsigned char)*s1) == my_tolower((unsigned char)*s2)) {
        if (*s1 == '\0') {
            return 0; // Strings are identical
        }
        s1++;
        s2++;
    }
    // Return the difference of the first non-matching characters.
    return my_tolower((unsigned char)*s1) - my_tolower((unsigned char)*s2);
}