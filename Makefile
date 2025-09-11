# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g -fno-exceptions -fno-rtti

# Executable name
EXEC = bib_manager

# Source files and object files
SRCS = main.cpp AppManager.cpp Publication.cpp Bibliography.cpp CustomLib.cpp SyscallLib.cpp SimpleIO.cpp
OBJS = $(SRCS:.cpp=.o) String.o

# Default target
all: $(EXEC)

# Rule to link the final executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

# --- Dependency Rules ---
# These rules tell 'make' when to recompile a .cpp file because a header it depends on has changed.
# The compilation command itself is handled by 'make's built-in rules.

main.o: main.cpp AppManager.h
AppManager.o: AppManager.cpp AppManager.h Bibliography.h SimpleIO.h
Bibliography.o: Bibliography.cpp Bibliography.h Publication.h SimpleIO.h
Publication.o: Publication.cpp Publication.h CustomLib.h SimpleIO.h
SimpleIO.o: SimpleIO.cpp SimpleIO.h SyscallLib.h
SyscallLib.o: SyscallLib.cpp SyscallLib.h CustomLib.h
CustomLib.o: CustomLib.cpp CustomLib.h

# Phony target for cleaning up
clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean
String.o: String.cpp String.h
	$(CXX) $(CXXFLAGS) -c -o $@ String.cpp
