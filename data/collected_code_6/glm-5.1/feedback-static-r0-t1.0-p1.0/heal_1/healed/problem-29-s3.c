#include <stdio.h>
#include <stdlib.h>

int find_odd_occurrence(const int *array, size_t size) {
    int result = 0;
    for (size_t i = 0; i < size; ++i) {
        result ^= array[i];
    }
    return result;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }

    size_t size = (size_t)(argc - 1);
    int *array = (int *)malloc(size * sizeof(int));
    if (array == NULL) {
        return 1;
    }

    for (size_t i = 0; i < size; ++i) {
        long val = strtol(argv[i + 1], NULL, 10);
        array[i] = (int)val;
    }

    int odd_occurrence = find_odd_occurrence(array, size);
    printf("%d\n", odd_occurrence);

    free(array);
    array = NULL;

    return 0;
}