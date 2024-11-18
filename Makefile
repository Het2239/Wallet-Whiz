# Compiler
CC = gcc
CFLAGS = -Wall -g

# Source files
SRC = main.c income.c report.c savings.c login.c expense.c

# Object files (replace .c with .o)
OBJ = $(SRC:.c=.o)

# Executable name
EXEC = main

# Default target
all: $(EXEC)

# Rule to create the executable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# Rule to compile each source file into an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJ) $(EXEC)
