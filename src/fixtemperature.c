#include "tmd.h"

void FixTemperature()
{
  if (step_count % step_adjust_temp) return;

  switch (ifixt)
  {
  case 0: /* Do nothing */
    break;
  case 1: /* Factor scaling */
    v_fact = 0.;
    v2_sum = 0.;
    ALL_MOL v2_sum += VecSqSum(v[i_mol]);
    v_fact = v_eq / sqrt(v2_sum / n_mol);
    ALL_MOL VecMulAll(v[i_mol], v_fact);
    break;
  case 2: /* Nose-Hoover thermal chain */
    
    break;
  default:
    printf("Error! Wrong parameter: 'ifixt'.\n");
    exit(1);
  }
}