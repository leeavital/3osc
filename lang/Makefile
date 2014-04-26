SRC=$(wildcard *.d)

all:
	dmd $(SRC) -unittest

run: all
	./main


clean:
	rm -f *.o
