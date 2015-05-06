# VARIABLES
#---------------------------------------------------------------------
CPP = g++
CPPFLAGS = -std=c++11 -pedantic -Wall -Werror
PROGS = client_cli # client_gui
SOURCE = Action.cpp  GameGenerator.cpp  GameManager.cpp  MazeBoard.cpp  MazeCard.cpp  MazeField.cpp  PathFinder.cpp  Player.cpp # temporary solution, some files droped because of errors
# SOURCE = $(shell ls src)
OBJECTS = $(SOURCE:%.cpp=build/%.o)

# RULES for programs
#---------------------------------------------------------------------
all: $(PROGS)

client_cli: client_cli.cpp $(OBJECTS)
	$(CPP) $(CPPFLAGS) $^ -o $@

client_gui: client_gui.cpp
	$(CPP) $(CPPFLAGS) $< -o $@


# RULES for objects
#---------------------------------------------------------------------

build/%.o: src/%.cpp
	$(CPP) $(CPPFLAGS) -c $^ -o $@

# PHONY
#---------------------------------------------------------------------
.PHONY: clean
.SILENT: clean
clean:
	rm -vf *.o *.a *.so $(PROGS)

