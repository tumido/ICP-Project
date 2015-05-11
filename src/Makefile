# VARIABLES
#---------------------------------------------------------------------
CPP = g++
CPPFLAGS = -std=c++11 -fPIC #-pedantic -Wall -Werror
# SOURCE = Action.cpp  GameGenerator.cpp  GameManager.cpp  MazeBoard.cpp  MazeCard.cpp  MazeField.cpp  PathFinder.cpp  Player.cpp # temporary solution, some files droped because of errors
SOURCE = $(shell ls core)
OBJECTS = $(SOURCE:%.cpp=../build/%.o)

all: $(OBJECTS) LabyrinthCLI.o

# RULES for objects
#---------------------------------------------------------------------
LabyrinthCLI.o: cli/LabyrinthCLI.cpp
	$(CPP) $(CPPFLAGS) -c $^ -o ../build/$@

../build/%.o: core/%.cpp
	$(CPP) $(CPPFLAGS) -c $^ -o $@
