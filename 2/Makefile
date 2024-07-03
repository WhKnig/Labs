SOURCES = main.c sort.c mstring.c in.c

OBJECTS = $(SOURCES:.c=.o)
	
CC = gcc
CFLAGS = -g -Wall

list: $(OBJECTS) list.o str.c 
	$(CC) $(OBJECTS) list.o str.c -lreadline -o list -D QUEUE_LIST -g -Wall 
	rm -f *.o 

vector: $(OBJECTS) vector.o str.c 
	$(CC) $(OBJECTS) vector.o str.c -lreadline -o vector -g -Wall
	rm -f *.o 

%.o: %.c $(SOURCES)
	$(CC) $(CFLAGS) -c $<

list.o: list.c
	$(CC) $(CFLAGS) -c list.c -D QUEUE_LIST

vector.o: vector.c
	$(CC) $(CFLAGS) -c vector.c

.PHONY: clean
clean:
	rm -f list vector
