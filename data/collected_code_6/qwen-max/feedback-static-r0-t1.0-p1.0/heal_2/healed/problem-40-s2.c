#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} Frequency;

int compare(const void *a, const void *b) {
    return (*(const int *)a - *(const int *)b);
}

Frequency* find_frequencies(int** lists, int list_count, const int* list_sizes, int* frequency_count) {
    int total_elements = 0;
    for (int i = 0; i < list_count; ++i) {
        total_elements += list_sizes[i];
    }

    if (total_elements == 0) {
        *frequency_count = 0;
        return NULL;
    }

    int* all_elements = (int*)malloc(total_elements * sizeof(int));
    if (!all_elements) {
        *frequency_count = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < list_count; ++i) {
        for (int j = 0; j < list_sizes[i]; ++j) {
            all_elements[index++] = lists[i][j];
        }
    }

    qsort(all_elements, total_elements, sizeof(int), compare);

    Frequency* frequencies = (Frequency*)malloc((total_elements + 1) * sizeof(Frequency));
    if (!frequencies) {
        free(all_elements);
        *frequency_count = 0;
        return NULL;
    }

    int current_value = all_elements[0];
    int current_count = 1;
    *frequency_count = 0;

    for (int i = 1; i < total_elements; ++i) {
        if (all_elements[i] == current_value) {
            current_count++;
        } else {
            frequencies[*frequency_count].value = current_value;
            frequencies[*frequency_count].count = current_count;
            (*frequency_count)++;
            current_value = all_elements[i];
            current_count = 1;
        }
    }

    frequencies[*frequency_count].value = current_value;
    frequencies[*frequency_count].count = current_count;
    (*frequency_count)++;

    free(all_elements);
    return frequencies;
}

int main() {
    int lists_count = 3;
    const int list_sizes[] = {3, 2, 4};
    int lists[lists_count][5] = {
        {1, 2, 3, 0, 0},
        {2, 3, 0, 0, 0},
        {1, 2, 3, 4, 0}
    };

    int frequency_count = 0;
    Frequency* frequencies = find_frequencies((int**)lists, lists_count, list_sizes, &frequency_count);

    for (int i = 0; i < frequency_count; ++i) {
        printf("Value: %d, Count: %d\n", frequencies[i].value, frequencies[i].count);
    }

    free(frequencies);
    return 0;
}