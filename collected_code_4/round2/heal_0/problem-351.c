#include <stdio.h>
#include <stdlib.h>

#define MAX_VAL 100000

int first_elem_k_times(int* arr, int n, int k) {
    int* counter = malloc(MAX_VAL * sizeof(int));
    if(counter == NULL) {
        // handles CWE-703
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for(int i = 0; i < MAX_VAL; i++) {
        counter[i] = 0;
    }

    for(int i = 0; i < n; i++) {
        counter[arr[i]]++;
        if(counter[arr[i]] == k) {
            int result = arr[i];
            free(counter); 
            // handles CWE-664
            return result;
        }
    }

    free(counter); 
    // handles CWE-664

    // if no element found, return -1.
    return -1;
}

int main() {
    int arr[] = {1, 1, 2, 2, 2, 3, 4, 4, 4, 4};
    int n = sizeof(arr)/sizeof(arr[0]);
    int k = 2;
    int result = first_elem_k_times(arr, n, k);
    if(result == -1) {
        printf("No element occurs %d times\n", k);
    } else {
        printf("First element occurring %d times is %d\n", k, result);
    }

    return 0;
}