#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} Frequency;

int find_frequencies(const int *arr, size_t n, Frequency **result, size_t *result_count)
{
    Frequency *freq;
    size_t i;
    size_t j;
    size_t unique;

    if (arr == NULL || result == NULL || result_count == NULL || n == 0) {
        return -1;
    }

    freq = malloc(n * sizeof(Frequency));
    if (freq == NULL) {
        return -1;
    }

    unique = 0;
    for (i = 0; i < n; i++) {
        int found = 0;
        for (j = 0; j < unique; j++) {
            if (freq[j].value == arr[i]) {
                freq[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            freq[unique].value = arr[i];
            freq[unique].count = 1;
            unique++;
        }
    }

    *result = freq;
    *result_count = unique;
    return 0;
}

int main(void)
{
    int data[] = {4, 2, 4, 7, 2, 9, 4, 7, 1};
    size_t n = sizeof(data) / sizeof(data[0]);
    Frequency *freq = NULL;
    size_t freq_count = 0;
    size_t i;

    if (find_frequencies(data, n, &freq, &freq_count) != 0) {
        fprintf(stderr, "Failed to compute frequencies\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < freq_count; i++) {
        if (printf("%d occurs %d time(s)\n", freq[i].value, freq[i].count) < 0) {
            free(freq);
            return EXIT_FAILURE;
        }
    }

    free(freq);
    return EXIT_SUCCESS;
}