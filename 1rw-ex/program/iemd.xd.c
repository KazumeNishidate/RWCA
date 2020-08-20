#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>
#include  <X11/Xlib.h>
#include  <X11/Xutil.h>
#include  "prototypes.h"

/* maximum number of points to display in xd() */
#define  XD_MAXPTS 10000 

void xd(void)
{
  int i;
  char stringbuffer[100];
  static int cnt=0;
  static double delta = 45.0 * PI/180.0;
  static double mu=10.0;
  static int x_scale, y_scale, z_scale;
  short ptx[XD_MAXPTS],pty[XD_MAXPTS],ptz[XD_MAXPTS];
  static Display *d;
  static Window w0,w1,w2,w3,w4;
  static GC gc;

/* change the Window Attributes */
  static XSetWindowAttributes attr;
  static unsigned long color[6];
  static XPoint xypts[XD_MAXPTS];
  static XPoint yzpts[XD_MAXPTS];
  static XPoint zxpts[XD_MAXPTS];
  static XPoint xyzpts[XD_MAXPTS];

/* initialize the window system */
  if(cnt==0){
    d = XOpenDisplay (NULL); /* connect to the server */
    w0 = XCreateSimpleWindow(d, RootWindow(d,0),0,0,480,500,2,0,1);
    w1 = XCreateSimpleWindow(d, w0,  30,  40, 200, 200, 2, 0, 1); /* x-y */
    w2 = XCreateSimpleWindow(d, w0, 250,  40, 200, 200, 2, 0, 1); /* y-z */
    w3 = XCreateSimpleWindow(d, w0,  30, 270, 200, 200, 2, 0, 1); /* z-x */
    w4 = XCreateSimpleWindow(d, w0, 250, 270, 200, 200, 2, 0, 1); /* x-y-z */
    color[0] = MyColor(d,"red");
    color[1] = MyColor(d,"blue");
    color[2] = MyColor(d,"black");
    color[3] = MyColor(d,"white");
    color[4] = MyColor(d,"green");
    color[5] = MyColor(d,"yellow");

/* change the Window attributes */
    attr.backing_store = Always;
    XChangeWindowAttributes(d, w0, CWBackingStore, &attr );
    XChangeWindowAttributes(d, w1, CWBackingStore, &attr );
    XChangeWindowAttributes(d, w2, CWBackingStore, &attr );
    XChangeWindowAttributes(d, w3, CWBackingStore, &attr );
    XChangeWindowAttributes(d, w4, CWBackingStore, &attr );

/* Mapping */
    XMapWindow(d,w0);
    XMapSubwindows(d,w0);
    gc = XCreateGC (d,w0,0,0);
    XStoreName (d, w0, "IEMD");
    XSetIconName (d, w0, "IEMD");

/* ======= Title =======  */
    XDrawString (d,w0,gc,120,260,"x-y",3);
    XDrawString (d,w0,gc,120,490,"y-z",3);
    XDrawString (d,w0,gc,330,260,"z-x",3);
    XDrawString (d,w0,gc,325,490,"x-y-z",5);
    cnt = 1;
  }

/* re-scale all of the atomic positions */
  x_scale = (int)(190.0/sys.Lx);
  y_scale = (int)(190.0/sys.Ly);
  z_scale = (int)(190.0/sys.Lz);      

  for(i=0; i<sys.N; i++) {
    ptx[i]=(int)(sys.rx[i]*x_scale); 
    pty[i]=(int)(sys.ry[i]*y_scale); 
    ptz[i]=(int)(sys.rz[i]*z_scale); 
  }
  for(i=0; i<sys.N; i++) {
    xypts[i].x = (ptx[i])+8;
    xypts[i].y = (pty[i])+8;
  }
  for(i=0; i<sys.N; i++) {
    yzpts[i].x = (pty[i])+8;
    yzpts[i].y = (ptz[i])+8;
  }
  for(i=0; i<sys.N; i++) {
    zxpts[i].x = (ptz[i])+8;
    zxpts[i].y = (ptx[i])+8;
  }
  for(i=0; i<sys.N; i++) {
    xyzpts[i].x = (ptx[i]-((int)mu*cos(delta))*ptz[i])+120;
    xyzpts[i].y = (pty[i]-((int)mu*sin(delta))*ptz[i])+120;
  }

/* ====== Real Time Step ======= */
  XSetForeground (d,gc,color[white]);
  XFillRectangle(d,w0,gc,0,0,400,25);
  XSetForeground (d,gc,color[black]);
  sprintf(stringbuffer,"TimeStep = %d  ( %9.2f [fs] ) ",sys.step, 
	  sys.step*sys.step_2_fsec);
  XDrawString(d,w0,gc,15,20,stringbuffer,strlen(stringbuffer));

/*  Plot  */    
  XDrawPoints (d,w1,gc,xypts,sys.N,CoordModeOrigin);
  XDrawPoints (d,w2,gc,yzpts,sys.N,CoordModeOrigin);
  XDrawPoints (d,w3,gc,zxpts,sys.N,CoordModeOrigin);
  XDrawPoints (d,w4,gc,xyzpts,sys.N,CoordModeOrigin);

  XFlush(d);
}
