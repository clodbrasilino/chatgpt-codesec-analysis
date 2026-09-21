#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int find_missing(const int *arr, size_t size) {
    if (arr == NULL) {
        return -1;
    }
    
    size_t low = 0;
    size_t high = size - 1;
    
    while (low <= high) {
        size_t mid = low + (high - low) / 2;
        
        if ((size_t)arr[mid] == mid + (size_t)arr[0]) {
            low = mid + 1;
        } else {
            if (mid == 0) {
                break;
            }
            high = mid - 1;
        }
    }
    
    return (int)(low + (size_t)arr[0]);
}

int main(int argc, char * const argv[]) {
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
        errno = 0;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (errno != 0 || endptr == argv[i + 1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            fprintf(stderr, "Invalid integer argument: %s\n", argv[i + 1]);
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