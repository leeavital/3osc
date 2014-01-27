all:
	CC main.c `pkg-config portaudio-2.0 --libs`

run: all
	./a.out
