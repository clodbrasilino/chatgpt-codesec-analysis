#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} ElementFrequency;

typedef struct {
    ElementFrequency *frequencies;
    size_t size;
} FrequencyResult;

FrequencyResult countConsecutiveDuplicates(const int *list, size_t length) {
    FrequencyResult result = {NULL, 0};

    if (list == NULL || length == 0) {
        return result;
    }

    result.frequencies = (ElementFrequency *)malloc(length * sizeof(ElementFrequency));
    if (result.frequencies == NULL) {
        return result;
    }

    size_t resultIndex = 0;
    result.frequencies[resultIndex].value = list[0];
    result.frequencies[resultIndex].count = 1;

    for (size_t i = 1; i < length; i++) {
        if (list[i] == result.frequencies[resultIndex].value) {
            result.frequencies[resultIndex].count++;
        } else {
            resultIndex++;
            result.frequencies[resultIndex].value = list[i];
            result.frequencies[resultIndex].count = 1;
        }
    }

    result.size = resultIndex + 1;

    ElementFrequency *temp = (ElementFrequency *)realloc(result.frequencies, result.size * sizeof(ElementFrequency));
    if (temp != NULL) {
        result.frequencies = temp;
    }

    return result;
}

int main(void) {
    int arr[] = {1, 1, 1, 2, 3, 3, 4, 4, 4, 4, 1};
    size_t length = sizeof(arr) / sizeof(arr[0]);

    FrequencyResult result = countConsecutiveDuplicates(arr, length);

    if (result.frequencies != NULL) {
        for (size_t i = 0; i < result.size; i++) {
            printf("Value: %d, Count: %d\n", result.frequencies[i].value, result.frequencies[i].count);
        }
        free(result.frequencies);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    return 0;
}