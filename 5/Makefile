SOURCES = main.c vvod.c dilogs.c picture.c
OBJECTS = $(SOURCES:.c=.o)
CC = gcc
CFLAGS = -g -Wall

LIBRARY = libgraph.a

LIB_SOURCES = graph.c sp_tasks.c tree_picture.c
LIB_OBJECTS = $(LIB_SOURCES:.c=.o)


all: $(LIBRARY) gr

gr: $(OBJECTS) $(LIBRARY)
	$(CC) $(OBJECTS) -L. -lgraph -lreadline -lgvc -lcgraph -o gr -g -Wall
	rm -f *.o


$(LIBRARY): $(LIB_OBJECTS)
	ar rcs $(LIBRARY) $(LIB_OBJECTS)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -f gr *.o $(LIBRARY)
