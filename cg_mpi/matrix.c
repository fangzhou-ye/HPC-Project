#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>
#include <err.h>

#define THRESHOLD 1e-8

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
	printf("localh = %d\n", A->localh);
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
// return thread i of p process the corresponding splited sparse matrix(csr)
struct csr_matrix_t *split_csr(const struct csr_matrix_t *A, int p, int i){
	int n = A->n;
	int localh = roundup(n, p);
	struct csr_matrix_t *csr = (struct csr_matrix_t *)malloc(sizeof(struct csr_matrix_t));
	int hh;
	if(i == p-1){
        hh =A->n-localh*(p-1);
    }else
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
	return csr;
}