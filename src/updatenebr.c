#include "tmd.h"

void UpdateNebr()
{
  static real r2_nebr;

  r2_nebr = (r_cut + r_nebr_shell) * (r_cut + r_nebr_shell);
}