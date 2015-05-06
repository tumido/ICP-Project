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
	$(CPP) -shared -fPIC -o core.so build/*.o

client_cli: client_cli.cpp core.so
	$(CPP) $(CPPFLAGS) $^ -o ../$@

client_gui: client_gui.cpp
	$(CPP) $(CPPFLAGS) $< -o ../$@


# PHONY
#---------------------------------------------------------------------
.PHONY: clean
.SILENT: clean
clean:
	rm -vf build/*.o *.so $(PROGS)
