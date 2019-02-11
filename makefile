OBJECTS= main.o draw.o display.o
CFLAGS= -Wall
CC= gcc

run: main
	./main

main: $(OBJECTS)
	$(CC) -o main $(OBJECTS) -lm

main.o: main.c display.h draw.h ml6.h
	$(CC) -c main.c -lm

draw.o: draw.c draw.h display.h ml6.h
	$(CC) $(CFLAGS) -c draw.c

display.o: display.c display.h ml6.h
	$(CC) $(CFLAGS) -c display.c

clean:
	rm *.o *~
