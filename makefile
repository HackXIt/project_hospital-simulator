# Variables
CC=gcc
# WORKSPACE=/home/rini-debian/git-stash/HWSE2/project_hospital-simulator
# INC=-iquote${WORKSPACE}/inc
CFLAGS=-std=c99 -Wall -Wextra -pedantic -g -Wno-unused-parameter
BUILD=./build/
GTKFLAGS=`pkg-config --cflags gtk+-3.0`
GTKLIB=`pkg-config --libs gtk+-3.0`
# VPATH:=src:build
# These define where make should look for certain project files
vpath %.o ./build
vpath %.c ./src
vpath %.h ./src

# This is required for source-files without header-files
#$(BUILD)object.o: source.c
#	$(CC) $(CFLAGS) -c $< -o $@

# For singular targets with source & header-files
# target: source.c header.h
# 	$(CC) $(CFLAGS) $< -o $(BUILD)$@

# For singular targets with just source files and no custom includes
# target: test.c
# 	$(CC) $(CFLAGS) $< -o $(BUILD)$@

# Automatic variable for object files
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $(BUILD)$@

# Executed when just using 'make'
all: current

# Executed with: make current
current: main.c seat_rows.o
	$(CC) $(CFLAGS) $^ -o $(BUILD)$@

# Executed with: make test
test: test.c test.h
	$(CC) $(CFLAGS) $< -o $(BUILD)$@

simulator-gui: simulator_gui.c
	$(CC) $(GTKFLAGS) $< -o $(BUILD)$@ $(GTKLIB)

# Executed with: make clean
clean:
	rm $(BUILD)*.o $(BUILD)current