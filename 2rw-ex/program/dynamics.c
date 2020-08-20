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
/* All walkers will move according to the RWCA-2D dynamics.      */
/* sys.mat0  => MOVE => sys.mat1                                 */
/*                                                               */
/*****************************************************************/
  int i, j, x, y;
  int n, e, s, w;
  int ne, se, sw, nw;
  int nn, ee, ss, ww;
  int move_cnt = 0;
  int msd_x1, msd_y1;  /* for msd calculation */
  int msd_n1, msd_e1, msd_s1, msd_w1;


  for (i = 2; i < ctl.mat_size+2; i++){
    for (j = 2; j < ctl.mat_size+2; j++){

      x  = sys.mat0[ctl.shift*i+j];

      n  = sys.mat0[ctl.shift*(i-1)+j];
      e  = sys.mat0[ctl.shift*i+j+1];
      s  = sys.mat0[ctl.shift*(i+1)+j];
      w  = sys.mat0[ctl.shift*i+j-1];

      ne  = sys.mat0[ctl.shift*(i-1)+j+1];
      se  = sys.mat0[ctl.shift*(i+1)+j+1];
      sw  = sys.mat0[ctl.shift*(i+1)+j-1];
      nw  = sys.mat0[ctl.shift*(i-1)+j-1];

      nn  = sys.mat0[ctl.shift*(i-2)+j];
      ee  = sys.mat0[ctl.shift*i+j+2];
      ss  = sys.mat0[ctl.shift*(i+2)+j];
      ww  = sys.mat0[ctl.shift*i+j-2];

      if( ctl.do_msd_calc!=0 ){
	msd_x1  = sys.msmat1[ctl.shift*i+j];
	msd_y1  = msd_x1;
	msd_n1  = sys.msmat1[ctl.shift*(i-1)+j];
	msd_e1  = sys.msmat1[ctl.shift*i+j+1];
	msd_s1  = sys.msmat1[ctl.shift*(i+1)+j];
	msd_w1  = sys.msmat1[ctl.shift*i+j-1];
      }

      if( x==1 && n==0 ){                     /*   rule set 1   */
        if( ne==4 )
          y = (int)(4*ran1(sys.random_seed)+1);
        else if( nw==2 )
          y = (int)(4*ran1(sys.random_seed)+1);
        else if( nn==3 )
          y = (int)(4*ran1(sys.random_seed)+1);
        else{
          y = 0;
	  if( ctl.do_moved_ants_calc!=0 ) move_cnt++;
          if( ctl.do_msd_calc!=0 ) msd_y1 = 0;
        }
      }

      else if( x==2 && e==0 ){                /*   rule set 2   */
        if( ne==3 )
          y = (int)(4*ran1(sys.random_seed)+1);
        else if( se==1 )
          y = (int)(4*ran1(sys.random_seed)+1);
        else if( ee==4 )
          y = (int)(4*ran1(sys.random_seed)+1);
        else{
          y = 0;
          if( ctl.do_moved_ants_calc!=0 ) move_cnt++;
          if( ctl.do_msd_calc!=0 ) msd_y1 = 0;
        }
      }

      else if( x==3 && s==0 ){                /*   rule set 3   */
        if( se==4 )
          y = (int)(4*ran1(sys.random_seed)+1);
        else if( sw==2 )
          y = (int)(4*ran1(sys.random_seed)+1);
        else if( ss==1 )
          y = (int)(4*ran1(sys.random_seed)+1);
        else{
          y = 0;
          if( ctl.do_moved_ants_calc!=0 ) move_cnt++;
          if( ctl.do_msd_calc!=0 ) msd_y1 = 0;
        }
      }

      else if( x==4 && w==0 ){                /*   rule set 4   */
        if( sw==1 )
          y = (int)(4*ran1(sys.random_seed)+1);
        else if( nw==3 )
          y = (int)(4*ran1(sys.random_seed)+1);
        else if( ww==2 )
          y = (int)(4*ran1(sys.random_seed)+1);
        else{
          y = 0;
          if( ctl.do_moved_ants_calc!=0 ) move_cnt++;
          if( ctl.do_msd_calc!=0 ) msd_y1 = 0;
        }
      }

      else if( x==1||x==2||x==3||x==4)         /*   rule set 5   */
          y = (int)(4*ran1(sys.random_seed)+1);

      if( x==0 && n==3 && e==4 )               /*   rule set 6   */
          y = 0;
      else if( x==0 && n==3 && s==1 )
          y = 0;
      else if( x==0 && n==3 && w==2 )
          y = 0;
      else if( x==0 && e==4 && s==1 )
          y = 0;
      else if( x==0 && e==4 && w==2 )
          y = 0;
      else if( x==0 && s==1 && w==2 )
          y = 0;

      else if( x==0 && n==3){                  /*   rule set 7   */
          y = (int)(4*ran1(sys.random_seed)+1);
          if( ctl.do_msd_calc!=0 ) msd_y1 = msd_n1;
        }
      else if( x==0 && e==4){
          y = (int)(4*ran1(sys.random_seed)+1);
          if( ctl.do_msd_calc!=0 ) msd_y1 = msd_e1;
        }
      else if( x==0 && s==1){
          y = (int)(4*ran1(sys.random_seed)+1);
          if( ctl.do_msd_calc!=0 ) msd_y1 = msd_s1;
        }
      else if( x==0 && w==2){
          y = (int)(4*ran1(sys.random_seed)+1);
          if( ctl.do_msd_calc!=0 ) msd_y1 = msd_w1;
        }

      else if( x==0 )                          /*   rule set 8   */
          y = 0;

      *(sys.mat1+ctl.shift*i+j) = y;
      if( ctl.do_msd_calc!=0 ) *(sys.msmat2+ctl.shift*i+j) = msd_y1;

    }
  }
  set_bc(sys.mat1);
  if( ctl.do_msd_calc!=0 ) set_bc(sys.msmat2);
  if( ctl.do_moved_ants_calc!=0 ) {
    sys.averaged_velocity[sys.time_step] +=
      ( (double)move_cnt/(double)sys.number_of_walkers )/
	(double)ctl.average_iteration_num;
  }

