SOURCES = main.c tabl.c vvod.c fin.c dilogs.c

OBJECTS = $(SOURCES:.c=.o)
	
CC = gcc
CFLAGS = -g -Wall

tabl: $(OBJECTS)
	$(CC) $(OBJECTS) -lreadline -o tabl -g -Wall 
	rm -f *.o 

%.o: %.c $(SOURCES)
	$(CC) $(CFLAGS) -c $<


.PHONY: clean
clean:
	rm -f tabl
