CC=gcc
CFLAGS=-Wall -g
OBJS=main.o memoria.o processo.o

all: simulador

simulador: $(OBJS)
	$(CC) $(CFLAGS) -o simulador $(OBJS)

main.o: main.c memoria.h processo.h
memoria.o: memoria.c memoria.h
processo.o: processo.c processo.h

clean:
	rm -f *.o simulador 