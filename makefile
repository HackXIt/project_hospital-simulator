CC=gcc
WORKSPACE=/home/rini-debian/git-stash/HWSE2/project_hospital-simulator
INC=-iquote${WORKSPACE}/inc
CFLAGS=-std=c99 -Wall -Wextra -pedantic -g -Wno-unused-parameter
BUILD=./build/
# VPATH:=src:build
# These define where make should look for certain project files
vpath %.o ./build
vpath %.c ./src
vpath %.h ./inc

# This is required for source-files without header-files
#$(BUILD)object.o: source.c
#	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# For singular targets with source & header-files
# target: source.c header.h
# 	$(CC) $(CFLAGS) $(INC) $< -o $(BUILD)$@

# For singular targets with just source files and no custom includes
# target: test.c
# 	$(CC) $(CFLAGS) $< -o $(BUILD)$@

# Automatic variable for object files
%.o: %.c %.h
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Executed when just using 'make'
all: current

# Executed with: make current
current: test.c test.h
	$(CC) $(CFLAGS) $(INC) $< -o $(BUILD)$@

# Executed with: make clean
clean:
	rm $(BUILD)*.o $(BUILD)pipetest