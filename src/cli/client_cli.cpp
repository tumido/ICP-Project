/**
 * @file client_cli.cpp
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 * @brief Main function for CLI version of our program
 */
#include "../include/io.h"
#include "../include/LabyrinthCLI.h"

#define RETRY_LIMIT 100

/// @brief Main which calls exec() method of LabyrinthCLI instance
int main()
{
  LabyrinthCLI cli;
  cli.exec();
  return EXIT_SUCCESS;
}
