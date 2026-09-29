#include <stdio.h>
#include <stdlib.h>

int find_odd_occurrence(const int *arr, size_t size) {
    if (size == 0) {
        return -1;
    }
    int result = 0;
    for (size_t i = 0; i < size; i++) {
        result ^= arr[i];
    }
    return result;
}

int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return 1;
    }
    size_t size = argc - 1;
    int *arr = malloc(size * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    for (size_t i = 0; i < size; i++) {
        arr[i] = atoi(argv[i + 1]);
    }
    int result = find_odd_occurrence(arr, size);
    printf("%d\n", result);
    free(arr);
    return 0;
}