#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} Frequency;

int get_frequencies(const int *list, size_t size, Frequency **result, size_t *result_size)
{
    Frequency *freq;
    size_t unique_count = 0;
    size_t i;
    size_t j;

    if (list == NULL || result == NULL || result_size == NULL || size == 0) {
        return -1;
    }

    freq = malloc(size * sizeof(Frequency));
    if (freq == NULL) {
        return -1;
    }

    for (i = 0; i < size; i++) {
        int found = 0;
        for (j = 0; j < unique_count; j++) {
            if (freq[j].value == list[i]) {
                freq[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            freq[unique_count].value = list[i];
            freq[unique_count].count = 1;
            unique_count++;
        }
    }

    *result = freq;
    *result_size = unique_count;
    return 0;
}

int main(void)
{
    int list[] = {4, 2, 7, 2, 4, 4, 9, 7, 1};
    size_t size = sizeof(list) / sizeof(list[0]);
    Frequency *frequencies = NULL;
    size_t freq_size = 0;
    size_t i;

    if (get_frequencies(list, size, &frequencies, &freq_size) != 0) {
        fprintf(stderr, "Failed to compute frequencies\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < freq_size; i++) {
        if (printf("Element %d: %d\n", frequencies[i].value, frequencies[i].count) < 0) {
            free(frequencies);
            return EXIT_FAILURE;
        }
    }

    free(frequencies);
    return EXIT_SUCCESS;
}