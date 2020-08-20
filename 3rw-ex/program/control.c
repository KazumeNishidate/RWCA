#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rw.h"
#include "prototypes.h"

#define ON  (1)
#define OFF (0)

void get_control_param(void){ 
  long time_dumy;

  /* set up the system control parameters */
  ctl.max_time_step = 5000;   /* max time step */
  ctl.mat_size = 20;         /* system size = n X n X n squared lattice */
  ctl.concentration = 0.01;  /* initial concentration probability */

  /* set up the calculation control parameters */
  /* set the following indicators as 1="ON" or 0="OFF" */
  ctl.do_msd_calc = 1;        /* mean squared displacement calculation  */
  ctl.do_moved_ants_calc = 0; /* calculation of number of moved walkers */
  ctl.average_iteration_num = 1; /* number of runs for averaged calculation */
  /* note: ctl.average_iteration_num > 0 */

  /* other calculation control parameter */

  /* "ctl.mat_size2" will be used at "msd_calc()" to consider the */
  /* effect of cyclic boundaly condition in MSD calculation.      */
  ctl.mat_size2 = ctl.mat_size/2; 
  ctl.shift = ctl.mat_size+4;
  ctl.shift2 = ctl.shift*ctl.shift;

  /* set a "seed" for random number generator */
  sys.random_seed = (long *)calloc(1, sizeof(long)); 
  *sys.random_seed=-time(&time_dumy); /* set seed for random numbers */

  sys.average_step = 0;  /* average iteration counter */

}
