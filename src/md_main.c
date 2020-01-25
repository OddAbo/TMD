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
    ++step_count;
    time_now = step_count * delta_t;
    VelocityVerlet(1);
    if (ipbc) ApplyPbc();
    UpdateForce();
    VelocityVerlet(2);
    if (step_count % step_adjust_volume == 0) FixVolume();
    if (step_count % step_adjust_press == 0) FixPressure();
    if (step_count % step_adjust_temp == 0) FixTemperature();
    EvalProps();
    if (step_count % step_print_log == 0) PrintProps(1);
    if (step_count % step_print_out == 0) PrintProps(2);
    if (step_count >= step_max) icycle = 0;
  }
  PrintProps(3);

  return 0;
}