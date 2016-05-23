CC= gcc
CFLAGS=-pedantic-errors -std=c89 -O3 -Wall
INCLUDES=
LIBS=
LDFLAGS=
SOURCES=chr-rom-to-bmp.c
OBJECTS=$(SOURCES:.c=.o)
EXE=chr-rom-to-bmp

all:
	$(CC) $(SOURCES) $(INCLUDES) $(CFLAGS) $(LIBS) $(LDFLAGS) -o $(EXE)

clean:
	rm -f $(OBJECTS) $(EXE)
