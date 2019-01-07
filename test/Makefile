.PHONY: all
all: clean
	gcc -o nmtest ./numatest.c  -lnmem

clean:
	rm -f *.o ./nmtest

.PHONY: run
run: all
	./nmtest 1
