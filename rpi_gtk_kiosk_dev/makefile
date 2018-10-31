# change application name here (executable output name)
TARGET=rpi_gtk_kiosk

# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall

PTHREAD=-pthread

CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe

GTKLIB=`pkg-config --cflags --libs gtk+-3.0`
LIBS+=-L/usr/local/lib -lwiringPi

# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) $(LIBS) -export-dynamic -lX11

OBJS=    main.o		acceso_bio.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS) -lwiringPi
    
main.o: src/main.c	src/soporte.h
	$(CC) -c $(CCFLAGS) src/main.c $(GTKLIB) -o main.o 
	
acceso_bio.o: src/acceso_bio.c	src/soporte.h
	$(CC) -c $(CCFLAGS) src/acceso_bio.c $(GTKLIB) -o acceso_bio.o
    
clean:
	rm -f *.o $(TARGET)
