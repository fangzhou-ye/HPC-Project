#ifndef MATRIX_H
#define MATRIX_H

struct csr_matrix_t {
	int n;			// dimension
	int nz;			// number of non-zero entries
	int *Ap;		// row pointers
	int *Aj;		// column indices
	double *Ax;		// actual coefficient
	int localh;
};

void display_double_array(double *arr, int n);
void display_int_array(int *arr, int n);
void display_csr(struct csr_matrix_t *A);
int roundup(int x, int y);
int *split_int_array(int *arr, int i, int j);
double *split_double_array(double *arr, int i, int j);
struct csr_matrix_t **split_csr(const struct csr_matrix_t *A, int p);


#endif