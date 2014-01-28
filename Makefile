all:
	CC main.c  `pkg-config portaudio-2.0 --libs` -lpthread  -Wall 

run: all
	./a.out
