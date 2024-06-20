# Directories
DIR_Config = ./lib/Config
DIR_EPD = ./lib/e-Paper
DIR_FONTS = ./lib/Fonts
DIR_GUI = ./lib/GUI
DIR_BIN = ./bin

# Source files
SRC_C = $(wildcard $(DIR_Config)/*.c $(DIR_EPD)/*.c $(DIR_GUI)/*.c $(DIR_FONTS)/*.c ./lib/*.c ./lib/*/*.c)
OBJ_C = $(patsubst ./lib/%.c, $(DIR_BIN)/%.o, $(wildcard ./lib/*.c)) \
        $(patsubst ./lib/*/%.c, $(DIR_BIN)/%.o, $(wildcard ./lib/*/*.c))
OBJ_CPP = $(DIR_BIN)/main.o
OBJ_O = $(OBJ_C) $(OBJ_CPP)

# Compiler settings
TARGET = epd
CC = gcc
CXX = g++
CFLAGS = -g -O -ffunction-sections -fdata-sections -Wall -D RPI -I ./lib
CXXFLAGS = $(CFLAGS)

# Check the architecture and set compiler variables accordingly
ARCH := $(shell uname -m)
ifeq ($(ARCH), x86_64)
    CC = arm-linux-gnueabihf-gcc
    CXX = arm-linux-gnueabihf-g++
endif

# Libraries
LIBS = -llgpio -lgpiod -lm

# Create bin directory if it doesn't exist
$(shell mkdir -p $(DIR_BIN))

# Default target
.PHONY: RPI clean

RPI: $(TARGET)

$(TARGET): $(OBJ_O)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

# Compile .c files
$(DIR_BIN)/%.o: $(DIR_Config)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_BIN)/%.o: $(DIR_EPD)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_BIN)/%.o: $(DIR_GUI)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_BIN)/%.o: $(DIR_FONTS)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile main.cpp
$(DIR_BIN)/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the build directory
clean:
	rm -f $(DIR_BIN)/*.o $(TARGET)
