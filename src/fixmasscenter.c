#include "tmd.h"

void FixMassCenter()
{
  VecSetAll(v_sum, 0);
  ALL_MOL VecsAdd(v_sum, v_sum, v[i_mol]);
  VecModAll(v_sum, n_mol);
  ALL_MOL VecsSub(v[i_mol], v[i_mol], v_sum);

  return;
}