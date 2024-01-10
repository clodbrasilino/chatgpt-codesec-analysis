#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(const int * const) a - *(const int * const) b);
}

int minSumOfAbsDiff(const int arr1[], const int arr2[], int n) {
    int *sortArr1 = malloc(n * sizeof(int));
    int *sortArr2 = malloc(n * sizeof(int));

    if(!sortArr1 || !sortArr2) {
        free(sortArr1);
        free(sortArr2);
        return -1;
    }

    for(int i = 0; i < n; i++){
        sortArr1[i] = arr1[i];
        sortArr2[i] = arr2[i];
    }

    qsort(sortArr1, n, sizeof(int), compare);
    qsort(sortArr2, n, sizeof(int), compare);

    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += abs(sortArr1[i] - sortArr2[i]);
    }

    free(sortArr1);
    free(sortArr2);

    return sum;
}

int main() {
    const int arr1[] = {1, 4, 8, 10};
    const int arr2[] = {2, 3, 6, 11};
    int n = sizeof(arr1) / sizeof(arr1[0]);

    int minSum = minSumOfAbsDiff(arr1, arr2, n);
    
    if(minSum != -1) {
        printf("Minimum sum of absolute differences: %d\n", minSum);   
    } else {
        printf("malloc failed\n");
    }

    return 0;
}