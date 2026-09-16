#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_frequency_difference(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }
    
    int max_freq = 0;
    int min_freq = n;
    
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count > max_freq) {
            max_freq = count;
        }
        if (count < min_freq) {
            min_freq = count;
        }
    }
    
    return max_freq - min_freq;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n <= 0) {
        fprintf(stderr, "Invalid array size\n");
        return EXIT_FAILURE;
    }
    
    int *arr = (int *)malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }
    
    int result = find_frequency_difference(arr, n);
    if (result >= 0) {
        printf("%d\n", result);
    }
    
    free(arr);
    arr = NULL;
    
    return EXIT_SUCCESS;
}