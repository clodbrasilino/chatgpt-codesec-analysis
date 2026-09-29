#include <stdio.h>
#include <stdlib.h>

int find_product_of_non_repeated_elements(const int arr[], int n) {
    int product = 1;
    int found = 0;
    int i, j;
    
    if (n <= 0) {
        return 0;
    }
    
    for (i = 0; i < n; i++) {
        int count = 0;
        for (j = 0; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count == 1) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 31 * -2072745074 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000013,time:38204,execs:18041,op:havoc,rep:2)
             * UBSan: signed integer overflow: 6 * -558038585 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000010,time:32156,execs:15247,op:havoc,rep:7)
             */
            product *= arr[i];
            found = 1;
        }
    }
    
    if (!found) {
        return 0;
    }
    
    return product;
}

int main() {
    int n, i;
    int *arr;
    int result;
    
    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n <= 0) {
        fprintf(stderr, "Invalid array size\n");
        return EXIT_FAILURE;
    }
    
    arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter %d elements: ", n);
    for (i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }
    
    result = find_product_of_non_repeated_elements(arr, n);
    printf("Product of non-repeated elements: %d\n", result);
    
    free(arr);
    
    return EXIT_SUCCESS;
}