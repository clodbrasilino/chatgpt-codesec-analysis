#include <stdio.h>
#include <stdlib.h>

int sum_even_even(const int *arr, int size) {
    int sum = 0;
    int i;
    
    if (arr == NULL || size <= 0) {
        return 0;
    }
    
    for (i = 0; i < size; i += 2) {
        if (arr[i] % 2 == 0) {
            sum += arr[i];
        }
    }
    
    return sum;
}

int main(void) {
    int size;
    int *arr;
    int i;
    int result;
    
    printf("Enter number of elements: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    arr = (int *)malloc(sizeof(int) * size);
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter %d elements: ", size);
    for (i = 0; i < size; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(arr);
            return 1;
        }
    }
    
    result = sum_even_even(arr, size);
    printf("Sum of even numbers at even positions: %d\n", result);
    
    free(arr);
    return 0;
}