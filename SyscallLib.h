#ifndef SYSCALL_LIB_H
#define SYSCALL_LIB_H

#include "CustomLib.h" // For size_t

// File flags for sys_open
#define O_RDONLY 0

namespace Syscall {
    // Writes 'count' bytes from 'buf' to a file descriptor 'fd'.
    // Returns the number of bytes written.
    long write(int fd, const void* buf, size_t count);

    // Reads 'count' bytes from 'fd' into 'buf'.
    // Returns the number of bytes read.
    long read(int fd, void* buf, size_t count);

    // Opens a file and returns its integer file descriptor.
    int open(const char* pathname, int flags);

    // Closes a file descriptor.
    int close(int fd);
}

#endif // SYSCALL_LIB_H