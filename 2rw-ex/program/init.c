#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rw.h"
#include "prototypes.h"

/****
 set the initial configuration of the system
****/
void set_init_conf()
{
  int i, j, cnt=0;

  while(cnt==0){  /*=== to avoid a vacant system ===*/
    cnt = 0; 

    for (i = 2; i < ctl.mat_size+2; i++){
      for (j = 2; j < ctl.mat_size+2; j++){
	sys.mat0[(ctl.mat_size+4)*i+j] = (int)(4*ran1(sys.random_seed)+1)*
	((int)(ran1(sys.random_seed)+ctl.concentration));
	if(sys.mat0[(ctl.mat_size+4)*i+j]>0) cnt++;
      }
    }
  } 
  sys.number_of_walkers = cnt;
/*
  printf("num = %d\n",cnt);
  printf("prob. = %f\n",(double)cnt/(double)ctl.mat_size);
  getchar();
*/
  set_bc(sys.mat0);
}

void open_files(void)
{
  if((fpout = fopen("../files/out","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }
  if((fpout_msd = fopen("../files/msd","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }
  if((fpout_move = fopen("../files/move","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }
}

void init_mem(void){
  int *mat_mem0, *mat_mem1, *mat_mem2;
  int *msmat_mem0, *msmat_mem1, *msmat_mem2;
  int *dstmat_mem;
  int n;
  
  n = ctl.mat_size+4;

  mat_mem0 = (int *)calloc(n*n, sizeof(int)); 
  mat_mem1 = (int *)calloc(n*n, sizeof(int)); 
  mat_mem2 = (int *)calloc(n*n, sizeof(int)); 
  sys.mat0 = mat_mem0;
  sys.mat1 = mat_mem1;
  sys.mat2 = mat_mem2;

  if(ctl.do_msd_calc != 0){  
    msmat_mem0 = (int *)calloc(n*n, sizeof(int)); 
    msmat_mem1 = (int *)calloc(n*n, sizeof(int)); 
    msmat_mem2 = (int *)calloc(n*n, sizeof(int)); 
    sys.msmat0 = msmat_mem0;
    sys.msmat1 = msmat_mem1;
    sys.msmat2 = msmat_mem2;
    sys.averaged_msd_value = (double *)calloc(ctl.max_time_step+1, 
					      sizeof(double)); 
    sys.averaged_velocity = (double *)calloc(ctl.max_time_step+1, 
					      sizeof(double)); 
  }
}

void show_matrix(int *field){
  int i, j;
/*
  for(i=0; i<ctl.mat_size+4; i++){
    for(j=0; j<ctl.mat_size+4; j++){
      printf(" %2d",field[(ctl.mat_size+4)*i+j]);
    }
    printf("\n");
  }
  printf("\n");
*/

  for(i=2; i<ctl.mat_size+2; i++){
    for(j=2; j<ctl.mat_size+2; j++){
      printf(" %d",field[(ctl.mat_size+4)*i+j]);
    }
    printf("\n");
  }
  printf("\n");

}

void print_matrix(int *field){
  int i, j;
/*
  for(i=0; i<ctl.mat_size+4; i++){
    for(j=0; j<ctl.mat_size+4; j++){
      fprintf(fpout," %d",field[(ctl.mat_size+4)*i+j]);
    }
    fprintf(fpout,"\n");
  }
  fprintf(fpout,"\n");
*/

  for(i=2; i<ctl.mat_size+2; i++){
    for(j=2; j<ctl.mat_size+2; j++){
      fprintf(fpout," %d",field[(ctl.mat_size+4)*i+j]);
    }
    fprintf(fpout,"\n");
  }
  fprintf(fpout,"\n");

}

void print_averaged_msd(void)
{
  int i=0;
  for(i=0;i<ctl.max_time_step;i++){
    fprintf(fpout_msd,"%d  %f\n", i, sys.averaged_msd_value[i]);
  }
}

void print_averaged_velocity(void)
{
  int i=0;
  for(i=0;i<ctl.max_time_step;i++){
    fprintf(fpout_move,"%d  %f\n", i, sys.averaged_velocity[i]);
  }
}
