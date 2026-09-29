#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *find_second_most_frequent(const char *const *sequence,
                                             size_t count)
{
    size_t *frequency = NULL;
    size_t i;
    size_t j;
    size_t highest = 0;
    size_t second_highest = 0;
    const char *result = NULL;

    if (sequence == NULL || count < 2U) {
        return NULL;
    }

    frequency = calloc(count, sizeof *frequency);
    if (frequency == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (sequence[i] == NULL) {
            free(frequency);
            return NULL;
        }
        frequency[i] = 1U;
        for (j = 0; j < i; j++) {
            if (strcmp(sequence[i], sequence[j]) == 0) {
                frequency[i] = 0U;
                frequency[j]++;
                break;
            }
        }
    }

    for (i = 0; i < count; i++) {
        if (frequency[i] > highest) {
            highest = frequency[i];
        }
    }

    for (i = 0; i < count; i++) {
        if (frequency[i] > second_highest && frequency[i] < highest) {
            second_highest = frequency[i];
            result = sequence[i];
        }
    }

    free(frequency);
    return result;
}

int main(void)
{
    const char *const sequence[] = {
        "apple", "banana", "apple", "orange",
        "banana", "apple", "orange", "grape"
    };
    const size_t count = sizeof sequence / sizeof sequence[0];
    const char *second;

    second = find_second_most_frequent(sequence, count);
    if (second == NULL) {
        if (fprintf(stderr, "No second most frequent string found.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Second most frequent string: %s\n", second) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}