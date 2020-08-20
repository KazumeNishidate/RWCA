#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rw.h"
#include "prototypes.h"

/* RWCA-2d uder cyclic boundary condition */

int main(void){

  open_files();
  get_control_param();
  init_mem();

  /*================= average calculation ======================*/
  for(sys.average_step = 0; 
      sys.average_step <ctl.average_iteration_num;
      sys.average_step++){

/* fix */
/*    printf("sys.average_step = %d\n",sys.average_step); */

    set_init_conf();
    mk_copy(sys.mat0, sys.mat1);
    
    /* initilize the MSD calculation */
    /* sys.msmat0 = initial matrix with numbered walkers */
    /* sys.msmat1 = matrix with numbered walkers at t-1  */
    /* sys.msmat1 = matrix with numbered walkers at t    */
    msd_ini();                       
    mk_copy(sys.msmat0, sys.msmat1); /* preparation for MSD */
    mk_copy(sys.msmat0, sys.msmat2);

    /*----------- RWCA moving step -----------*/
    for(sys.time_step=0;sys.time_step<ctl.max_time_step;sys.time_step++)
      {
/*-------------- X interface -------------------*/
#ifdef XD
	xd();
#endif

	/* printf("run[%d] time = %d\n",sys.average_step,sys.time_step); */
	/* printf("num of ants = %d\n",sys.number_of_walkers); */
	/* display current matrix configuration */
	/* show_matrix(sys.mat0); */

	/* display the numbered walkers */
	/*	show_matrix(sys.msmat1); */

	/* print current matrix configuration (../files/out) */
	/*	print_matrix(sys.mat0); */
	/* print the numbered walkers (../files/out) */
	/*	print_matrix(sys.msmat1); */

	move_walkers();       /* sys.mat0 => RWCA  => sys.mat1 */
	mk_copy(sys.mat1, sys.mat0);  /* sys.mat1  =  sys.mat0 */
	if(ctl.do_msd_calc != 0) {
	  calc_msd();
	  mk_copy(sys.msmat2, sys.msmat1);
	}

      }
    /*-------- end of RWCA moving step -------*/
  } 
  /*============== end of average calculation ===================*/
  if(ctl.do_msd_calc != 0) print_averaged_msd();
  if(ctl.do_moved_ants_calc != 0) print_averaged_velocity();

  return 0;
}

