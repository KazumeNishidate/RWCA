/* prototypes.h */

/* control.c */
void get_control_param(void);

/* main.c */
int main(void);

/* dynamics.c */
void move_walkers();
void set_bc(int *ants);
void mk_copy(int *original, int *copy);

/* msd.c */
void msd_ini();
void calc_msd();

/* init.c */
void set_init_conf();
void init_mem(void);  
void open_files(void);
void show_matrix(int *field);
void print_averaged_msd(void);
void print_matrix(int *field);
void print_averaged_velocity(void);

/* ran.c */
float ran1(long *idum);

/* xd.c */
void   xd(void);

/* xmycolor.c */
unsigned long MyColor();
