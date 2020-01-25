#include "tmd.h"

void VelocityVerley(int part)
{
  switch (part)
  {
  case 1:
    ALL_MOL r[i_mol].x += v[i_mol].x + 0.5 * a[i_mol].x * delta_t2;
    break;
  case 2:
    memcpy(a_old, a, 3 * n_mol * sizeof(real));
  default:
    break;
  }
}