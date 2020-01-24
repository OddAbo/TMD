/* 2020-01-14 by dianmo */
/* Toy Molecular Dynamics program */

#include "tmd.h"

void GetNameList(int argc, char **argv);
void SetupJob();
void SingleStep();
void PrintProps(int iprint);

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
  PrintProp();

  return 0;
}