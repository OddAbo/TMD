/* 2020-01-14 by dianmo */

#include "tmd.h"

void PrintProps(int iprint);

void SetupJob()
{
  /*******************/
  /* Sets parameters */
  update_nebr = 1;
  n_nebr_tab_max = n_nebr * n_mol;
  step_count = 0;
  time_now = step_count * delta_t;
  mass = rmass * kBoltz;
  delta_t2 = delta_t * delta_t;
  v_eq = sqrt(kBoltz * temperature / mass);

  /***********************************************************/
  /* Allocates memory for coordinate, velocity, acceleration */
  r = (real *)malloc(n_mol * sizeof(VecR));
  v = (real *)malloc(n_mol * sizeof(VecR));
  a = (real *)malloc(n_mol * sizeof(VecR));
  a_old = (real *)malloc(n_mol * sizeof(VecR));

  /******************************************/
  /* Initializes coordinate and velocity */
  srand((int)time(0));
  switch (iread)
  {
  case 1:
    fp_rv = fopen("pos.in","r");
    ALL_MOL fscanf("%lf %lf %lf\n", &r[i_mol].x, &r[i_mol].y, &r[i_mol].z);
    break;
  case 2:
    fp_rv = fopen("md.tmp","rb");
    fread(r, n_mol * sizeof(VecR), n_mol, fp_rv);
    fread(v, n_mol * sizeof(VecR), n_mol, fp_rv);
    break;
  default:
    break;
  }
  fclose(fp_rv);
  ALL_MOL
  {
    VecAddAll(r[i_mol], r_rand_scale * ((real) rand() / RAND_MAX - 0.5));
    VecAddAll(v[i_mol], r_rand_scale * ((real) rand() / RAND_MAX - 0.5));
  }

  FixMassCenter();
  
  /**************************************************/
  /* Initializes velocity roughly by factor scaling */
  v_fact = 0.;
  v2_sum = 0.;
  ALL_MOL v2_sum += VecSqSum(v[i_mol]);
  v_fact = v_eq / sqrt(v2_sum / n_mol);
  ALL_MOL VecMulAll(v[i_mol], v_fact);

  UpdateNebr();
  Force();
  ValProps();
  PrintProps(0);
  return;
}