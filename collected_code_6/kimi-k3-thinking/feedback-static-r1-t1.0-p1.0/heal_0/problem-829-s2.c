#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *second_most_frequent(const char *arr[], size_t n)
{
    const char **unique;
    size_t *counts;
    size_t unique_count = 0;
    size_t i;
    size_t j;
    size_t max_count = 0;
    size_t second_count = 0;
    const char *max_str = NULL;
    const char *second_str = NULL;

    if (arr == NULL || n == 0) {
        return NULL;
    }

    unique = malloc(n * sizeof(*unique));
    counts = malloc(n * sizeof(*counts));
    if (unique == NULL || counts == NULL) {
        free(unique);
        free(counts);
        return NULL;
    }

    for (i = 0; i < n; i++) {
        int found = 0;
        if (arr[i] == NULL) {
            continue;
        }
        for (j = 0; j < unique_count; j++) {
            if (strcmp(unique[j], arr[i]) == 0) {
                counts[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            unique[unique_count] = arr[i];
            counts[unique_count] = 1;
            unique_count++;
        }
    }

    for (i = 0; i < unique_count; i++) {
        if (counts[i] > max_count) {
            second_count = max_count;
            second_str = max_str;
            max_count = counts[i];
            max_str = unique[i];
        } else if (counts[i] < max_count && counts[i] > second_count) {
            second_count = counts[i];
            second_str = unique[i];
        }
    }

    free(unique);
    free(counts);

    return second_str;
}

int main(void)
{
    const char *sequence[] = {
        "apple", "banana", "apple", "cherry",
        "banana", "apple", "cherry", "banana",
        "date", "cherry", "banana"
    };
    size_t n = sizeof(sequence) / sizeof(sequence[0]);
    const char *result = second_most_frequent(sequence, n);

    if (result != NULL) {
        printf("Second most frequent string: %s\n", result);
    } else {
        printf("No second most frequent string found.\n");
    }

    return 0;
}