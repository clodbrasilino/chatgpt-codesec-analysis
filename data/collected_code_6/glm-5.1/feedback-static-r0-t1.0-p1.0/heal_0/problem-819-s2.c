#include <stdio.h>
#include <stdlib.h>

struct Frequency {
    int value;
    int count;
};

struct Frequency* count_consecutive_duplicates(const int* arr, size_t size, size_t* result_size) {
    if (arr == NULL || result_size == NULL) {
        return NULL;
    }

    if (size == 0) {
        *result_size = 0;
        return NULL;
    }

    struct Frequency* result = malloc(size * sizeof(struct Frequency));
    if (result == NULL) {
        return NULL;
    }

    size_t idx = 0;
    result[idx].value = arr[0];
    result[idx].count = 1;

    for (size_t i = 1; i < size; ++i) {
        if (arr[i] == result[idx].value) {
            result[idx].count++;
        } else {
            idx++;
            result[idx].value = arr[i];
            result[idx].count = 1;
        }
    }

    *result_size = idx + 1;

    struct Frequency* temp = realloc(result, *result_size * sizeof(struct Frequency));
    if (temp != NULL) {
        result = temp;
    }

    return result;
}

int main(void) {
    int numbers[] = {1, 1, 1, 2, 2, 3, 4, 4, 4, 4, 5, 5, 1, 1};
    size_t num_count = sizeof(numbers) / sizeof(numbers[0]);
    size_t result_size = 0;

    struct Frequency* freqs = count_consecutive_duplicates(numbers, num_count, &result_size);

    if (freqs != NULL) {
        for (size_t i = 0; i < result_size; ++i) {
            printf("Value: %d, Count: %d\n", freqs[i].value, freqs[i].count);
        }
        free(freqs);
    }

    return 0;
}