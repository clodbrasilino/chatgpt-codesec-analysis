#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_numeric(const void *a, const void *b) {
    return strcmp(*(char * const *)a, *(char * const *)b);
}

void sort_numeric_strings(char **arr, size_t n) {
    qsort(arr, n, sizeof(char *), compare_numeric);
}

int main() {
    char *numbers[] = {"30", "100", "9", "200", "25"};
    size_t count = 5;

    sort_numeric_strings(numbers, count);

    for (size_t i = 0; i < count; ++i) {
        printf("%s\n", numbers[i]);
    }

    for (size_t i = 0; i < count; ++i) {
        free(numbers[i]);
    }
    free(numbers);

    return 0;
}