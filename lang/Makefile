SRC=parser.d scanner.d
SRC_MAIN=main.d
SRC_TEST=empty.d

all:
	dmd $(SRC) $(SRC_MAIN)

run: all
	./main


tests: make_test
	./empty

make_test:
	dmd $(SRC_TEST) $(SRC) -unittest



clean:
	rm -f *.o
