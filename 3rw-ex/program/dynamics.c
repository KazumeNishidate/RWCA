#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rw.h"
#include "prototypes.h"

#define RND6 (int)(6*ran1(sys.random_seed)+1)

static int num1 ,num2;
#define RND125 ( (num1) = (int)(3*ran1(sys.random_seed)+1), (num1)==(3) ? (5) : (num1))
#define RND346 ( (num2) = (int)(3*ran1(sys.random_seed)+3), (num2)==(5) ? (6) : (num2))

#define lookup(mat,x,y,z) *(mat+((ctl.shift2*(x))+(ctl.shift*(y))+(z)))

void move_walkers()
{
/*****************************************************************/
/* move_walkers                                                  */
/*                                                               */
/* All walkers will move according to the RWCA-3D dynamics.      */
/* sys.mat0  => MOVE => sys.mat1                                 */
/*                                                               */
/*****************************************************************/
  int i, j, k, x, y;
  int n, e, s, w;
  int ne, se, sw, nw;
  int nn, ee, ss, ww;

  int u, d, uu, dd;
  int un, dn, ue, de;
  int us, ds, uw, dw;

  int move_cnt = 0;
  int msd_x1, msd_y1;  /* for msd calculation */
  int msd_n1, msd_e1, msd_s1, msd_w1, msd_u1, msd_d1;

  for (i = 2; i < ctl.mat_size+2; i++){
    for (j = 2; j < ctl.mat_size+2; j++){
      for (k = 2; k < ctl.mat_size+2; k++){

	x  = lookup(sys.mat0,   i,   j,   k);
	n  = lookup(sys.mat0,   i, j-1,   k);
	e  = lookup(sys.mat0,   i,   j, k+1);
	s  = lookup(sys.mat0,   i, j+1,   k);
	w  = lookup(sys.mat0,   i,   j, k-1);

	ne = lookup(sys.mat0,   i, j-1, k+1);
	se = lookup(sys.mat0,   i, j+1, k+1);
	sw = lookup(sys.mat0,   i, j+1, k-1);
	nw = lookup(sys.mat0,   i, j-1, k-1);

	nn = lookup(sys.mat0,   i, j-2,   k);
	ee = lookup(sys.mat0,   i,   j, k+2);
	ss = lookup(sys.mat0,   i, j+2,   k);
	ww = lookup(sys.mat0,   i,   j, k-2);

	u  = lookup(sys.mat0, i-1,   j,   k);
	d  = lookup(sys.mat0, i+1,   j,   k);
	uu = lookup(sys.mat0, i-2,   j,   k);
	dd = lookup(sys.mat0, i+2,   j,   k);

	un = lookup(sys.mat0, i-1, j-1,   k);
	dn = lookup(sys.mat0, i+1, j-1,   k);
	ue = lookup(sys.mat0, i-1,   j, k+1);
	de = lookup(sys.mat0, i+1,   j, k+1);

	us = lookup(sys.mat0, i-1, j+1,   k);
	ds = lookup(sys.mat0, i+1, j+1,   k);
	uw = lookup(sys.mat0, i-1,   j, k-1);
	dw = lookup(sys.mat0, i+1,   j, k-1);

if(x==0&&n==0&&e==0&&s==0&&w==0&&ne==0&&se==0&&sw==0&&nw==0&&nn==0&&ee==0&&ss==0&&ww==0&&u==0&&d==0&&uu==0&&dd==0&&un==0&&dn==0&&ue==0&&de==0&&us==0&&ds==0&&uw==0&&dw==0) continue;

	if( ctl.do_msd_calc!=0 ){
	  msd_x1  = lookup(sys.msmat1,    i,   j,   k);
	  msd_y1  = msd_x1;
	  msd_n1  = lookup(sys.msmat1,    i, j-1,   k);
	  msd_e1  = lookup(sys.msmat1,    i,   j, k+1);
	  msd_s1  = lookup(sys.msmat1,    i, j+1,   k);
	  msd_w1  = lookup(sys.msmat1,    i,   j, k-1);
	  msd_u1  = lookup(sys.msmat1, i-1,    j,   k);
	  msd_d1  = lookup(sys.msmat1, i+1,    j,   k);
	}
/*********************************************/

	if( x==1 && n==0 ){                     /*   rule set 1   */
	  if( ne==4 )
	    y = RND125;
	  else if( nw==2 )
	    y = RND125;
	  else if( nn==3 )
	    y = RND125;
	  else if( un==6 )
	    y = RND125;
	  else if( dn==5 )
	    y = RND125;
	  else{
	    y = 0;
	    if( ctl.do_moved_ants_calc!=0 ) move_cnt++;
	    if( ctl.do_msd_calc!=0 ) msd_y1 = 0;
	  }
	}

	else if( x==2 && e==0 ){                /*   rule set 2   */
	  if( ne==3 )
	    y = RND125;
	  else if( se==1 )
	    y = RND125;
	  else if( ee==4 )
	    y = RND125;
	  else if( ue==6 )
	    y = RND125;
	  else if( de==5 )
	    y = RND125;
	  else{
	    y = 0;
	    if( ctl.do_moved_ants_calc!=0 ) move_cnt++;
	    if( ctl.do_msd_calc!=0 ) msd_y1 = 0;
	  }
	}

	else if( x==3 && s==0 ){                /*   rule set 3   */
	  if( se==4 )
	    y = RND346;
	  else if( sw==2 )
	    y = RND346;
	  else if( ss==1 )
	    y = RND346;
	  else if( us==6 )
	    y = RND346;
	  else if( ds==5 )
	    y = RND346;
	  else{
	    y = 0;
	    if( ctl.do_moved_ants_calc!=0 ) move_cnt++;
	    if( ctl.do_msd_calc!=0 ) msd_y1 = 0;
	  }
	}

	else if( x==4 && w==0 ){                /*   rule set 4   */
	  if( sw==1 )
	    y = RND346;
	  else if( nw==3 )
	    y = RND346;
	  else if( ww==2 )
	    y = RND346;
	  else if( uw==6 )
	    y = RND346;
	  else if( dw==5 )
	    y = RND346;
	  else{
	    y = 0;
	    if( ctl.do_moved_ants_calc!=0 ) move_cnt++;
	    if( ctl.do_msd_calc!=0 ) msd_y1 = 0;
	  }
	}

	else if( x==5 && u==0 ){                /*   rule set 5   */
	  if( uu==6 )
	    y = RND125;
	  else if( un==3 )
	    y = RND125;
	  else if( ue==4 )
	    y = RND125;
	  else if( us==1 )
	    y = RND125;
	  else if( uw==2 )
	    y = RND125;
	  else{
	    y = 0;
	    if( ctl.do_moved_ants_calc!=0 ) move_cnt++;
	    if( ctl.do_msd_calc!=0 ) msd_y1 = 0;
	  }
	}

	else if( x==6 && d==0 ){                /*   rule set 6   */
	  if( dd==5 )
	    y = RND346;
	  else if( dn==3 )
	    y = RND346;
	  else if( de==4 )
	    y = RND346;
	  else if( ds==1 )
	    y = RND346;
	  else if( dw==2 )
	    y = RND346;
	  else{
	    y = 0;
	    if( ctl.do_moved_ants_calc!=0 ) move_cnt++;
	    if( ctl.do_msd_calc!=0 ) msd_y1 = 0;
	  }
	}

	else if( x==1 || x==2 || x==5 )         /*   rule set 7   */
	  y = RND125;
	else if( x==3 || x==4 || x==6 )         /*   rule set 7   */
	  y = RND346;

	if( x==0 && n==3 && e==4 )               /*   rule set 8   */
          y = 0;
	else if( x==0 && n==3 && s==1 )
          y = 0;
	else if( x==0 && n==3 && w==2 )
          y = 0;
	else if( x==0 && n==3 && u==6 )
          y = 0;
	else if( x==0 && n==3 && d==5 )
          y = 0;

	else if( x==0 && e==4 && s==1 )
          y = 0;
	else if( x==0 && e==4 && w==2 )
          y = 0;
	else if( x==0 && e==4 && u==6 )
          y = 0;
	else if( x==0 && e==4 && d==5 )
          y = 0;

	else if( x==0 && s==1 && w==2 )
          y = 0;
	else if( x==0 && s==1 && u==6 )
          y = 0;
	else if( x==0 && s==1 && d==5 )
          y = 0;

	else if( x==0 && w==2 && u==6 )
          y = 0;
	else if( x==0 && w==2 && d==5 )
          y = 0;
	else if( x==0 && u==6 && d==5 )
          y = 0;

	else if( x==0 && n==3){                  /*   rule set 9   */
          y = RND346;
          if( ctl.do_msd_calc!=0 ) msd_y1 = msd_n1;
        }
	else if( x==0 && e==4){
          y = RND346;
          if( ctl.do_msd_calc!=0 ) msd_y1 = msd_e1;
        }
	else if( x==0 && s==1){
          y = RND125;
          if( ctl.do_msd_calc!=0 ) msd_y1 = msd_s1;
        }
	else if( x==0 && w==2){
          y = RND125;
          if( ctl.do_msd_calc!=0 ) msd_y1 = msd_w1;
        }
	else if( x==0 && u==6){
          y = RND346;
          if( ctl.do_msd_calc!=0 ) msd_y1 = msd_u1;
        }
	else if( x==0 && d==5){
          y = RND125;
          if( ctl.do_msd_calc!=0 ) msd_y1 = msd_d1;
        }

	else if( x==0 )                          /*   rule set 10   */
          y = 0;

	lookup(sys.mat1, i, j, k) = y;

	if( ctl.do_msd_calc!=0 ) {
	  lookup(sys.msmat2, i, j, k) = msd_y1;
	}
      }
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
  printf("step = %d mvcnt = %d averaged_velocity = %f\n",
	 sys.time_step,move_cnt, sys.averaged_velocity[sys.time_step]); 
  printf("sys.number_of_walkers = %d\n",sys.number_of_walkers);
    show_matrix(sys.mat1);
*/

}

void set_bc(int *ants)
{
  int i, j, k;

  /* cyclic boundary condition setting for each of the x-y planes */
  for(k=2; k<ctl.mat_size+2; k++){ 
    /* corner adjustment 1 */
    *(ants+ctl.shift2*k)   = 
      *(ants + ( ctl.shift2*k + ctl.shift*(ctl.mat_size+1) - 4));
    *(ants+ctl.shift2*k+1) = 
      *(ants + ( ctl.shift2*k + ctl.shift*(ctl.mat_size+1) - 3));
    *(ants+ctl.shift2*k+ctl.shift) = 
      *(ants + ctl.shift2*k + ( ctl.shift*(ctl.mat_size+2) - 4));
    *(ants+ctl.shift2*k+(ctl.mat_size+5)) = 
      *(ants + ctl.shift2*k + ( ctl.shift*(ctl.mat_size+2) - 3));

    /* corner adjustment 2 */
    *(ants+ctl.shift2*k+(ctl.mat_size+2)) = 
      *(ants+ ctl.shift2*k + (ctl.shift*ctl.mat_size + 2));
    *(ants+ctl.shift2*k+(ctl.mat_size+3))   = 
      *(ants+ ctl.shift2*k + (ctl.shift*ctl.mat_size + 3));
    *(ants+ctl.shift2*k+2*(ctl.mat_size+3)) = 
      *(ants+ ctl.shift2*k + (ctl.shift*(ctl.mat_size+1)+2));
    *(ants+ctl.shift2*k+2*(ctl.mat_size+3)+1) = 
      *(ants+ ctl.shift2*k + (ctl.shift*(ctl.mat_size+1)+3));

    /* corner adjustment 3 */
    *(ants+ctl.shift2*k+(ctl.mat_size+3)*(ctl.mat_size+3)-1) = 
      *(ants+ ctl.shift2*k +3*ctl.shift-4);
    *(ants+ctl.shift2*k+(ctl.mat_size+3)*(ctl.mat_size+3)) = 
      *(ants+ ctl.shift2*k +3*ctl.shift-3);
    *(ants+ctl.shift2*k+(ctl.mat_size+3)*ctl.shift) = 
      *(ants+ ctl.shift2*k +4*ctl.shift-4);
    *(ants+ctl.shift2*k+(ctl.mat_size+3)*ctl.shift+1) = 
      *(ants+ ctl.shift2*k +4*ctl.shift-3);

    /* corner adjustment 4 */
    *(ants+ctl.shift2*k+ctl.shift*(ctl.mat_size+3)-2) = 
      *(ants+ ctl.shift2*k +2*ctl.shift+2);
    *(ants+ctl.shift2*k+ctl.shift*(ctl.mat_size+3)-1) = 
      *(ants+ ctl.shift2*k +2*ctl.shift+3);
    *(ants+ctl.shift2*k+ctl.shift*ctl.shift-2) = 
      *(ants+ ctl.shift2*k +3*ctl.shift+2);
    *(ants+ctl.shift2*k+ctl.shift*ctl.shift-1) = 
      *(ants+ ctl.shift2*k +3*ctl.shift+3);

    /* border adjustment   */
    for (i = 2; i < ctl.mat_size+2; i++){
      *(ants+ ctl.shift2*k +i) = 
	*(ants+ ctl.shift2*k +ctl.shift*ctl.mat_size+i);
      *(ants+ ctl.shift2*k +ctl.mat_size+4+i) = 
	*(ants+ ctl.shift2*k +ctl.shift*(ctl.mat_size+1)+i); 
      *(ants+ ctl.shift2*k +ctl.shift*(ctl.mat_size+2)+i) =
	*(ants+ ctl.shift2*k +2*ctl.shift+i);
      *(ants+ ctl.shift2*k +ctl.shift*(ctl.mat_size+3)+i) = 
	*(ants+ ctl.shift2*k +3*ctl.shift+i); 

      *(ants+ ctl.shift2*k +i*ctl.shift) = 
	*(ants+ ctl.shift2*k +(i+1)*ctl.shift-4);
      *(ants+ ctl.shift2*k +i*ctl.shift+1) = 
	*(ants+ ctl.shift2*k +(i+1)*ctl.shift-3);

      *(ants+ ctl.shift2*k +(i+1)*ctl.shift-2) = 
	*(ants+ ctl.shift2*k +i*ctl.shift+2);
      *(ants+ ctl.shift2*k +(i+1)*ctl.shift-1) = 
	*(ants+ ctl.shift2*k +i*ctl.shift+3);
    }
  }

  /* cyclic boundary condition setting for the */
  /* UP-UP, UP, DOWN, and DOWN-DOWN planes.    */
  for (i = 0; i < ctl.mat_size+4; i++){
    for (j = 0; j < ctl.mat_size+4; j++){
      *(ants+ ctl.shift*i + j) =                   /* UP-UP */
	*(ants+ (ctl.shift2*(ctl.shift-4)) + ctl.shift*i + j);
      *(ants+ ctl.shift2 + ctl.shift*i + j) =      /* UP */
	*(ants+ (ctl.shift2*(ctl.shift-3)) + ctl.shift*i + j);

      *(ants+ (ctl.shift2*(ctl.shift-2)) + ctl.shift*i + j) = 
	*(ants+ ctl.shift2*2 + ctl.shift*i + j);   /* DOWN */
      *(ants+ (ctl.shift2*(ctl.shift-1)) + ctl.shift*i + j) = 
	*(ants+ ctl.shift2*3 + ctl.shift*i + j);   /* DOWN-DOWN */
    }
  }
}

void mk_copy(int *original, int *copy)
{
  int i, j, k;

  for(i=0; i<ctl.mat_size+4; i++){
    for(j=0; j<ctl.mat_size+4; j++){
      for(k=0; k<ctl.mat_size+4; k++){
	*(copy+ctl.shift2*i+ctl.shift*j+k)  = 
	  *(original+ctl.shift2*i+ctl.shift*j+k);
      }
    }
  }
}

