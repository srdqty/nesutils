CC= gcc
CFLAGS=-pedantic-errors -std=c89 -O3 -Wall
INCLUDES=
LIBS=
LDFLAGS=
SOURCES=extract-chr.c
OBJECTS=$(SOURCES:.c=.o)
EXE=extract-chr

all:
	$(CC) $(SOURCES) $(INCLUDES) $(CFLAGS) $(LIBS) $(LDFLAGS) -o $(EXE)

clean:
	rm -f $(OBJECTS) $(EXE)
