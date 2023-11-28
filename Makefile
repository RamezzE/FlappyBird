SRC_DIR := src
CPP_DIR := $(SRC_DIR)/cpp
HPP_DIR := $(SRC_DIR)/hpp
OBJ_DIR := obj

MAIN_CPP 	  := $(wildcard $(CPP_DIR)/main.cpp)
MAIN_OBJ := $(MAIN_CPP:$(CPP_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CPP_FILES       := $(filter-out $(MAIN_CPP), $(wildcard $(CPP_DIR)/*.cpp))
OBJ_FILES     := $(CPP_FILES:$(CPP_DIR)/%.cpp=$(OBJ_DIR)/%.o)

DEFINITON_FILE := $(wildcard $(HPP_DIR)/Definitions.hpp)

CC = g++

# CFLAGS       := -std=c++14 -g -gdwarf-2 -fno-omit-frame-pointer
CFLAGS       := -std=c++14

CPPFLAGS  := -I"SFML\include"

LDFLAGS := -L"SFML\lib"

# LDLIBS := -lsfml-graphics-d -lsfml-window-d -lsfml-system-d -lsfml-audio-d
LDLIBS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# APP_NAME := "FlarkyBird"
TARGET := "myApp.exe"

.PHONY: all clean

all: build run

$(OBJ_FILES): $(OBJ_DIR)/%.o: $(CPP_DIR)/%.cpp $(HPP_DIR)/%.hpp $(DEFINITON_FILE) 
	$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

#handle main.cpp error (no .h file)
$(MAIN_OBJ): $(MAIN_CPP)
	$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

build: $(OBJ_DIR) link

$(OBJ_DIR):
	@test -d "$(OBJ_DIR)" || mkdir $(OBJ_DIR)

link: $(OBJ_FILES) $(MAIN_OBJ)
	$(CC) $^ -o $(TARGET) $(LDFLAGS) $(LDLIBS)

run:
	$(TARGET)

clean:
	del $(OBJ_DIR)\*.o
	del $(TARGET)