/* fix */
/*
    show_matrix(sys.mat0);
    show_matrix(sys.mat1);
    printf("mvcnt = %d averaged_velocity = %f\n",
	   move_cnt, sys.averaged_velocity[sys.time_step]); 
    getchar();
*/
}

void set_bc(int *ants)
{
  int i;

/* corner adjustment 1 */
  *ants     = *(ants+( ctl.shift*(ctl.mat_size+1) - 4));
  *(ants+1) = *(ants+( ctl.shift*(ctl.mat_size+1) - 3));
  *(ants+ctl.shift) = *(ants+( ctl.shift*(ctl.mat_size+2) - 4));
  *(ants+(ctl.mat_size+5)) = *(ants+( ctl.shift*(ctl.mat_size+2) - 3));

/* corner adjustment 2 */
  *(ants+(ctl.mat_size+2))   = *(ants+(ctl.shift*ctl.mat_size + 2));
  *(ants+(ctl.mat_size+3))   = *(ants+(ctl.shift*ctl.mat_size + 3));
  *(ants+2*(ctl.mat_size+3)) = *(ants+(ctl.shift*(ctl.mat_size+1)+2));
  *(ants+2*(ctl.mat_size+3)+1) = *(ants+(ctl.shift*(ctl.mat_size+1)+3));

/* corner adjustment 3 */
  *(ants+(ctl.mat_size+3)*(ctl.mat_size+3)-1) = *(ants+3*ctl.shift-4);
  *(ants+(ctl.mat_size+3)*(ctl.mat_size+3)) = *(ants+3*ctl.shift-3);
  *(ants+(ctl.mat_size+3)*ctl.shift) = *(ants+4*ctl.shift-4);
  *(ants+(ctl.mat_size+3)*ctl.shift+1) = *(ants+4*ctl.shift-3);

/* corner adjustment 4 */
  *(ants+ctl.shift*(ctl.mat_size+3)-2) = *(ants+2*ctl.shift+2);
  *(ants+ctl.shift*(ctl.mat_size+3)-1) = *(ants+2*ctl.shift+3);
  *(ants+ctl.shift*ctl.shift-2) = *(ants+3*ctl.shift+2);
  *(ants+ctl.shift*ctl.shift-1) = *(ants+3*ctl.shift+3);

/* border adjustment   */

  for (i = 2; i < ctl.mat_size+2; i++){
      *(ants+i) = *(ants+ctl.shift*ctl.mat_size+i);
      *(ants+ctl.mat_size+4+i) = *(ants+ctl.shift*(ctl.mat_size+1)+i); 
      *(ants+ctl.shift*(ctl.mat_size+2)+i)=*(ants+2*ctl.shift+i);
      *(ants+ctl.shift*(ctl.mat_size+3)+i) = *(ants+3*ctl.shift+i); 

      *(ants+i*ctl.shift)   = *(ants+(i+1)*ctl.shift-4);
      *(ants+i*ctl.shift+1) = *(ants+(i+1)*ctl.shift-3);

      *(ants+(i+1)*ctl.shift-2)   = *(ants+i*ctl.shift+2);
      *(ants+(i+1)*ctl.shift-1)   = *(ants+i*ctl.shift+3);
    }

}

void mk_copy(int *original, int *copy)
{
  int i, j;

  for(i=0; i<ctl.mat_size+4; i++){
    for(j=0; j<ctl.mat_size+4; j++){
      *(copy+ctl.shift*i+j)  = *(original+ctl.shift*i+j);
    }
  }
}

