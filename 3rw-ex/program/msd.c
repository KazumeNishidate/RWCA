#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rw.h"
#include "prototypes.h"

/* MSD calculation */

void calc_msd()
{
  int i, j, k, ii, jj, kk;
  int ddx, ddy, ddz, dx2=0;

  for (i = 2; i < ctl.mat_size+2; i++){
    for (j = 2; j < ctl.mat_size+2; j++){
      for (k = 2; k < ctl.mat_size+2; k++){

	if(sys.msmat1[ctl.shift2*i+ctl.shift*j+k]!=0){
	  for (ii = 2; ii < ctl.mat_size+2; ii++){
	    for (jj = 2; jj < ctl.mat_size+2; jj++){
	      for (kk = 2; kk < ctl.mat_size+2; kk++){

		if(sys.msmat1[ctl.shift2*i+ctl.shift*j+k]==
		   sys.msmat2[ctl.shift2*ii+ctl.shift*jj+kk]){

		  ddx = i-ii;     /* cyclic BC effect consideration for ddx */
		  if(ddx >  ctl.mat_size2) ddx -= ctl.mat_size;
		  if(ddx < -ctl.mat_size2) ddx += ctl.mat_size;

		  ddy = j-jj;     /* cyclic BC effect consideration for ddy */
		  if(ddy >  ctl.mat_size2) ddy -= ctl.mat_size;
		  if(ddy < -ctl.mat_size2) ddy += ctl.mat_size;

		  ddz = k-kk;     /* cyclic BC effect consideration for ddz */
		  if(ddz >  ctl.mat_size2) ddz -= ctl.mat_size;
		  if(ddz < -ctl.mat_size2) ddz += ctl.mat_size;

		  sys.msd_sum_x[sys.msmat1[ctl.shift2*i+ctl.shift*j+k]]
		    += ddx;
		  sys.msd_sum_y[sys.msmat1[ctl.shift2*i+ctl.shift*j+k]]
		    += ddy;
		  sys.msd_sum_z[sys.msmat1[ctl.shift2*i+ctl.shift*j+k]]
		    += ddz;

		} /* [note] ddx = rx(t-1)-rx(t), ddy = ry(t-1)-ry(t)   */
	      }   /*        ddz = rz(t-1)-rz(t)                        */
	    }   /* sys.msd_sum_x[sys.msmat1[i]] = Sum(t)[ddx] = rx(0)-rx(t) */
	  }     /* sys.msd_sum_y[sys.msmat1[i]] = Sum(t)[ddy] = ry(0)-ry(t) */
	}       /* sys.msd_sum_z[sys.msmat1[i]] = Sum(t)[ddz] = rz(0)-rz(t) */

      }
    }
  }

  /* Sum(i)[ |r(0)-r(t)|^2 ] */
  for(i=1;i<=sys.number_of_walkers;i++){  
/* check */
/*
    printf("num = %d x y z = %d %d %d\n",i,sys.msd_sum_x[i],sys.msd_sum_y[i],sys.msd_sum_z[i]);
*/
    dx2 += sys.msd_sum_x[i] * sys.msd_sum_x[i] + 
      sys.msd_sum_y[i] * sys.msd_sum_y[i] + 
	sys.msd_sum_z[i] * sys.msd_sum_z[i];
  }

  /* <MSD(t)> = Sum(i)[ |r(0)-r(t)|^2 ]/N */
/* check */
/*
  printf("total msd sum (t) = %d\n",dx2);
*/
  sys.averaged_msd_value[sys.time_step] += 
    ( (double)dx2/(double)sys.number_of_walkers )/
      (double)ctl.average_iteration_num;

/* check */
/*
  printf("msd = %f\n",sys.averaged_msd_value[sys.time_step]);
  show_matrix(sys.msmat2);
*/

}

void msd_ini()
{
  int i, j, k, cnt=1;

  for (i = 2; i < ctl.mat_size+2; i++){
    for (j = 2; j < ctl.mat_size+2; j++){
      for (k = 2; k < ctl.mat_size+2; k++){

	if(sys.mat0[ctl.shift2*i+ctl.shift*j+k] > 0){
	  sys.msmat0[ctl.shift2*i+ctl.shift*j+k] = cnt;
	  cnt++;
	} 
	else {sys.msmat0[ctl.shift2*i+ctl.shift*j+k]=0;}
      }
    }
  }

  set_bc(sys.msmat0);
  sys.msd_sum_x = (int *)calloc(cnt, sizeof(int)); 
  sys.msd_sum_y = (int *)calloc(cnt, sizeof(int)); 
  sys.msd_sum_z = (int *)calloc(cnt, sizeof(int)); 

/* debug */
/*  printf("number of walkers = %d\n",cnt-1); */
/*  getchar(); */

}

