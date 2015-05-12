Project: ICP Labyrinth 2015
===========================
Authors: Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)

Implementation details
----------------------
Our project has been implemented using the OOP approach.
Game logic source code is located in `./src/core/` directory.
Class `GameManager` provides game interface for GUI and CLI modules.
GUI and CLI classes are in `./src/gui/` and `./src/cli/` directories.


Notes
-----
- Save does not store previous moves between the sessions.
  Player's are only able to undo action, that were made during the current session.

Make options
------------
make labyrinth2015
    builds GUI application

make labyrinth2015-cli
    builds CLI application

make doxygen
    builds documentation in `./doc/` folder

make pack
    creates archive containing application's source code

make clean
    clears project directory
