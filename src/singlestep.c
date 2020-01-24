/* 2020-01-14 by dianmo */

#include "tmd.h"

void VelocityVerlet(int part);
void ApplyPbc();
void ComputeForce();
void EvalProps();
void PrintProps();

void SingleStep()
{
  ++step_count;
  time_now = step_count * delta_t;
  VelocityVerlet(1);
  if (ipbc) ApplyPbc();
  ComputeForce();
  VelocityVerlet(2);
  EvalProps();
  PrintProps();
  return;
}