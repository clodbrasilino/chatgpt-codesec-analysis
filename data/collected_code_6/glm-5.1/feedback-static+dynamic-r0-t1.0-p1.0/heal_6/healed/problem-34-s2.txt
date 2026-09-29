#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int find_missing(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }
    
    size_t low = 0;
    size_t high = size - 1;
    int base = arr[0];
    
    while (low <= high) {
        size_t mid = low + (high - low) / 2;
        
        if (arr[mid] == (int)mid + base) {
            low = mid + 1;
        } else {
            if (mid == 0) {
                break;
            }
            high = mid - 1;
        }
    }
    
    return (int)low + base;
}

int main(int argc, char * const * const argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <sorted_integers...>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    size_t size = (size_t)(argc - 1);
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < size; i++) {
        char *endptr;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (endptr == argv[i + 1] || *endptr != '\0' || errno == ERANGE || val > INT_MAX || val < INT_MIN) {
            fprintf(stderr, "Invalid or out of range integer: %s\n", argv[i + 1]);
            free(arr);
            return EXIT_FAILURE;
        }
        arr[i] = (int)val;
    }
    
    int missing = find_missing(arr, size);
    printf("%d\n", missing);
    
    free(arr);
    return EXIT_SUCCESS;
}