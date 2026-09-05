#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_numeric(const void *a, const void *b) {
    long num_a = strtol(*(const char **)a, NULL, 10);
    long num_b = strtol(*(const char **)b, NULL, 10);
    if (num_a < num_b) return -1;
    if (num_a > num_b) return 1;
    return 0;
}

void sort_strings_numerically(char **strings, size_t count) {
    if (strings == NULL || count == 0) {
        return;
    }
    qsort(strings, count, sizeof(char *), compare_numeric);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <num1> <num2> ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t count = argc - 1;
    char **str_array = malloc(count * sizeof(char *));
    if (str_array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        str_array[i] = argv[i + 1];
    }

    sort_strings_numerically(str_array, count);

    for (size_t i = 0; i < count; ++i) {
        printf("%s\n", str_array[i]);
    }

    free(str_array);
    str_array = NULL;

    return EXIT_SUCCESS;
}