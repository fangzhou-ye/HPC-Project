# HPC_project
This is the course project of [HPC](https://cbouilla.github.io/HPC.html) at M1 Sorbonne University. Consisting of parallelizing a sparse matrix multiplication system **A\*x = y** with conjugate gradient method. The algorithm was derived from [Wiki page](https://en.wikipedia.org/wiki/Conjugate_gradient_method)

# Project structure
* **cg_seq:** 
containing the provided code of sequential solution

* **cg_mpi:**
optimized by MPI

* **cg_hybrid:**
optimized by MPI+OpenMP

# How to run and test
In each repository, using "make" command to compile the program. Testing matrix to be downloaded into somewhere and correct the "command_line" variable in runner.py to fit the path to the testing matrix. run \textmd{python runner.py}
Available matrix in https://hpc.fil.cool/matrix/
