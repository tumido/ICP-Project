# VARIABLES
#---------------------------------------------------------------------
CPP = g++
CPPFLAGS = -std=c++11 -pedantic -Wall -Werror -fPIC
# SOURCE = Action.cpp  GameGenerator.cpp  GameManager.cpp  MazeBoard.cpp  MazeCard.cpp  MazeField.cpp  PathFinder.cpp  Player.cpp # temporary solution, some files droped because of errors
SOURCE = $(shell ls core)
OBJECTS = $(SOURCE:%.cpp=../build/%.o)

all: $(OBJECTS)

# RULES for objects
#---------------------------------------------------------------------
../build/%.o: core/%.cpp
	$(CPP) $(CPPFLAGS) -c $^ -o $@
