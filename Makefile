CFLAGS=`pkg-config portaudio-2.0 --libs` -lpthread -Wall
DEBUG_FLAGS=-g

LIBS=`pkg-config portaudio-2.0 --cflags-only-I` -Wall

SRC=$(wildcard *.c)
OBJECTS=$(patsubst %.c,%.o,$(wildcard *.c))

CC=clang

build: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(DEBUG_FLAGS)


debug: build
	lldb a.out

.c.o:
	$(CC) -c $< $(LIBS) $(DEBUG_FLAGS)

run: build
	./a.out



clean:
	rm $(OBJECTS)
