#include <stdio.h>
#include <stdlib.h>

int *find_sum_even_odd(int *arr, int size) {
    int *result = malloc(2 * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    
    int first_even = 0;
    int first_odd = 0;
    int even_found = 0;
    int odd_found = 0;
    
    for (int i = 0; i < size; i++) {
        if (!even_found && arr[i] % 2 == 0) {
            first_even = arr[i];
            even_found = 1;
        }
        if (!odd_found && arr[i] % 2 != 0) {
            first_odd = arr[i];
            odd_found = 1;
        }
        if (even_found && odd_found) {
            break;
        }
    }
    
    if (!even_found || !odd_found) {
        free(result);
        return NULL;
    }
    
    result[0] = first_even + first_odd;
    result[1] = first_even;
    result[1] = first_odd;
    
    return result;
}

int main(void) {
    int arr[] = {5, 2, 8, 3, 6};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    int *result = find_sum_even_odd(arr, size);
    
    if (result == NULL) {
        printf("Could not find both even and odd numbers\n");
        return 1;
    }
    
    printf("First even: %d\n", result[0]);
    printf("First odd: %d\n", result[1]);
    printf("Sum: %d\n", result[0] + result[1]);
    
    free(result);
    return 0;
}