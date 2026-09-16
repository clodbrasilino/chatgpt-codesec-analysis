#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    size_t count;
} Frequency;

int count_consecutive_frequencies(const int *numbers, size_t length,
                                  Frequency **result, size_t *result_length)
{
    Frequency *frequencies = NULL;
    size_t group_count = 0;
    size_t i = 0;

    if (numbers == NULL || result == NULL || result_length == NULL) {
        return -1;
    }

    *result = NULL;
    *result_length = 0;

    if (length == 0) {
        return 0;
    }

    frequencies = malloc(length * sizeof(Frequency));
    if (frequencies == NULL) {
        return -1;
    }

    frequencies[0].value = numbers[0];
    frequencies[0].count = 1;
    group_count = 1;

    for (i = 1; i < length; i++) {
        if (numbers[i] == frequencies[group_count - 1].value) {
            frequencies[group_count - 1].count++;
        } else {
            frequencies[group_count].value = numbers[i];
            frequencies[group_count].count = 1;
            group_count++;
        }
    }

    *result = frequencies;
    *result_length = group_count;

    return 0;
}

int main(void)
{
    int numbers[] = {1, 1, 2, 3, 3, 3, 4, 5, 5, 5, 5, 6};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    Frequency *frequencies = NULL;
    size_t frequency_count = 0;
    size_t i = 0;

    if (count_consecutive_frequencies(numbers, length,
                                      &frequencies, &frequency_count) != 0) {
        fprintf(stderr, "Failed to count frequencies\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < frequency_count; i++) {
        if (printf("Value %d appears %zu time(s) consecutively\n",
                   frequencies[i].value, frequencies[i].count) < 0) {
            free(frequencies);
            return EXIT_FAILURE;
        }
    }

    free(frequencies);
    frequencies = NULL;

    return EXIT_SUCCESS;
}