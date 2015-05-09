# VARIABLES
#---------------------------------------------------------------------
CPP = g++
CPPFLAGS = -std=c++11 -pedantic -Wall -Werror -g
QFLAGS =
PROGS = client_cli  client_gui

QMAKE = qmake-qt4
BUILD_FOLDER = build
SRC_FOLDER = src
GUI_FOLDER = gui
CLI_FOLDER = cli
GUI_WORK_FOLDER = gui_build

# RULES for programs
#---------------------------------------------------------------------
all: $(BUILD_FOLDER)/core.so $(PROGS)

$(BUILD_FOLDER)/core.so:
	$(MAKE) -C src
	$(CPP) -shared -fPIC -o $@ $(BUILD_FOLDER)/*.o

client_cli: $(SRC_FOLDER)/$(CLI_FOLDER)/client_cli.cpp $(BUILD_FOLDER)/core.so
	$(CPP) $(CPPFLAGS) $^ -o $@

client_gui: $(SRC_FOLDER)/$(GUI_FOLDER)/client_gui.cpp $(BUILD_FOLDER)/core.so
	cd $(GUI_FOLDER) && $(QMAKE) Labyrinth2015.pro -r -spec linux-g++ CONFIG+=debug -o ../$(GUI_WORK_FOLDER)/Makefile
	$(MAKE) CXX=$(CPP) -C $(GUI_WORK_FOLDER)
	mv ./gui_build/labyrinth2015_gui client_gui

# PHONY
#---------------------------------------------------------------------
.PHONY: clean
clean:
	rm -vf build/*.o build/*.so $(PROGS)
	rm -rv $(GUI_WORK_FOLDER)
