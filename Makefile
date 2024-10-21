# Compiler to use
CC = gcc

# Flags to compile with
CFLAGS = -Wall -Wextra -Werror

# Source files
SOURCES = main.c

# Object files
OBJS = $(SOURCES:.c=.o)

# Target executable
TARGET = my_bsq

# Default target
all: $(TARGET)

# Linking the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compiling source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and target
clean:
	rm -f $(OBJS) $(TARGET)

# Clean and then rebuild everything
rebuild: clean all

.PHONY: all clean rebuild