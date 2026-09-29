#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void round_and_multiply(int *arr, int len) {
    int i;
    double sum = 0;
    for(i = 0; i < len; i++) {
        sum += round(arr[i]);
    }
    printf("Total is %.2f\n", sum*len);
}

int main() {
    int n, i;
    printf("Enter the size of the array \n");
    scanf("%d", &n);
    int *arr = (int *)malloc(n*sizeof(int));
    if(arr == NULL) {
        fprintf(stderr, "Memory not allocated.\n");
        exit(0);
    }
    printf("Now enter the elements of the array\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    round_and_multiply(arr, n);

    free(arr);

    return 0;
}