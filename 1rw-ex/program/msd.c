#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rw.h"
#include "prototypes.h"

/* MSD calculation */

void calc_msd()
{
  int i, j;
  int ddx, dx2=0;

  for (i = 2; i < ctl.mat_size+2; i++){
    if(sys.msmat1[i]!=0){
      for (j = 2; j < ctl.mat_size+2; j++){
	if(sys.msmat1[i]==sys.msmat2[j]){
	  ddx = i - j;     /* cyclic BC effect consideration for ddx */
	  if(ddx >  ctl.mat_size2) ddx -= ctl.mat_size;
	  if(ddx < -ctl.mat_size2) ddx += ctl.mat_size;
	  sys.msd_sum[sys.msmat1[i]]+= ddx;
	}
      }   /* [note] ddx = r(t-1)-r(t)                                */
    }     /* sys.msd_sum[sys.msmat1[i]] = Sum(t)[ ddx ] = r(0)-r(t)  */
  }

  for(i=1;i<=sys.number_of_walkers;i++){  /* Sum(i)[ |r(0)-r(t)|^2 ] */
    dx2 += sys.msd_sum[i] * sys.msd_sum[i];
  }

  /* MSD(t) = Sum(i)[ |r(0)-r(t)|^2 ]/N */
  sys.averaged_msd_value[sys.time_step] += 
    ( (double)dx2/(double)sys.number_of_walkers )/
      (double)ctl.average_iteration_num;
  
/* fix */
/*
  sys.msd_value = (double)dx2/(double)sys.number_of_walkers;
  fprintf(fpout_msd,"%d  %f\n", sys.time_step, sys.msd_value);
  if(sys.time_step==50){
    printf(" num = %d\n",sys.number_of_walkers);
    show_matrix(sys.msmat0);
    show_matrix(sys.msmat2);
    for(i=1;i<=sys.number_of_walkers;i++){
      printf(" sys.msd_sum[%d] = %d\n", i, sys.msd_sum[i]);
    }
    printf("msd_value = %f\n",sys.msd_value); 
    printf("averaged_msd_value = %f\n",sys.averaged_msd_value[sys.time_step]); 
    getchar();
  }
*/
}

void msd_ini()
{
  int i, cnt=1;

  for (i = 2; i < ctl.mat_size+2; i++){
      if(sys.mat0[i] > 0){
        sys.msmat0[i] = cnt;
        cnt++;
      } 
      else {sys.msmat0[i]=0;}
    }
  set_bc(sys.msmat0);
  sys.msd_value = 0.0;
  sys.msd_sum = (int *)calloc(cnt, sizeof(int)); 

/* debug */
/*  printf("number of walkers = %d\n",cnt-1); */
/*  getchar(); */

}

