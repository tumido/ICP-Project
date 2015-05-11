# VARIABLES
#---------------------------------------------------------------------
CPP = g++
CPPFLAGS = -std=c++11 -fPIC # -pedantic -Wall -Werror -g
PROGS = client_cli  client_gui

ifeq ($(shel hostname), merlin.fit.vutbr.cz)
	QMAKE = /usr/local/share/Qt-5.2.1/5.2.1/gcc_64/bin/qmake
else
	QMAKE = qmake-qt5
endif
BUILD_FOLDER = build
SRC_FOLDER = src
GUI_FOLDER = gui
CLI_FOLDER = cli
GUI_WORK_FOLDER = gui_build

# RULES for programs
#---------------------------------------------------------------------
all: $(BUILD_FOLDER)/core.a $(PROGS)

$(BUILD_FOLDER)/core.a:
	mkdir $(BUILD_FOLDER)
	$(MAKE) -C src
	ar -rsc $@ $(BUILD_FOLDER)/*.o

client_cli: $(SRC_FOLDER)/$(CLI_FOLDER)/client_cli.cpp $(BUILD_FOLDER)/core.a
	$(CPP) $(CPPFLAGS) $^ -o $@

client_gui: $(SRC_FOLDER)/$(GUI_FOLDER)/client_gui.cpp $(BUILD_FOLDER)/core.a
	cd $(GUI_FOLDER) && $(QMAKE) Labyrinth2015.pro -r -spec linux-g++ CONFIG+=debug -o ../$(GUI_WORK_FOLDER)/Makefile
	$(MAKE) CXX=$(CPP) -C $(GUI_WORK_FOLDER)
	mv ./gui_build/labyrinth2015_gui client_gui

# PHONY
#---------------------------------------------------------------------
.PHONY: clean pack docs doxygen zip
clean:
	rm -vf build/*.o build/*.a $(PROGS) | true
	rm -rv $(GUI_WORK_FOLDER) $(BUILD_FOLDER) | true
	rm -rf docs/* | true
doxygen: docs
zip: pack

docs:
	doxygen
pack:
	zip -r xcoufa09_xuchyt03.zip include src gui Makefile README.md
