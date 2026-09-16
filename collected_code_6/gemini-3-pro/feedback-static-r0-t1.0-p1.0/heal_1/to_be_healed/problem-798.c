#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
long long int sum_array(int *arr, size_t size) {
    long long int sum = 0;
    
    if (arr == NULL) {
        return 0;
    }

    for (size_t i = 0; i < size; i++) {
        sum += arr[i];
    }
    
    return sum;
}

int main(void) {
    size_t size = 5;
    int *arr = (int *)malloc(size * sizeof(int));
    
    if (arr == NULL) {
        return EXIT_FAILURE;
    }
    
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    arr[3] = 40;
    arr[4] = 50;
    
    long long int total_sum = sum_array(arr, size);
    
    printf("Sum: %lld\n", total_sum);
    
    free(arr);
    arr = NULL;
    
    return EXIT_SUCCESS;
}