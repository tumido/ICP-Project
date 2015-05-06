# VARIABLES
#---------------------------------------------------------------------
CPP = g++
CPPFLAGS = -std=c++11 -pedantic -Wall -Werror
PROGS = client_cli # client_gui


# RULES for programs
#---------------------------------------------------------------------
all: objects $(PROGS)

objects:
	$(MAKE) -C src
	$(CPP) -shared -fPIC -o build/core.so build/*.o

client_cli: src/client_cli.cpp build/core.so
	$(CPP) $(CPPFLAGS) $^ -o $@

client_gui: src/client_gui.cpp build/core.so
	$(CPP) $(CPPFLAGS) $< -o $@


# PHONY
#---------------------------------------------------------------------
.PHONY: clean
.SILENT: clean
clean:
	rm -vf build/*.o *.so $(PROGS)
