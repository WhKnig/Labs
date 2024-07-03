SOURCES = main.c tree.c vvod.c dilogs.c fin.c graf.c gen.c

OBJECTS = $(SOURCES:.c=.o)
	
CC = gcc
CFLAGS = -g -Wall

tabl: $(OBJECTS)
	$(CC) $(OBJECTS) -lreadline -lgvc -lcgraph -o tr -g -Wall

	rm -f *.o 

%.o: %.c $(SOURCES)
	$(CC) $(CFLAGS) -c $<


.PHONY: clean
clean:
	rm -f tr
