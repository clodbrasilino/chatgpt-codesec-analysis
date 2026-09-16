#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    size_t count;
} Frequency;

static Frequency *get_frequencies(const int *list, size_t length, size_t *out_count)
{
    Frequency *result;
    size_t unique;
    size_t i;
    size_t j;

    if (list == NULL || out_count == NULL || length == 0) {
        return NULL;
    }

    result = malloc(length * sizeof(Frequency));
    if (result == NULL) {
        return NULL;
    }

    unique = 0;
    for (i = 0; i < length; i++) {
        int found = 0;
        for (j = 0; j < unique; j++) {
            if (result[j].value == list[i]) {
                result[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            result[unique].value = list[i];
            result[unique].count = 1;
            unique++;
        }
    }

    *out_count = unique;
    return result;
}

int main(void)
{
    int list[] = { 4, 2, 4, 7, 2, 4, 9, 7, 1 };
    size_t length = sizeof(list) / sizeof(list[0]);
    size_t unique_count = 0;
    Frequency *frequencies;
    size_t i;

    frequencies = get_frequencies(list, length, &unique_count);
    if (frequencies == NULL) {
        fprintf(stderr, "Failed to compute frequencies\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < unique_count; i++) {
        if (printf("%d: %zu\n", frequencies[i].value, frequencies[i].count) < 0) {
            free(frequencies);
            return EXIT_FAILURE;
        }
    }

    free(frequencies);
    return EXIT_SUCCESS;
}