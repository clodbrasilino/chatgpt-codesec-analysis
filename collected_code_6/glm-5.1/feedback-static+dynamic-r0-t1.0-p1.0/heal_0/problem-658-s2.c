#include <stdio.h>
#include <stdlib.h>

int find_max_occurrences(int *list, size_t size, int *max_item) {
    if (list == NULL || size == 0 || max_item == NULL) {
        return -1;
    }

    int current_value = list[0];
    size_t current_count = 1;
    int best_value = list[0];
    size_t best_count = 1;

    for (size_t i = 1; i < size; i++) {
        if (list[i] == current_value) {
            current_count++;
        } else {
            current_value = list[i];
            current_count = 1;
        }

        if (current_count > best_count) {
            best_value = current_value;
            best_count = current_count;
        }
    }

    *max_item = best_value;
    return 0;
}

int compare_int(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <integer1> <integer2> ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t size = (size_t)(argc - 1);
    int *list = (int *)malloc(size * sizeof(int));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        list[i] = atoi(argv[i + 1]);
    }

    qsort(list, size, sizeof(int), compare_int);

    int max_item;
    int result = find_max_occurrences(list, size, &max_item);

    if (result == 0) {
        printf("%d\n", max_item);
    }

    free(list);
    list = NULL;

    return EXIT_SUCCESS;
}