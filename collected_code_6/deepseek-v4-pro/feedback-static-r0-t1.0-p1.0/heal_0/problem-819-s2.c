#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} Frequency;

int count_frequency(const int *arr, int size, Frequency **result) {
    if (arr == NULL || size <= 0 || result == NULL) {
        return -1;
    }

    Frequency *freq = (Frequency *)malloc(sizeof(Frequency) * size);
    if (freq == NULL) {
        return -1;
    }

    int freq_count = 0;
    int i = 0;

    while (i < size) {
        int current = arr[i];
        int count = 1;

        while (i + count < size && arr[i + count] == current) {
            count++;
        }

        freq[freq_count].value = current;
        freq[freq_count].count = count;
        freq_count++;
        i += count;
    }

    Frequency *resized = (Frequency *)realloc(freq, sizeof(Frequency) * freq_count);
    if (resized == NULL && freq_count > 0) {
        free(freq);
        return -1;
    }

    *result = resized;
    return freq_count;
}

int main(void) {
    int arr[] = {1, 1, 2, 3, 3, 3, 4, 4, 4, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    Frequency *result = NULL;

    int count = count_frequency(arr, size, &result);
    if (count < 0) {
        printf("Error processing array\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("%d: %d\n", result[i].value, result[i].count);
    }

    free(result);
    return 0;
}