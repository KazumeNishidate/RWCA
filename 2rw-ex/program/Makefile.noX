CC= gcc
CFLAGS= -O2 

LIBS= -lm 

SOURCES= init.c main.c ran.c control.c msd.c dynamics.c
OBJECTS= init.o main.o ran.o control.o msd.o dynamics.o

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
