#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* list;
    size_t size;
} List;

typedef struct {
    int key;
    int count;
} Frequency;

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

Frequency* compute_frequency(List* lists, size_t num_lists, size_t* result_size) {
    size_t total_elements = 0;
    for (size_t i = 0; i < num_lists; ++i) {
        total_elements += lists[i].size;
    }

    if (total_elements == 0) {
        *result_size = 0;
        return NULL;
    }

    int* all_elements = (int*)malloc(total_elements * sizeof(int));
    if (!all_elements) {
        *result_size = 0;
        return NULL;
    }

    size_t offset = 0;
    for (size_t i = 0; i < num_lists; ++i) {
        for (size_t j = 0; j < lists[i].size; ++j) {
            all_elements[offset + j] = lists[i].list[j];
        }
        offset += lists[i].size;
    }

    qsort(all_elements, total_elements, sizeof(int), compare);

    Frequency* frequencies = (Frequency*)malloc(total_elements * sizeof(Frequency));
    if (!frequencies) {
        free(all_elements);
        *result_size = 0;
        return NULL;
    }

    size_t freq_count = 0;
    int current_value = all_elements[0];
    int current_count = 1;

    for (size_t i = 1; i < total_elements; ++i) {
        if (all_elements[i] == current_value) {
            current_count++;
        } else {
            frequencies[freq_count].key = current_value;
            frequencies[freq_count].count = current_count;
            freq_count++;
            current_value = all_elements[i];
            current_count = 1;
        }
    }

    frequencies[freq_count].key = current_value;
    frequencies[freq_count].count = current_count;
    freq_count++;

    *result_size = freq_count;
    free(all_elements);
    return frequencies;
}

int main() {
    List lists[] = {
        {{1, 2, 2, 3}, 4},
        {{2, 3, 3, 4}, 4},
        {{3, 4, 4, 5}, 4}
    };
    size_t num_lists = 3;
    size_t result_size;

    Frequency* frequencies = compute_frequency(lists, num_lists, &result_size);

    for (size_t i = 0; i < result_size; ++i) {
        printf("Value: %d, Count: %d\n", frequencies[i].key, frequencies[i].count);
    }

    free(frequencies);
    return 0;
}