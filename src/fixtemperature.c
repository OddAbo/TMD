#include "tmd.h"

void FixTemperatrue()
{
  switch (ifixt)
  {
  case 0: /* Do nothing */
    break;
  case 1: /* Factor Scaling */
    if (step_count % step_adjust_temp == 0)
    {
      v_fact = 0.;
      v2_sum = 0.;
      ALL_MOL v2_sum += VecSqSum(v[i_mol]);
      v_fact = v_eq / sqrt(v2_sum / n_mol);
      ALL_MOL VecMulAll(v[i_mol], v_fact);
    }
  default:
    printf("Error! Wrong parameter: 'ifixt'.\n");
    exit(1);
  }
}