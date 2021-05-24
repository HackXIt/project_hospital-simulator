# Variables
CC=gcc
# WORKSPACE=/home/rini-debian/git-stash/HWSE2/project_hospital-simulator
# INC=-iquote${WORKSPACE}/inc
CFLAGS=-Wall -Wextra -pedantic -g -Wno-unused-parameter
BUILD=./build/
# For GTK
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

gtk3.o: gtk3.c gtk3.h
	$(CC) $(GTKFLAGS) -c $< -o $(BUILD)$@ $(GTKLIB)

# Automatic variable for object files
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $(BUILD)$@

# Executed when just using 'make'
all: current

# Executed with: make current
current: main.c seat_rows.o persons.o gtk3.o
	$(CC) $(GTKFLAGS) $(CFLAGS) $^ -o $(BUILD)$@ $(GTKLIB)

# Executed with: make test
test: test.c test.h
	$(CC) $(CFLAGS) $< -o $(BUILD)$@

# Executed with: make gtk
gtk: gtk3.c gtk3.h
	$(CC) $(GTKFLAGS) $< -o $(BUILD)$@ $(GTKLIB)

# Executed with: make clean
clean:
	rm $(BUILD)*.o $(BUILD)current

# For targets which don't have any input-files
.PHONY: clean