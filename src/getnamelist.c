#include "tmd.h"

typedef enum {
  N_I, N_R
} VType;

typedef struct {
  char *v_name;
  void *v_ptr;
  VType v_type;
  int v_len, v_stat;
} NameList;

#define NameI(x)  {#x, &x, N_I, sizeof(x) / sizeof(int)}
#define NameR(x)  {#x, &x, N_R, sizeof(x) / sizeof(real)}

#define NPT_I     ((int *)(name_list[i].v_ptr) + j)
#define NPT_R     ((real *)(name_list[i].v_ptr) + j)

#define ALL_NAMELIST  for(i = 0; i < n_namelist; ++i)

void GetNameList(int argc, char **argv)
{  
  int i, j, n_namelist, ok;
  char buff[80], *token;
  FILE *fp;
  NameList name_list[] =
  {
    NameI(n_mol),
    NameR(rmass),
    NameR(r_cut),
    NameI(n_nebr),
    NameR(r_nebr_shell),
    NameR(iread),
    NameI(step_max),
    NameR(delta_t),
    NameI(ifixt),
    NameR(des_temp),
    NameI(step_adjust_temp),
    NameI(ifixp),
    NameR(des_press),
    NameI(step_adjust_press),
    NameI(ifixv),
    NameR(des_volume),
    NameI(step_adjust_volume),
    NameI(ipbc),
    NameR(pbc),
    NameI(step_print_log),
    NameI(step_print_out),
  };

  strcpy(buff, argv[0]);
  strcat(buff, ".in");
  if ((fp = fopen(buff, "r")) == 0)
  {
    printf("Error! Lacking file: %s.\n",buff);
    exit(1);
  }

  ok = 1;
  n_namelist = sizeof(name_list) / sizeof(NameList);
  ALL_NAMELIST name_list[i].v_stat = 0;

  while (1)
  {
    fgets(buff, 80, fp);
    if (feof(fp)) break;
    if (buff[0] == '/' || buff[0] == '\n') continue;
    token = strtok(buff,",= \t\n");
    if(! token) break;
    ALL_NAMELIST
    {
      if (strcmp(token, name_list[i].v_name) == 0)
      {
        if (name_list[i].v_stat == 0)
        {
          name_list[i].v_stat = 1;
          for (j = 0; j < name_list[i].v_len; ++j)
          {
            token = strtok(NULL, ",= \t\n");
            if (token)
            {
              switch (name_list[i].v_type)
              {
              case N_I:
                *NPT_I = atol(token);
                break;
              case N_R:
                *NPT_R = atof(token);
                break;          
              default:
                break;
              }
            } else {
              name_list[i].v_stat = 2;
              ok = 0;
            }
          }
          token = strtok(NULL, ",= \t\n");
          if (token)
          {
            name_list[i].v_stat = 3;
            ok = 0;
          }  
          break;
        } else {
          name_list[i].v_stat = 4;
          ok = 0;
        }
      }
    }
  }
  fclose(fp);

  if (ok == 0)
  {
    ALL_NAMELIST
    {
      switch (name_list[i].v_stat)
      {
      case 1: default:
        break;
      case 2:
        printf("Error! Wrong parameter: '%s'.\n",name_list[i].v_name);
        break;
      case 3:
        printf("Error! Too many input: '%s'.\n",name_list[i].v_name);
        break;
      case 4:
        printf("Error! Lacks parameter: '%s'.\n",name_list[i].v_name);
        break;
      }
    }
    exit(1);
  }

  return;
}