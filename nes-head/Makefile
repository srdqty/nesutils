CC= gcc
CFLAGS=-pedantic-errors -std=c89 -O3 -Wall
INCLUDES=
LIBS=
LDFLAGS=
SOURCES=nes-head.c
OBJECTS=$(SOURCES:.c=.o)
EXE=nes-head

all:
	$(CC) $(SOURCES) $(INCLUDES) $(CFLAGS) $(LIBS) $(LDFLAGS) -o $(EXE)

clean:
	rm -f $(OBJECTS) $(EXE)
