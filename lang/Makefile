SRC=parser.d scanner.d
SRC_MAIN=main.d
SRC_TEST=empty.d
LIB3OSC=../lib3osc.a



all:
	dmd -ofmain $(SRC) $(SRC_MAIN) $(LIB3OSC)


run: all
	./main


tests: make_test
	./empty

make_test:
	dmd $(SRC_TEST) $(SRC) -unittest


clean:
	rm -f *.o
