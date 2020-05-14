# Add your choice of flags
CFLAGS = -O3 -Wall -Wextra -g
LDLIBS = -lm

all : cg_mpi

cg_mpi: cg_mpi.o mmio.o matrix.o
	mpicc -O3 cg_mpi.o mmio.o matrix.o -o cg_mpi

cg_mpi.o: cg_mpi.c
	mpicc -O3 -c cg_mpi.c -o cg_mpi.o

mmio.o: mmio.c
	gcc -O3 -c mmio.c -o mmio.o

matrix.o: matrix.c
	gcc -O3 -c matrix.c -o matrix.o

.PHONY: clean
clean:
	rm -rf *.o cg_mpi