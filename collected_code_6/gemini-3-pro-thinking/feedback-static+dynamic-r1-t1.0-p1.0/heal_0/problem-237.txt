#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} ElementFreq;

int compare_ints(const void *a, const void *b);
int compare_freqs(const void *a, const void *b);
void check_similar_occurrences(const int *tuples, size_t size);

int compare_ints(const void *a, const void *b) {
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

int compare_freqs(const void *a, const void *b) {
    int count_a = ((const ElementFreq *)a)->count;
    int count_b = ((const ElementFreq *)b)->count;
    if (count_a < count_b) return -1;
    if (count_a > count_b) return 1;
    return 0;
}

void check_similar_occurrences(const int *tuples, size_t size) {
    if (tuples == NULL || size == 0) {
        return;
    }

    int *sorted_tuples = (int *)malloc(size * sizeof(int));
    if (sorted_tuples == NULL) {
        return;
    }

    for (size_t i = 0; i < size; i++) {
        sorted_tuples[i] = tuples[i];
    }

    qsort(sorted_tuples, size, sizeof(int), compare_ints);

    ElementFreq *freqs = (ElementFreq *)malloc(size * sizeof(ElementFreq));
    if (freqs == NULL) {
        free(sorted_tuples);
        return;
    }

    size_t unique_count = 0;
    freqs[0].value = sorted_tuples[0];
    freqs[0].count = 1;
    unique_count++;

    for (size_t i = 1; i < size; i++) {
        if (sorted_tuples[i] == sorted_tuples[i - 1]) {
            freqs[unique_count - 1].count++;
        } else {
            freqs[unique_count].value = sorted_tuples[i];
            freqs[unique_count].count = 1;
            unique_count++;
        }
    }

    qsort(freqs, unique_count, sizeof(ElementFreq), compare_freqs);

    size_t j = 0;
    while (j < unique_count) {
        size_t k = j;
        while (k < unique_count && freqs[k].count == freqs[j].count) {
            k++;
        }
        if ((k - j) > 1) {
            printf("%d: ", freqs[j].count);
            for (size_t m = j; m < k; m++) {
                printf("%d ", freqs[m].value);
            }
            printf("\n");
        }
        j = k;
    }

    free(freqs);
    free(sorted_tuples);
}

int main(void) {
    int records[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 6, 7, 7, 7, 7};
    size_t size = sizeof(records) / sizeof(records[0]);

    check_similar_occurrences(records, size);

    return 0;
}