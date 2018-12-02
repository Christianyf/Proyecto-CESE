# change application name here (executable output name)
TARGET=servidor

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

OBJS=    server.o		ClientData.o	

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS) -lwiringPi
    
server.o: src/server.c	src/ClientData.h
	$(CC) -c $(CCFLAGS) src/server.c $(GTKLIB) -o server.o 
	
ClientData.o: src/ClientData.c	src/ClientData.h
	$(CC) -c $(CCFLAGS) src/ClientData.c $(GTKLIB) -o ClientData.o

    
clean:
	rm -f *.o $(TARGET)
