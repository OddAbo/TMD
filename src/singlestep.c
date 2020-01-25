/* 2020-01-14 by dianmo */

#include "tmd.h"

void SingleStep()
{
  ++step_count;
  time_now = step_count * delta_t;
  VelocityVerlet(1);
  Force();
  FixTemperature();
  VelocityVerlet(2);
  EvalProps();
  if (step_count % step_print_log == 0) PrintProps(1);
  if (step_count % step_print_out == 0) PrintProps(2);
  return;
}