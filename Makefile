CFLAGS=`pkg-config portaudio-2.0 --libs` -lpthread -Wall

LIBS=`pkg-config portaudio-2.0 --cflags-only-I` -Wall

SRC=$(wildcard *.c)
OBJECTS=$(patsubst %.c,%.o,$(wildcard *.c))

CC=clang

build: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS)

.c.o:
	$(CC) -c $< $(LIBS)

run: build
	./a.out



clean:
	rm $(OBJECTS)
