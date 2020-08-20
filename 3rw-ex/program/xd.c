#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <math.h>
#include  <X11/Xlib.h>
#include  <X11/Xutil.h>
#include "rw.h"
#include "prototypes.h"


void xd(void)
{
  int i, j, k, ii;
  char stringbuffer[100];
  static int cnt=0;
  /* "cavalier projection" [degree] */
  static double DELTA=40.0;
  static double MU=0.3;

  static int x_shift=120, y_shift=120;
  static double box_corner_position_X[8];
  static double box_corner_position_Y[8];
  static double box_corner_position_Z[8];
  static int box1_x, box2_x;
  static int box1_y, box2_y;

  static double x_scale, y_scale, z_scale;
  int x_position, y_position;

  static Display *d;
  static Window w0, w1, w2, w3, w4;
  static GC gc;

/* change the Window Attributes */
  static XSetWindowAttributes attr;
  static unsigned long color[6];


/* initialize the window system */
  if(cnt==0){
    d = XOpenDisplay (NULL); /* connect to the server */
    w0 = XCreateSimpleWindow(d, RootWindow(d,0),0,0,480,500,2,0,1);

    color[0] = MyColor(d,"red");
    color[1] = MyColor(d,"blue");
    color[2] = MyColor(d,"black");
    color[3] = MyColor(d,"white");
    color[4] = MyColor(d,"green");
    color[5] = MyColor(d,"yellow");

/* change the Window attributes */
    attr.backing_store = Always;
    XChangeWindowAttributes(d, w0, CWBackingStore, &attr );

/* Mapping */
    XMapWindow(d,w0);
    XMapSubwindows(d,w0);
    gc = XCreateGC (d,w0,0,0);
    XStoreName (d, w0, "RW1D");
    XSetIconName (d, w0, "RW1D");

/* re-scale all of the atomic positions */
    x_scale = 300.0/ (double)(ctl.mat_size+4);
    y_scale = 300.0/ (double)(ctl.mat_size+4);
    z_scale = 300.0/ (double)(ctl.mat_size+4);

    box_corner_position_X[0]= -2.0;
    box_corner_position_Y[0]= -2.0;
    box_corner_position_Z[0]= -2.0;

    box_corner_position_X[1]= (double)ctl.mat_size+2.0;
    box_corner_position_Y[1]= -2.0;
    box_corner_position_Z[1]= -2.0;

    box_corner_position_X[2]= -2.0;
    box_corner_position_Y[2]= (double)ctl.mat_size+2.0;
    box_corner_position_Z[2]= -2.0;

    box_corner_position_X[3]= -2.0;
    box_corner_position_Y[3]= -2.0;
    box_corner_position_Z[3]= (double)ctl.mat_size+2.0;

    box_corner_position_X[4]= (double)ctl.mat_size+2.0;
    box_corner_position_Y[4]= (double)ctl.mat_size+2.0;
    box_corner_position_Z[4]= -2.0;

    box_corner_position_X[5]= (double)ctl.mat_size+2.0;
    box_corner_position_Y[5]= -2.0;
    box_corner_position_Z[5]= (double)ctl.mat_size+2.0;

    box_corner_position_X[6]= -2.0;
    box_corner_position_Y[6]= (double)ctl.mat_size+2.0;
    box_corner_position_Z[6]= (double)ctl.mat_size+2.0;

    box_corner_position_X[7]= (double)ctl.mat_size+2.0;
    box_corner_position_Y[7]= (double)ctl.mat_size+2.0;
    box_corner_position_Z[7]= (double)ctl.mat_size+2.0;

    cnt = 1;
  }

  XSetForeground (d,gc,color[black]);
  XFillRectangle(d,w0,gc,0,0,480,500);

/* draw frame lines in 3d */

  XSetForeground(d,gc,color[white]);

  for(i=1;i<4;i++){
    box1_x = (int)((box_corner_position_X[0]-
	    MU*cos(DELTA/180.0)*box_corner_position_Z[0])*x_scale+x_shift);
    box1_y = (int)((box_corner_position_Y[0]-
	    MU*sin(DELTA/180.0)*box_corner_position_Z[0])*y_scale+y_shift);
    box2_x = (int)((box_corner_position_X[i]-
	    MU*cos(DELTA/180.0)*box_corner_position_Z[i])*x_scale+x_shift);
    box2_y = (int)((box_corner_position_Y[i]-
	    MU*sin(DELTA/180.0)*box_corner_position_Z[i])*y_scale+y_shift);

    XDrawLine(d, w0, gc, box1_x, box1_y, box2_x, box2_y);
  }

    box1_x = (int)((box_corner_position_X[1]-
	    MU*cos(DELTA/180.0)*box_corner_position_Z[1])*x_scale+x_shift);
    box1_y = (int)((box_corner_position_Y[1]-
	    MU*sin(DELTA/180.0)*box_corner_position_Z[1])*y_scale+y_shift);
    box2_x = (int)((box_corner_position_X[4]-
	    MU*cos(DELTA/180.0)*box_corner_position_Z[4])*x_scale+x_shift);
    box2_y = (int)((box_corner_position_Y[4]-
	    MU*sin(DELTA/180.0)*box_corner_position_Z[4])*y_scale+y_shift);

    XDrawLine(d, w0, gc, box1_x, box1_y, box2_x, box2_y);

    box1_x = (int)((box_corner_position_X[1]-
	    MU*cos(DELTA/180.0)*box_corner_position_Z[1])*x_scale+x_shift);
    box1_y = (int)((box_corner_position_Y[1]-
	    MU*sin(DELTA/180.0)*box_corner_position_Z[1])*y_scale+y_shift);
    box2_x = (int)((box_corner_position_X[5]-
	    MU*cos(DELTA/180.0)*box_corner_position_Z[5])*x_scale+x_shift);
    box2_y = (int)((box_corner_position_Y[5]-
	    MU*sin(DELTA/180.0)*box_corner_position_Z[5])*y_scale+y_shift);

    XDrawLine(d, w0, gc, box1_x, box1_y, box2_x, box2_y);

    box1_x = (int)((box_corner_position_X[2]-
	    MU*cos(DELTA/180.0)*box_corner_position_Z[2])*x_scale+x_shift);
    box1_y = (int)((box_corner_position_Y[2]-
	    MU*sin(DELTA/180.0)*box_corner_position_Z[2])*y_scale+y_shift);
    box2_x = (int)((box_corner_position_X[4]-
	    MU*cos(DELTA/180.0)*box_corner_position_Z[4])*x_scale+x_shift);
    box2_y = (int)((box_corner_position_Y[4]-
	    MU*sin(DELTA/180.0)*box_corner_position_Z[4])*y_scale+y_shift);

    XDrawLine(d, w0, gc, box1_x, box1_y, box2_x, box2_y);


    box1_x = (int)((box_corner_position_X[2]-
	    MU*cos(DELTA/180.0)*box_corner_position_Z[2])*x_scale+x_shift);
    box1_y = (int)((box_corner_position_Y[2]-
	    MU*sin(DELTA/180.0)*box_corner_position_Z[2])*y_scale+y_shift);
    box2_x = (int)((box_corner_position_X[6]-
	    MU*cos(DELTA/180.0)*box_corner_position_Z[6])*x_scale+x_shift);
    box2_y = (int)((box_corner_position_Y[6]-
	    MU*sin(DELTA/180.0)*box_corner_position_Z[6])*y_scale+y_shift);

    XDrawLine(d, w0, gc, box1_x, box1_y, box2_x, box2_y);

    box1_x = (int)((box_corner_position_X[3]-
	    MU*cos(DELTA/180.0)*box_corner_position_Z[3])*x_scale+x_shift);
    box1_y = (int)((box_corner_position_Y[3]-
	    MU*sin(DELTA/180.0)*box_corner_position_Z[3])*y_scale+y_shift);
    box2_x = (int)((box_corner_position_X[5]-
	    MU*cos(DELTA/180.0)*box_corner_position_Z[5])*x_scale+x_shift);
    box2_y = (int)((box_corner_position_Y[5]-
	    MU*sin(DELTA/180.0)*box_corner_position_Z[5])*y_scale+y_shift);

    XDrawLine(d, w0, gc, box1_x, box1_y, box2_x, box2_y);

    box1_x = (int)((box_corner_position_X[3]-
	    MU*cos(DELTA/180.0)*box_corner_position_Z[3])*x_scale+x_shift);
    box1_y = (int)((box_corner_position_Y[3]-
	    MU*sin(DELTA/180.0)*box_corner_position_Z[3])*y_scale+y_shift);
    box2_x = (int)((box_corner_position_X[6]-
	    MU*cos(DELTA/180.0)*box_corner_position_Z[6])*x_scale+x_shift);
    box2_y = (int)((box_corner_position_Y[6]-
	    MU*sin(DELTA/180.0)*box_corner_position_Z[6])*y_scale+y_shift);

    XDrawLine(d, w0, gc, box1_x, box1_y, box2_x, box2_y);

  for(i=4;i<7;i++){
    box1_x = (int)((box_corner_position_X[7]-
	    MU*cos(DELTA/180.0)*box_corner_position_Z[7])*x_scale+x_shift);
    box1_y = (int)((box_corner_position_Y[7]-
	    MU*sin(DELTA/180.0)*box_corner_position_Z[7])*y_scale+y_shift);
    box2_x = (int)((box_corner_position_X[i]-
	    MU*cos(DELTA/180.0)*box_corner_position_Z[i])*x_scale+x_shift);
    box2_y = (int)((box_corner_position_Y[i]-
	    MU*sin(DELTA/180.0)*box_corner_position_Z[i])*y_scale+y_shift);

    XDrawLine(d, w0, gc, box1_x, box1_y, box2_x, box2_y);
  }


  if(sys.time_step == ctl.max_time_step-10) getchar();

  ii = 1;

  for (i = 2; i < ctl.mat_size+2; i++){
    for (j = 2; j < ctl.mat_size+2; j++){
      for (k = 2; k < ctl.mat_size+2; k++){

	if(sys.mat0[ctl.shift2*i+ctl.shift*j+k]>0){

	  x_position = (int)(( (double)(i)-MU*cos(DELTA/180.0)*(double)k)*x_scale+x_shift );
	  y_position = (int)(( (double)(j)-MU*cos(DELTA/180.0)*(double)k)*y_scale+y_shift );

	  XSetForeground (d,gc,color[red]);
	  
	  XFillArc(d,w0,gc,x_position,y_position,10,10,0,360*64);
	  ii++;
      }

      }
    }
  }
  printf("ii-1 = %d\n",ii-1); 

/* ====== Real Time Step ======= */
  XSetForeground (d,gc,color[white]);
  sprintf(stringbuffer,"RWCA2d TimeStep = %d ",sys.time_step);
  XDrawString(d,w0,gc,15,20,stringbuffer,strlen(stringbuffer));

  XFlush(d);
}
