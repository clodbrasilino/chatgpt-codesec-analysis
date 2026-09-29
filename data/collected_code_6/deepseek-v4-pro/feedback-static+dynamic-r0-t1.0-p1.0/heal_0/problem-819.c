#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 16

typedef struct {
    int *values;
    int *frequencies;
    int size;
    int capacity;
} FrequencyResult;

FrequencyResult count_consecutive_duplicates(int *numbers, int length) {
    FrequencyResult result;
    result.values = (int *)malloc(INITIAL_CAPACITY * sizeof(int));
    result.frequencies = (int *)malloc(INITIAL_CAPACITY * sizeof(int));
    result.size = 0;
    result.capacity = INITIAL_CAPACITY;

    if (result.values == NULL || result.frequencies == NULL) {
        if (result.values != NULL) free(result.values);
        if (result.frequencies != NULL) free(result.frequencies);
        result.values = NULL;
        result.frequencies = NULL;
        result.size = 0;
        result.capacity = 0;
        return result;
    }

    for (int i = 0; i < length; i++) {
        if (result.size == 0 || result.values[result.size - 1] != numbers[i]) {
            if (result.size == result.capacity) {
                int new_capacity = result.capacity * 2;
                int *new_values = (int *)realloc(result.values, new_capacity * sizeof(int));
                int *new_frequencies = (int *)realloc(result.frequencies, new_capacity * sizeof(int));

                if (new_values == NULL || new_frequencies == NULL) {
                    if (new_values != NULL) free(new_values);
                    if (new_frequencies != NULL) free(new_frequencies);
                    free(result.values);
                    free(result.frequencies);
                    result.values = NULL;
                    result.frequencies = NULL;
                    result.size = 0;
                    result.capacity = 0;
                    return result;
                }

                result.values = new_values;
                result.frequencies = new_frequencies;
                result.capacity = new_capacity;
            }

            result.values[result.size] = numbers[i];
            result.frequencies[result.size] = 1;
            result.size++;
        } else {
            result.frequencies[result.size - 1]++;
        }
    }

    return result;
}

void free_frequency_result(FrequencyResult *result) {
    if (result != NULL) {
        if (result->values != NULL) {
            free(result->values);
            result->values = NULL;
        }
        if (result->frequencies != NULL) {
            free(result->frequencies);
            result->frequencies = NULL;
        }
        result->size = 0;
        result->capacity = 0;
    }
}

int main(void) {
    int numbers[] = {1, 1, 2, 3, 3, 3, 4, 5, 5};
    int length = sizeof(numbers) / sizeof(numbers[0]);

    FrequencyResult result = count_consecutive_duplicates(numbers, length);

    if (result.values == NULL || result.frequencies == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_frequency_result(&result);
        return 1;
    }

    printf("Value\tFrequency\n");
    for (int i = 0; i < result.size; i++) {
        printf("%d\t%d\n", result.values[i], result.frequencies[i]);
    }

    free_frequency_result(&result);

    return 0;
}