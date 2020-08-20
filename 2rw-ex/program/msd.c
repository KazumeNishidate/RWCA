#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rw.h"
#include "prototypes.h"

/* MSD calculation */

void calc_msd()
{
  int i, j, ii, jj;
  int ddx, ddy, dx2=0;

  for (i = 2; i < ctl.mat_size+2; i++){
    for (j = 2; j < ctl.mat_size+2; j++){

      if(sys.msmat1[ctl.shift*i+j]!=0){
	for (ii = 2; ii < ctl.mat_size+2; ii++){
	  for (jj = 2; jj < ctl.mat_size+2; jj++){

	    if(sys.msmat1[ctl.shift*i+j]==
	       sys.msmat2[ctl.shift*ii+jj]){

	      ddx = i-ii;     /* cyclic BC effect consideration for ddx */
	      if(ddx >  ctl.mat_size2) ddx -= ctl.mat_size;
	      if(ddx < -ctl.mat_size2) ddx += ctl.mat_size;

	      ddy = j-jj;     /* cyclic BC effect consideration for ddy */
	      if(ddy >  ctl.mat_size2) ddy -= ctl.mat_size;
	      if(ddy < -ctl.mat_size2) ddy += ctl.mat_size;

	      sys.msd_sum_x[sys.msmat1[ctl.shift*i+j]]+= ddx;
	      sys.msd_sum_y[sys.msmat1[ctl.shift*i+j]]+= ddy;
	    } /* [note] ddx = rx(t-1)-rx(t), ddy = ry(t-1)-ry(t)   */

	  }   /* sys.msd_sum_x[sys.msmat1[i]] = Sum(t)[ddx] = rx(0)-rx(t) */
	}     /* sys.msd_sum_y[sys.msmat1[i]] = Sum(t)[ddy] = ry(0)-ry(t) */
      }

    }
  }

  for(i=1;i<=sys.number_of_walkers;i++){  /* Sum(i)[ |r(0)-r(t)|^2 ] */
    dx2 += sys.msd_sum_x[i] * sys.msd_sum_x[i] + 
      sys.msd_sum_y[i] * sys.msd_sum_y[i];
  }

  /* MSD(t) = Sum(i)[ |r(0)-r(t)|^2 ]/N */
  sys.averaged_msd_value[sys.time_step] += 
    ( (double)dx2/(double)sys.number_of_walkers )/
      (double)ctl.average_iteration_num;
  
/* fix */
  sys.msd_value = (double)dx2/(double)sys.number_of_walkers;
  fprintf(fpout_msd,"%d  %f\n", sys.time_step, sys.msd_value);

/*
    printf(" num = %d\n",sys.number_of_walkers);
    
    show_matrix(sys.msmat0);
    show_matrix(sys.msmat2);
    for(i=1;i<=sys.number_of_walkers;i++){
      printf(" sys.msd_sum_x[%d] = %d\n", i, sys.msd_sum_x[i]);
      printf(" sys.msd_sum_y[%d] = %d\n", i, sys.msd_sum_y[i]);
    }
    printf("msd_value = %f\n",sys.msd_value); 
    printf("averaged_msd_value = %f\n",sys.averaged_msd_value[sys.time_step]); 
    getchar();
*/

}

void msd_ini()
{
  int i, j, cnt=1;

  for (i = 2; i < ctl.mat_size+2; i++){
    for (j = 2; j < ctl.mat_size+2; j++){

      if(sys.mat0[(ctl.mat_size+4)*i+j] > 0){
        sys.msmat0[(ctl.mat_size+4)*i+j] = cnt;
        cnt++;
      } 
      else {sys.msmat0[(ctl.mat_size+4)*i+j]=0;}
    }
  }

  set_bc(sys.msmat0);
  sys.msd_value = 0.0;
  sys.msd_sum_x = (int *)calloc(cnt, sizeof(int)); 
  sys.msd_sum_y = (int *)calloc(cnt, sizeof(int)); 

/* debug */
/*  printf("number of walkers = %d\n",cnt-1); */
/*  getchar(); */

}

