#include "tmd.h"

void evalprops()
{
  static real v2;
  sum_dr = 0;
  ALL_MOL
  {
    v2 = v[i_mol].x * v[i_mol].x \
       + v[i_mol].y * v[i_mol].y \
       + v[i_mol].z * v[i_mol].z;
    v2_max = (v2_max > v2) ? v2_max : v2;
  }
  sum_dr += sqrt(v2_max) * delta_t;
  if (sum_dr > 0.5 * r_nebr_shell) update_nebr = 1;

  return;
}