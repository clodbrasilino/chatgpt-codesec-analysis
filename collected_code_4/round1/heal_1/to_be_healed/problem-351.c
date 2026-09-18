#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

int firstElementKTimes(int *arr, int n, int k) {
    int count[MAX] = {0};

    for(int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  use of uninitialized value '*arr_24(D) + _2' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        count[arr[i]]++;
        if(count[arr[i]] == k) {
            return arr[i];
        }
    }

    return -1;
}

int main(void) {
    int n, k;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));
    
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }

    printf("Enter the elements in the array: \n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the occurrence count: ");
    scanf("%d", &k);

    int result = firstElementKTimes(arr, n, k);

    if(result != -1) {
        printf("The first element occurring %d times is %d.\n", k, result);
    } else {
        printf("No elements occur %d times in the given array.\n", k);
    }

    free(arr);

    return 0;
}