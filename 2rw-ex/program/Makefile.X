CC= gcc
CFLAGS=  -O2 

INC=  -I/usr/include/X11R5 -I/usr/include/X11 -I/usr/X11R6/include/X11  -I/opt/X11/include
LIBS= -lm -L/usr/X11R6/lib  -lX11

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
