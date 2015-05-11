# VARIABLES
#---------------------------------------------------------------------
CPP = g++
CPPFLAGS = -std=c++11 -fPIC # -pedantic -Wall -Werror -g
PROGS = labyrint2015-cli labyrint2015

ifeq ($(shell hostname), merlin.fit.vutbr.cz)
	QMAKE = /usr/local/share/Qt-5.2.1/5.2.1/gcc_64/bin/qmake
else
	QMAKE = qmake-qt5
endif
BUILD_FOLDER = build
SRC_FOLDER = src
GUI_FOLDER = gui
CLI_FOLDER = cli
DOC_FOLDER = doc
GUI_WORK_FOLDER = gui_build
ZIP_NAME = xcoufa09_xuchyt03.zip

# RULES for programs
#---------------------------------------------------------------------
all: $(BUILD_FOLDER)/core.a $(PROGS)

$(BUILD_FOLDER)/core.a:
	mkdir -p $(BUILD_FOLDER)
	$(MAKE) -C src
	ar -rsc $@ $(BUILD_FOLDER)/*.o

labyrint2015-cli: $(SRC_FOLDER)/$(CLI_FOLDER)/client_cli.cpp $(BUILD_FOLDER)/core.a
	$(CPP) $(CPPFLAGS) $^ -o $@

labyrint2015: $(SRC_FOLDER)/$(GUI_FOLDER)/client_gui.cpp $(BUILD_FOLDER)/core.a
	cd $(GUI_FOLDER) && $(QMAKE) Labyrinth2015.pro -r -spec linux-g++ CONFIG+=debug -o ../$(GUI_WORK_FOLDER)/Makefile
	$(MAKE) CXX=$(CPP) -C $(GUI_WORK_FOLDER)

# PHONY
#---------------------------------------------------------------------
.PHONY: clean pack docs doxygen zip
clean:
	-rm -vf $(PROGS) $(ZIP_NAME)
	-rm -rfv $(GUI_WORK_FOLDER) $(BUILD_FOLDER) $(DOC_FOLDER)
doxygen: docs
zip: pack

docs:
	doxygen
pack:
	zip -r $(ZIP_NAME) $(SRC_FOLDER) $(GUI_FOLDER) examples Makefile Doxyfile README.md
