#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rw.h"
#include "prototypes.h"

#define TRUE  (1)
#define FALSE (0)

void get_control_param(void){ 
  long time_dumy;

  /* set up the system control parameters */
  ctl.max_time_step = 10000;   /* max time step */
  ctl.mat_size = 450;         /* system size   */
  ctl.concentration = 0.1;   /* initial concentration probability */

  /* set up the calculation control parameters */
  /* set the following indicators as 1="TRUE" or 0="FALSE" */
  ctl.do_msd_calc = 1;        /* mean squared displacement calculation  */
  ctl.do_moved_ants_calc = 1; /* calculation of number of moved walkers */
  ctl.average_iteration_num = 1; /* number of runs for averaged calculation */

  /* other calculation control parameter */

  /* "ctl.mat_size2" will be used at "msd_calc()" to consider the */
  /* effect of cyclic boundaly condition in MSD calculation.      */
  ctl.mat_size2 = ctl.mat_size/2; 

  /* set a "seed" for random number generator */
  sys.random_seed = (long *)calloc(1, sizeof(long)); 
  *sys.random_seed=-time(&time_dumy); /* set seed for random numbers */

}
