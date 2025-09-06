#include "SimpleIO.h"
#include "SyscallLib.h"

// --- Console Class Implementation ---

// Helper to convert a long integer to a string.
char* Console::long_to_str(long num, char* buffer) {
    int i = 0;
    bool is_negative = false;
    if (num == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return buffer;
    }
    if (num < 0) {
        is_negative = true;
        num = -num;
    }
    while (num != 0) {
        buffer[i++] = (num % 10) + '0';
        num = num / 10;
    }
    if (is_negative) {
        buffer[i++] = '-';
    }
    buffer[i] = '\0';
    reverse(buffer, i);
    return buffer;
}

// Helper to reverse a string.
void Console::reverse(char* str, int length) {
    char* start = str;
    char* end = str + length - 1;
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

void Console::print(const char* str) {
    if (!str) return;
    Syscall::write(1, str, my_strlen(str)); // fd 1 is stdout
}

void Console::print(long num) {
    char buffer[21]; // Max length for a 64-bit long
    long_to_str(num, buffer);
    print(buffer);
}

long Console::readLine(char* buffer, size_t size) {
    return Syscall::read(0, buffer, size - 1); // fd 0 is stdin
}

// --- File Class Implementation ---

File::File() : fd(-1), buffer_pos(0), buffer_end(0) {}

File::~File() {
    close();
}

bool File::open(const char* path) {
    fd = Syscall::open(path, O_RDONLY);
    return fd >= 0;
}

void File::close() {
    if (fd >= 0) {
        Syscall::close(fd);
        fd = -1;
    }
}

// Reads a file one character at a time until a newline is found.
// It uses an internal buffer to reduce the number of system calls.
bool File::readLine(char* line, size_t size) {
    if (fd < 0) return false;
    size_t i = 0;
    while (i < size - 1) {
        if (buffer_pos >= buffer_end) {
            // Buffer is empty, read more data from the file
            buffer_end = Syscall::read(fd, read_buffer, sizeof(read_buffer));
            buffer_pos = 0;
            if (buffer_end <= 0) {
                line[i] = '\0';
                return i > 0; // Return true if we read something before EOF
            }
        }
        char c = read_buffer[buffer_pos++];
        if (c == '\n') {
            break; // End of line
        }
        line[i++] = c;
    }
    line[i] = '\0';
    return true;
}