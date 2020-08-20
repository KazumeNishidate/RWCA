#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rw.h"
#include "prototypes.h"

void move_walkers()
{
/*****************************************************************/
/* move_walkers                                                  */
/*                                                               */
/* All walkers will move according to the RWCA-1D dynamics.      */
/* sys.mat0  => MOVE => sys.mat1                                 */
/*                                                               */
/*****************************************************************/
  int i, x, y, e, w, ee, ww;
  int move_cnt=0; 
  int msd_x, msd_e, msd_w;  /* for msd calculation */

/*   actual system elements (size = 5)          |a|b|c|d|e|      */
/*   ants matrix elements No.               |0|1|2|3|4|5|6|7|8|  */

  for (i = 2; i < ctl.mat_size+2; i++){

    x   = sys.mat0[i];
    e   = sys.mat0[i+1];
    w   = sys.mat0[i-1];
    ee  = sys.mat0[i+2];
    ww  = sys.mat0[i-2];

    if(ctl.do_msd_calc!=0){
      msd_x  = sys.msmat1[i];
      msd_e  = sys.msmat1[i+1];
      msd_w  = sys.msmat1[i-1];
    }

    if( x==1 && e==0 ){                /*   rule set 1   */
      if( ee==2 )
	y = (int)(2*ran1(sys.random_seed)+1);          
      else{
	y = 0; 
	if( ctl.do_moved_ants_calc!=0 ) move_cnt++;
	if( ctl.do_msd_calc!=0 ) msd_x = 0;
      }
    }

    else if( x==2 && w==0 ){           /*   rule set 2   */
      if( ww==1 )
	y = (int)(2*ran1(sys.random_seed)+1);          
      else{
	y = 0; 
	if( ctl.do_moved_ants_calc!=0 ) move_cnt++;
	if( ctl.do_msd_calc!=0 ) msd_x = 0;
      }
    }

    else if( x==1||x==2 )             /*   rule set 3    */
      y = (int)(2*ran1(sys.random_seed)+1);          

    if( x==0 && e==2 && w==1 )        /*   rule set 4    */
      y = 0;

    else if( x==0 && e==2){           /*   rule set 5    */
      y = (int)(2*ran1(sys.random_seed)+1);          
      if( ctl.do_msd_calc!=0 ) msd_x = msd_e;
    }

    else if( x==0 && w==1){           /*   rule set 6    */
      y = (int)(2*ran1(sys.random_seed)+1);          
      if( ctl.do_msd_calc!=0 ) msd_x = msd_w;
    }

    else if( x==0 )                   /*   rule set 7    */
      y = 0;

    *(sys.mat1+i) = y;
    if( ctl.do_msd_calc!=0 ) *(sys.msmat2+i) = msd_x;

  }
  set_bc(sys.mat1);
  if( ctl.do_msd_calc!=0 ) set_bc(sys.msmat2);
  if( ctl.do_moved_ants_calc!=0 ) {
    sys.averaged_velocity[sys.time_step] += 
      ( (double)move_cnt/(double)sys.number_of_walkers )/
	(double)ctl.average_iteration_num;
  }
}

void set_bc(int *ants)
{
/*****************************************************************/
/* corner adjustment                                             */
/*                                                               */
/* for system size = 5 case (ctl.mat_size=5)                     */
/*                                                               */
/*   actual system elements (size = 5)          |a|b|c|d|e|      */
/*   ants matrix elements No.               |0|1|2|3|4|5|6|7|8|  */
/*                                                               */
/* boarder fixing procedure                                      */
/*                                                               */
/*   ants[0] <= [d] <= ants[5]   <= ants[ctl.mat_size]           */
/*   ants[1] <= [e] <= ants[5+1] <= ants[ctl.mat_size+1]         */
/*   ants[7] = ants[ctl.mat_size+2] <= [a] <= ants[2]            */
/*   ants[8] = ants[ctl.mat_size+3] <= [b] <= ants[3]            */
/*                                                               */
/*****************************************************************/

  *ants       = *(ants+(ctl.mat_size));
  *(ants+1)   = *(ants+(ctl.mat_size+1));
  *(ants+ctl.mat_size+2)     = *(ants+2);
  *(ants+ctl.mat_size+3)     = *(ants+3);
}

void mk_copy(int *original, int *copy)
{
  int i;

  for (i = 0; i < ctl.mat_size+4; i++){
      *(copy+i)  = *(original+i);
    }
}

