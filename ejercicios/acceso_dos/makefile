# change application name here (executable output name)
TARGET=template_app
 
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
 
# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic
 
OBJS=    main.o		complementario.o	configuraciones.o
 
all: $(OBJS)
	$(LD)	-o	$(TARGET)	$(OBJS)	$(LDFLAGS)
    
main.o: src/main.c	
	$(CC)	-c	$(CCFLAGS)	src/main.c	$(GTKLIB)	-o	main.o

complementario.o: src/complementario.c	
	$(CC)	-c	$(CCFLAGS)	src/complementario.c	$(GTKLIB)	-o	complementario.o
	
configuraciones.o: src/configuraciones.c	
	$(CC)	-c	$(CCFLAGS)	src/configuraciones.c	$(GTKLIB)	-o	configuraciones.o	

    
clean:
	rm	-f	*.o	$(TARGET)
