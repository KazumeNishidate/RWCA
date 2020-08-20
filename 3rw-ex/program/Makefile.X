### Compile command HP-UX
###  for FreeBSD
CC= gcc
CFLAGS=  -fstrength-reduce -O 

### Include files and library ################################
###  where is the X include file "Xlib.h" and "Xutil.h"?
INC=  -I/usr/include/X11R5 -I/usr/include/X11 -I/usr/X11R6/include/X11

###  where is the X library "libX11.a"?
LIBS= -lm  -L/usr/X11R6/lib -L/usr/lib/X11R5 -lX11

##############################################################

###  Run options  ############################################
RUN_OPTIONS= -DXD

SOURCES= init.c main.c ran.c control.c msd.c dynamics.c xd.c xmycolor.c
OBJECTS= init.o main.o ran.o control.o msd.o dynamics.o xd.o xmycolor.o

TARGET= rw

.c.o	:$(SOURCES)
	$(CC) -c $(CFLAGS) $(INC) $(RUN_OPTIONS) $< -o $@ 

$(TARGET)	:$(OBJECTS)
	$(CC) $(CFLAGS) $(RUN_OPTIONS) -o $(TARGET) $(OBJECTS) $(LIBS)

clean	:
	rm -f $(OBJECTS) *.core core a.out *~ "#"* *.ln
#	rm -f $(OBJECTS) *.core core $(TARGET) a.out *~ "#"*

lint	:
	lint -cbx $(SOURCES)
