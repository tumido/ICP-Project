#include "../../include/io.h"
#include "../../include/LabyrinthCLI.h"

#define RETRY_LIMIT 100

int main()
{
  LabyrinthCLI cli;
  cli.exec();
  return EXIT_SUCCESS;
}
