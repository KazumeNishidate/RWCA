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
  int i, cnt=0;

  while(cnt==0){ /*=== to avoid a vacant system ===*/
    cnt = 0;
    for (i = 2; i < ctl.mat_size+2; i++){
      sys.mat0[i] = (int)(2*ran1(sys.random_seed)+1)*
	((int)(ran1(sys.random_seed)+ctl.concentration));
      if(sys.mat0[i]>0) cnt++;
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

  mat_mem0 = (int *)calloc(ctl.mat_size+4, sizeof(int)); 
  mat_mem1 = (int *)calloc(ctl.mat_size+4, sizeof(int)); 
  mat_mem2 = (int *)calloc(ctl.mat_size+4, sizeof(int)); 
  sys.mat0 = mat_mem0;
  sys.mat1 = mat_mem1;
  sys.mat2 = mat_mem2;

  if(ctl.do_msd_calc != 0){  
    msmat_mem0 = (int *)calloc(ctl.mat_size+4, sizeof(int)); 
    msmat_mem1 = (int *)calloc(ctl.mat_size+4, sizeof(int)); 
    msmat_mem2 = (int *)calloc(ctl.mat_size+4, sizeof(int)); 
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
  int i;
/*
  for(i=0; i<ctl.mat_size+4; i++){
    printf(" %d",field[i]);
  }
  printf("\n");
*/
  for(i=2; i<ctl.mat_size+2; i++){
    printf(" %d",field[i]);
  }
  printf("\n");

}

void print_matrix(int *field){
  int i;
/*
  for(i=0; i<ctl.mat_size+4; i++){
    fprintf(fpout," %d",field[i]);
  }
  fprintf(fpout,"\n");
*/
  for(i=2; i<ctl.mat_size+2; i++){
    fprintf(fpout," %d",field[i]);
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
