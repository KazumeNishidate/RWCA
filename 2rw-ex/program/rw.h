/*------------------ global definitions ----------------------------------*/

/* input and output files */
FILE *fpin, *fpout, *fpout_msd, *fpout_move;

/*------------------ global variables -------------------------------------*/
typedef	struct {

  int max_time_step;    /* max time step */
  int mat_size;         /* system size   */
  int mat_size2;        /* mat_size/2: will be used at "msd_calc()"  */
  int shift;            /* column shift = mat_size + 4               */
  double concentration; /* initial concentration probability         */

  int do_msd_calc;            /* mean squared displacement calculation   */
  int do_moved_ants_calc;     /* calculation of number of moved walkers  */
  int average_iteration_num;  /* number of runs for averaged calculation */
} calc_control;

typedef	struct {

  long tdumy;   /* dummy variable for time() function     */ 
  long seed;    /* seed for random number genelater       */

  int time_step;    /* current number of time step */
  int average_step; /* current average step        */

  int *mat0; 
  int *mat1; 
  int *mat2;  /* not used */
  int *msmat0;
  int *msmat1; 
  int *msmat2; 

  int    *msd_sum_x;
  int    *msd_sum_y;
  double msd_value;
  double *averaged_msd_value;
  double *averaged_velocity;

  double *accumulation;
  double *distinct_sites;
  int number_of_walkers;

  long *random_seed;
  float random;

} system_property;

/* "enum" declaration to use in X files */
enum {red, blue, black, white, green, yellow};

/*------------------- declaration for the structures ----------------------*/

calc_control ctl;
system_property sys;


