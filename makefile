#all: game

#game: src/Graph.cpp src/Node.cpp src/CombatUnit.cpp src/PlayerCharacter.cpp src/Gameworld.cpp src/Main.cpp
#	g++ src/Graph.cpp src/Node.cpp src/CombatUnit.cpp src/PlayerCharacter.cpp src/Gameworld.cpp src/Main.cpp -std=c++11 -o bin/game

SRC_DIR := src
OBJ_DIR := obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS := -std=c++11
CPPFLAGS := ...
CXXFLAGS := ...

bin/game: $(SRC_FILES)
	g++ $^ $(LDFLAGS) -o $@ 

