# Variables
CC=gcc
# WORKSPACE=/home/rini-debian/git-stash/HWSE2/project_hospital-simulator
# INC=-iquote${WORKSPACE}/inc
CFLAGS=$(INC) -Wall -Wextra -pedantic -g -Wno-unused-parameter
INC=-Iinc
BUILD=./build/
SOURCE=./src/
# For GTK
GTKFLAGS=`pkg-config --cflags gtk+-3.0`
GTKLIB=`pkg-config --libs gtk+-3.0`
# VPATH:=src:build
# These define where make should look for certain project files, if necessary
vpath %.o ./build
vpath %.c ./src
vpath %.h ./inc

_OBJECTS=gtk3.o seat_rows.o persons.o
OBJECTS=$(patsubst %,$(BUILD)%,$(_OBJECTS))

# This is required for source-files without header-files
#$(BUILD)object.o: source.c
#	$(CC) $(CFLAGS) -c $< -o $@

# For singular targets with source & header-files
# target: source.c header.h
# 	$(CC) $(CFLAGS) $< -o $(BUILD)$@

# For singular targets with just source files and no custom includes
# target: test.c
# 	$(CC) $(CFLAGS) $< -o $(BUILD)$@

$(BUILD)gtk3.o: gtk3.c
	$(CC) $(CFLAGS) $(GTKFLAGS) -c $< -o $@ $(GTKLIB)

# Automatic variable for object files
$(BUILD)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Executed when just using 'make'
all: current

# Executed with: make current
current: main.c $(OBJECTS)
	$(CC) $(CFLAGS) $(GTKFLAGS) $^ -o $(BUILD)$@ $(GTKLIB)

# Executed with: make test
$(BUILD)test: test.c
	$(CC) $(CFLAGS) $< -o $(BUILD)$@

# Executed with: make gtk
$(BUILD)gtk: gtk3.c
	$(CC) $(GTKFLAGS) $< -o $@ $(GTKLIB)

# Executed with: make clean
clean:
	rm $(BUILD)*.o $(BUILD)current

# For targets which don't have any input-files
.PHONY: clean