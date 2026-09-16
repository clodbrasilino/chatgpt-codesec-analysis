#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} Frequency;

int getFrequencies(const int *list, size_t size, Frequency **result, size_t *resultSize)
{
    Frequency *freq;
    size_t uniqueCount;
    size_t i;
    size_t j;
    int found;

    if (list == NULL || result == NULL || resultSize == NULL || size == 0) {
        return -1;
    }

    freq = malloc(size * sizeof(Frequency));
    if (freq == NULL) {
        return -1;
    }

    uniqueCount = 0;

    for (i = 0; i < size; i++) {
        found = 0;
        for (j = 0; j < uniqueCount; j++) {
            if (freq[j].value == list[i]) {
                freq[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            freq[uniqueCount].value = list[i];
            freq[uniqueCount].count = 1;
            uniqueCount++;
        }
    }

    *result = freq;
    *resultSize = uniqueCount;
    return 0;
}

int main(void)
{
    int list[] = {4, 2, 4, 7, 2, 4, 9, 7, 1};
    size_t size = sizeof(list) / sizeof(list[0]);
    Frequency *frequencies = NULL;
    size_t freqSize = 0;
    size_t i;

    if (getFrequencies(list, size, &frequencies, &freqSize) != 0) {
        fprintf(stderr, "Failed to compute frequencies\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < freqSize; i++) {
        if (printf("Element %d occurs %d time(s)\n",
                   frequencies[i].value, frequencies[i].count) < 0) {
            free(frequencies);
            return EXIT_FAILURE;
        }
    }

    free(frequencies);
    return EXIT_SUCCESS;
}