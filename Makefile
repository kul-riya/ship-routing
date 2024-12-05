# Compiler and flags
CC = gcc
CFLAGS = -Wall `pkg-config --cflags champlain-gtk`
LDFLAGS = `pkg-config --libs champlain-gtk`

# Directories for source and include files
SRC_DIR = src
INCLUDE_DIR = include

# List of object files to compile
OBJS = $(SRC_DIR)/mainmap.o $(SRC_DIR)/map.o

# Default target that will be executed when you run `make`
all: map_app

# Create the final executable from the object files
map_app: $(OBJS)
	$(CC) -o map_app $(OBJS) $(LDFLAGS)

# Compile mainmap.c into mainmap.o
$(SRC_DIR)/mainmap.o: $(SRC_DIR)/mainmap.c $(INCLUDE_DIR)/map.h
	$(CC) -c $(SRC_DIR)/mainmap.c -o $(SRC_DIR)/mainmap.o $(CFLAGS)

# Compile map.c into map.o
$(SRC_DIR)/map.o: $(SRC_DIR)/map.c $(INCLUDE_DIR)/map.h
	$(CC) -c $(SRC_DIR)/map.c -o $(SRC_DIR)/map.o $(CFLAGS)

# Clean up object files and the executable
clean:
	rm -f $(SRC_DIR)/*.o map_app
