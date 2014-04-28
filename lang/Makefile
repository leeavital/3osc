SRC=parser.d scanner.d
SRC_MAIN=main.d
SRC_TEST=empty.d

LIB3OSC=../lib3osc.a



all: lib3osc
	dmd $(SRC) $(SRC_MAIN) $(LIB3OSC)


lib3osc: $(LIB3OSC)
	cd ../; cmake CMakeLists.txt; make


run: all
	./main


tests: make_test
	./empty

make_test:
	dmd $(SRC_TEST) $(SRC) -unittest



clean:
	rm -f *.o
