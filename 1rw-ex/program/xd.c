#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>
#include  <string.h>
#include  <X11/Xlib.h>
#include  <X11/Xutil.h>
#include "rw.h"
#include "prototypes.h"

/* maximum number of points to display in xd() */
#define  XD_MAXPTS 10000

void xd(void)
{
  int i, ii;
  char stringbuffer[100];
  static int cnt=0;
  static double x_scale, y_scale;
  short ptx[XD_MAXPTS],pty[XD_MAXPTS];
  static Display *d;
  static Window w0,w1,w2,w3,w4;
  static GC gc;

/* change the Window Attributes */
  static XSetWindowAttributes attr;
  static unsigned long color[6];
  static XPoint xypts[XD_MAXPTS];

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
    x_scale = 450.0/ (double)(ctl.mat_size+4);
    y_scale = 450.0/ (double)ctl.max_time_step;

    cnt = 1;
  }

  if(sys.time_step == ctl.max_time_step-10) getchar();

  ii = 1;
  for(i=2; i<ctl.mat_size+2; i++) {
    if(sys.mat0[i]>0){
      xypts[ii].x=(int)( (double)i*x_scale )+20;
      xypts[ii].y=(int)( (double)sys.time_step*y_scale)+30;
/*
      printf("ii= %d  xypts.x = %d  xypts.y = %d\n", ii, xypts[ii].x, xypts[ii].y);
*/
      ii++;
    }
  }

/* ====== Real Time Step ======= */

  XSetForeground (d,gc,color[white]);
  XFillRectangle(d,w0,gc,0,0,400,25);
  XSetForeground (d,gc,color[black]);
  sprintf(stringbuffer,"TimeStep = %d ",sys.time_step);
  XDrawString(d,w0,gc,15,20,stringbuffer,strlen(stringbuffer));

/*  Plot  */
  XSetForeground (d,gc,color[green]);  
  XDrawPoints (d,w0,gc,xypts,ii-1,CoordModeOrigin);

  XFlush(d);
}
