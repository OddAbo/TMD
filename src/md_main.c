/* 2020-01-14 by dianmo */
/* Toy Molecular Dynamics program */

#include "tmd.h"

int main(int argc, char **argv)
{
  GetNameList(argc, argv);
  SetupJob();

  int icycle = 1;
  while (icycle) 
  {
    SingleStep();
    if (step_count >= step_max) icycle = 0;
  }
  PrintProps(3);

  return 0;
}