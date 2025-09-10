#include "SyscallLib.h"

// Each function uses inline assembly to load registers with the correct
// syscall number and arguments, then executes the 'syscall' instruction
// to trap into the kernel and perform the operation.

long Syscall::write(int fd, const void* buf, size_t count) {
    long ret;
    asm volatile(
        "syscall"
        : "=a"(ret) // Output: return value in rax
        : "a"(1),    // Input: syscall number for write is 1
          "D"(fd),   // Input: first argument (fd) in rdi
          "S"(buf),  // Input: second argument (buf) in rsi
          "d"(count) // Input: third argument (count) in rdx
        : "rcx", "r11", "memory" // Clobbered registers
    );
    return ret;
}

long Syscall::read(int fd, void* buf, size_t count) {
    long ret;
    asm volatile(
        "syscall"
        : "=a"(ret)
        : "a"(0),    // syscall number for read is 0
          "D"(fd),
          "S"(buf),
          "d"(count)
        : "rcx", "r11", "memory"
    );
    return ret;
}

int Syscall::open(const char* pathname, int flags) {
    int ret;
    asm volatile(
        "syscall"
        : "=a"(ret)
        : "a"(2),    // syscall number for open is 2
          "D"(pathname),
          "S"(flags)
        : "rcx", "r11", "memory"
    );
    return ret;
}

int Syscall::close(int fd) {
    int ret;
    asm volatile(
        "syscall"
        : "=a"(ret)
        : "a"(3),    // syscall number for close is 3
          "D"(fd)
        : "rcx", "r11"
    );
    return ret;
}