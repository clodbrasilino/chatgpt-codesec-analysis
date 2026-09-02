#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} Frequency;

int find_index(const Frequency *freq, int size, int value) {
    for (int i = 0; i < size; i++) {
        if (freq[i].value == value) {
            return i;
        }
    }
    return -1;
}

Frequency* get_frequency(const int *list, int size, int *unique_count) {
    if (list == NULL || size <= 0 || unique_count == NULL) {
        return NULL;
    }

    Frequency *freq = (Frequency*)malloc(size * sizeof(Frequency));
    if (freq == NULL) {
        return NULL;
    }

    *unique_count = 0;

    for (int i = 0; i < size; i++) {
        int index = find_index(freq, *unique_count, list[i]);
        if (index != -1) {
            freq[index].count++;
        } else {
            freq[*unique_count].value = list[i];
            freq[*unique_count].count = 1;
            (*unique_count)++;
        }
    }

    Frequency *result = (Frequency*)malloc(*unique_count * sizeof(Frequency));
    if (result == NULL) {
        free(freq);
        return NULL;
    }

    for (int i = 0; i < *unique_count; i++) {
        result[i] = freq[i];
    }

    free(freq);
    return result;
}

int main() {
    int list[] = {1, 2, 3, 2, 1, 3, 3, 4, 5, 4};
    int size = sizeof(list) / sizeof(list[0]);
    int unique_count = 0;

    Frequency *freq = get_frequency(list, size, &unique_count);

    if (freq == NULL) {
        printf("Error: Failed to calculate frequencies\n");
        return 1;
    }

    for (int i = 0; i < unique_count; i++) {
        printf("Element %d occurs %d times\n", freq[i].value, freq[i].count);
    }

    free(freq);
    return 0;
}