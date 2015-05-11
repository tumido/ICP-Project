/**
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 */
#include "../../include/io.h"
#include "../../include/LabyrinthCLI.h"

#define RETRY_LIMIT 100

int main()
{
  LabyrinthCLI cli;
  cli.exec();
  return EXIT_SUCCESS;
}
