CFLAGS=`pkg-config portaudio-2.0 --libs` lpthread -Wall



all:
	CC main.c 3osc.c ftable.c  `pkg-config portaudio-2.0 --libs` -lpthread  -Wall 

run: all
	./a.out
