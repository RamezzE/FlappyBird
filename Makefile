SRC_DIR := src
OBJ_DIR := obj

MAIN_CPP 	  := $(wildcard $(SRC_DIR)/main.cpp)
MAIN_OBJ := $(MAIN_CPP:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CPP_FILES       := $(filter-out $(MAIN_CPP), $(wildcard $(SRC_DIR)/*.cpp))
OBJ_FILES     := $(CPP_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

DEFINITON_FILE := $(wildcard $(SRC_DIR)/Definitions.hpp)

COMPILED_FLAGS       := -DSFML_STATIC -std=c++14 -g

INCLUDE_DIRECTORIES  := -I"SFML-2.5.1 (mingw)\include" 

LIB_DIRECTORIES := -L"SFML-2.5.1 (mingw)\lib"

LIB_FILES := -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lsfml-main -lfreetype
# LIB_FILES := -lsfml-graphics-s-d -lsfml-window-s-d -lsfml-system-s-d -lopengl32 -lwinmm -lgdi32 -lsfml-main-d -lfreetype

# APP_NAME := "FlarkyBird"
APP_NAME := "myApp"

.PHONY: all clean

all: build run

$(OBJ_FILES): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp $(DEFINITON_FILE) 
	 g++ -c $< -o $@ $(INCLUDE_DIRECTORIES) $(COMPILED_FLAGS)

#handle main.cpp error (no .h file)
$(MAIN_OBJ): $(MAIN_CPP)
	g++ -c $< -o $@ $(INCLUDE_DIRECTORIES) $(COMPILED_FLAGS)

build: $(OBJ_DIR) link

$(OBJ_DIR):
	@test -d "$(OBJ_DIR)" || mkdir $(OBJ_DIR)

link: $(OBJ_FILES) $(MAIN_OBJ)
	g++ $^ -o $(APP_NAME) $(LIB_DIRECTORIES) $(LIB_FILES)

run:
	$(APP_NAME)

clean:
	del $(OBJ_DIR)\*.o
	del $(APP_NAME).exe