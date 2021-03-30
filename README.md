# HPC Project
This is the course project of [HPC](https://cbouilla.github.io/HPC.html) at M1 Sorbonne University. Consisting of resolve a sparse matrix multiplication system **A\*x = y** with conjugate gradient method. The algorithm was derived from [Wiki page](https://en.wikipedia.org/wiki/Conjugate_gradient_method) and be parallelized with MPI and Open MP derivatives. Testing matrix are available in https://hpc.fil.cool/matrix/

# Project structure
* **cg_seq:** 
containing the provided code of sequential solution

* **cg_mpi:**
optimized by MPI

* **cg_hybrid:**
optimized by MPI+OpenMP

* **ToDo**:
Vectorization

# How to run and test
In each repository, using **make** command to compile the program. Testing matrix to be downloaded somewhere and correct the *command_line* variable in **runner.py** to fit the path to the testing matrix. Run **python runner.py** command to generate a receipt file and run **python check_receipt.py [receipt_file]** to check the solution and the preformance.
