#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

void display_double_array(double *arr, int n){
    for(int i=0; i<n; i++){
        printf("%f ", arr[i]);
    }
    printf("\n");
}

int main(){
   double *dest = (double *)malloc(sizeof(double)*8);
   double source[] = {1.0, 2.0, 3.0};
   display_double_array(dest, 8);
   memcpy(dest, source, 3);
   display_double_array(dest, 8);
}