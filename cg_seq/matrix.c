#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct csr_matrix_t {
	int n;			// dimension
	int nz;			// number of non-zero entries
	int *Ap;		// row pointers
	int *Aj;		// column indices
	double *Ax;		// actual coefficient
	int localh;
};
void display_double_array(double *arr, int n){
    for(int i=0; i<n; i++){
        printf("%f ", arr[i]);
    }
    printf("\n");
}
void display_int_array(int *arr, int n){
    for(int i=0; i<n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}
/*display csr_matrix structure*/
void display_csr(struct csr_matrix_t *A){
	printf("dimension: %d\n", A->n);
	printf("number of non-zero values: %d\n", A->nz);
	printf("v = ");
	display_double_array(A->Ax, A->nz);
	printf("col_ind = ");
	display_int_array(A->Aj, A->nz);
	printf("row_ind = ");
	display_int_array(A->Ap, A->localh+1);
}
/*integer division ceil*/
int roundup(int x, int y){
    return (x + (y - 1)) / y;
}
/* split int array from index i(inclusive) to index j(exclusive) */
int *split_int_array(int *arr, int i, int j){
    int size = j-i;
    int *res = (int *)malloc(sizeof(int)*size);
    memcpy(res, arr+i, sizeof(int)*size);
    return res;
}
/* split double array from index i(inclusive) to index j(exclusive) */
double *split_double_array(double *arr, int i, int j){
    int size = j-i;
    double *res = (double *)malloc(sizeof(double)*size);
    memcpy(res, arr+i, sizeof(double)*size);
    return res;
}
struct csr_matrix_t **split_csr(const struct csr_matrix_t *A, int p, int my_rank){
	struct csr_matrix_t **csrs = (struct csr_matrix_t **)malloc(sizeof(struct csr_matrix_t *)*p);
	int n = A->n;
	int localh = roundup(n, p);
	for(int i=0; i<p; i++){
		struct csr_matrix_t *csr = (struct csr_matrix_t *)malloc(sizeof(struct csr_matrix_t));
		int hh;
		if((i+1)*localh > n)
            hh = localh-1;
        else
            hh = localh;
		csr->localh = hh;
		csr->nz = A->Ap[i*localh+hh]-A->Ap[i*localh];
		csr->n = A->n;
		csr->Ax = split_double_array(A->Ax, A->Ap[i*localh], A->Ap[i*localh+hh]);
		csr->Aj = split_int_array(A->Aj, A->Ap[i*localh], A->Ap[i*localh+hh]);
		csr->Ap = split_int_array(A->Ap, i*localh, i*localh+hh+1);
		int length = hh+1;
		for(int j=0; j<length; j++){
			csr->Ap[j] -= A->Ap[i*localh];
		}
		csrs[i] = csr;
	}
	return csrs;
}
/*
void sp_gemv(const struct csr_matrix_t *A, const double *x, double *y)
{
	int n = A->n;
	int *Ap = A->Ap;
	int *Aj = A->Aj;
	double *Ax = A->Ax;
	for (int i = 0; i < A->localh; i++) {
		y[i] = 0;
		for (int u = Ap[i]; u < Ap[i + 1]; u++) {
			int j = Aj[u];
			double A_ij = Ax[u];
			y[i] += A_ij * x[j];
		}
	}
}
int main(){
    struct csr_matrix_t *mat = malloc(sizeof(struct csr_matrix_t));
	mat->n = 8;
	mat->nz = 11;
	int temp_Ap[] = {0, 1, 3, 5, 6, 7, 8, 9, 11};
	mat->Ap = temp_Ap;
	int temp_Aj[] = {3, 2, 5, 1, 7, 0, 4, 1, 7, 2, 6};
	mat->Aj = temp_Aj;
	double temp_Ax[] = {5.0, 2.0, 1.0, 2.0, 4.0, 5.0, 3.0, 1.0, 6.0, 4.0, 6.0};
	mat->Ax = temp_Ax;

	struct csr_matrix_t **csrs = split_csr(mat, 4);

	const double x[] = {2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0};
	for(int i=0; i<4; i++){
		struct csr_matrix_t *csr = csrs[i];
		double *y = (double *)malloc(sizeof(double)*csr->localh);
		sp_gemv(csr, x, y);
		display_double_array(y, csr->localh);
		printf("------------------------\n");
	}

    return 0;
}
*/