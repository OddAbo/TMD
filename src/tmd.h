#ifndef _TMD_H
#define _TMD_H

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef double real;

const real kBoltz = 1.0;
const real kMass = 1.0;

/* Vectors type of real and int */
typedef struct {
  real x, y, z;
} VecR;

typedef struct {
  int x, y, z;
} VecI;

/* System properties */
typedef struct 
{
  real val, sum, sum2;
} Prop;

VecR pbc, v_sum, dr, *r, *v, *a, *a_old;
Prop kin_ene, tot_ene, pressure;
int n_mol, i_mol, ifixt, ifixp, ifixv, ipbc, iread;
int step_max, step_count, step_print_log, step_print_out;
int step_adjust_temp, step_adjust_press, step_adjust_volume;
int update_nebr, n_nebr, n_nebr_tab_max, *nebr_tab;
real v_fact, v2_sum, v2_max, v_eq, time_now, temperature, volume;
real r_rand_scale, v_rand_scale, r_nebr_shell, sum_dr, delta_t, delta_t2;
real mass, rmass, r_cut, des_temp, des_press, des_volume;
FILE *fp_rv, *fp_log, *fp_out, *fp_tmp, *fp_res;

/* Some operation for convinience */
#define VecSet(v, a, b, c) \
  (v).x = a,               \
  (v).y = b,               \
  (v).z = c

#define VecAdd(v, a, b, c) \
  (v).x += a,              \
  (v).y += b,              \
  (v).z += c

#define VecSub(v, a, b, c) \
  (v).x -= a,              \
  (v).y -= b,              \
  (v).z -= c

#define VecMul(v, a, b, c) \
  (v).x *= a,              \
  (v).y *= b,              \
  (v).z *= c

#define VecMod(v, a, b, c) \
  (v).x /= a,              \
  (v).y /= b,              \
  (v).z /= c

#define VecSetAll(v, a)  VecSet(v, a, a, a)
#define VecAddAll(v, b)  VecAdd(v, b, b, b)
#define VecMulAll(v, c)  VecMul(v, c, c, c)
#define VecModAll(v, d)  VecMod(v, d, d, d)

#define VecsAdd(v1, v2, v3) \
  (v1).x = (v2).x + (v3).x, \
  (v1).y = (v2).y + (v3).y, \
  (v1).z = (v2).z + (v3).z

#define VecsSub(v1, v2, v3) \
  (v1).x = (v2).x - (v3).x, \
  (v1).y = (v2).y - (v3).y, \
  (v1).z = (v2).z - (v3).z

#define VecSqSum(v)  ((v).x * (v).x + (v).y * (v).y + (v).z * (v).z)

#define ALL_MOL  for (i_mol = 0; i_mol < n_mol; ++i_mol)

void GetNameList(int argc, char **argv);
void SetupJob();
void UpdateNebr();
void Force();
void PrintProps(int iprint);
void VelocityVerlet(int part);
void EvalProps();
void FixTemperature();
void FixPressure();
void FixVolume();

#endif