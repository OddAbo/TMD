#include "tmd.h"

void VelocityVerlet(int part)
{
  switch (part)
  {
  case 1:
    ALL_MOL
    {
      r[i_mol].x += v[i_mol].x + 0.5 * a[i_mol].x * delta_t2;
      r[i_mol].y += v[i_mol].y + 0.5 * a[i_mol].y * delta_t2;
      r[i_mol].z += v[i_mol].z + 0.5 * a[i_mol].z * delta_t2;
    } 
    break;
  case 2:
    ALL_MOL
    {
      v[i_mol].x += 0.5 * (a[i_mol].x + a_old[i_mol].x) *delta_t;
      v[i_mol].y += 0.5 * (a[i_mol].y + a_old[i_mol].y) *delta_t;
      v[i_mol].z += 0.5 * (a[i_mol].z + a_old[i_mol].z) *delta_t;
    }
    break;
  default:
    break;
  }
}