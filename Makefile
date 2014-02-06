CFLAGS=`pkg-config portaudio-2.0 --libs` -lpthread -Wall
DEBUG_FLAGS=-g
OUT=3osc

LIBS=`pkg-config portaudio-2.0 --cflags-only-I`
LIB_FLEX=-L/usr/local/Cellar/flex/2.5.37/lib/ -lfl

SRC=$(wildcard *.c)
OBJECTS=$(patsubst %.c,%.o,$(wildcard *.c))

CC=clang

build: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(DEBUG_FLAGS) -o $(OUT)


debug: build
	lldb $(OUT)

.c.o:
	$(CC) -c $< $(LIBS) $(DEBUG_FLAGS)

run: build
	./$(OUT)



clean:
	rm $(OBJECTS)
