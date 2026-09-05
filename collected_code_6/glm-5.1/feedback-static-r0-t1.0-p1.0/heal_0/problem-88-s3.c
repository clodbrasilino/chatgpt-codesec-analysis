#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int count;
} Frequency;

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

size_t get_frequencies(const int *list, size_t list_size, Frequency **freqs) {
    if (list == NULL || freqs == NULL) {
        return 0;
    }

    *freqs = NULL;
    if (list_size == 0) {
        return 0;
    }

    int *sorted = malloc(list_size * sizeof(int));
    if (sorted == NULL) {
        return 0;
    }

    for (size_t i = 0; i < list_size; i++) {
        sorted[i] = list[i];
    }

    qsort(sorted, list_size, sizeof(int), compare);

    size_t unique_count = 0;
    for (size_t i = 0; i < list_size; i++) {
        if (i == 0 || sorted[i] != sorted[i - 1]) {
            unique_count++;
        }
    }

    Frequency *result = malloc(unique_count * sizeof(Frequency));
    if (result == NULL) {
        free(sorted);
        return 0;
    }

    size_t res_idx = 0;
    for (size_t i = 0; i < list_size; i++) {
        if (i == 0 || sorted[i] != sorted[i - 1]) {
            result[res_idx].key = sorted[i];
            result[res_idx].count = 1;
            res_idx++;
        } else {
            result[res_idx - 1].count++;
        }
    }

    free(sorted);
    *freqs = result;
    return unique_count;
}

int main(void) {
    int list[] = {5, 2, 8, 2, 5, 5, 1, 8, 9, 2};
    size_t list_size = sizeof(list) / sizeof(list[0]);
    Frequency *freqs = NULL;

    size_t freq_size = get_frequencies(list, list_size, &freqs);

    for (size_t i = 0; i < freq_size; i++) {
        printf("%d: %d\n", freqs[i].key, freqs[i].count);
    }

    free(freqs);
    return 0;
}