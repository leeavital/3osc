all:
	CC 3osc.c  `pkg-config portaudio-2.0 --libs` -lpthread  -Wall 

run: all
	./a.out
