# Add your choice of flags
CFLAGS = -O3 -Wall -Wextra -g
LDLIBS = -lm

all : cg_hybrid

cg_hybrid: cg_hybrid.o mmio.o matrix.o
	mpicc -O3 -openmp cg_hybrid.o mmio.o matrix.o -o cg_hybrid

cg_hybrid.o: cg_hybrid.c
	mpicc -O3 -c -openmp cg_hybrid.c -o cg_hybrid.o

mmio.o: mmio.c
	gcc -O3 -c mmio.c -o mmio.o

matrix.o: matrix.c
	gcc -O3 -c matrix.c -o matrix.o

.PHONY: clean
clean:
	rm -rf *.o cg_hybrid