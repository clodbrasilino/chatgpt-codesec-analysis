#include <stdio.h>
#include <stdlib.h>

struct ElementFrequency {
    int element;
    int frequency;
};

struct ElementFrequency* get_frequencies(const int* arr, size_t size, size_t* out_freq_size) {
    if (arr == NULL || out_freq_size == NULL) {
        return NULL;
    }

    if (size == 0) {
        *out_freq_size = 0;
        return NULL;
    }

    struct ElementFrequency* frequencies = malloc(size * sizeof(struct ElementFrequency));
    if (frequencies == NULL) {
        return NULL;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < size; ++i) {
        int found = 0;
        for (size_t j = 0; j < unique_count; ++j) {
            if (frequencies[j].element == arr[i]) {
                frequencies[j].frequency++;
                found = 1;
                break;
            }
        }
        if (!found) {
            frequencies[unique_count].element = arr[i];
            frequencies[unique_count].frequency = 1;
            unique_count++;
        }
    }

    struct ElementFrequency* resized_frequencies = realloc(frequencies, unique_count * sizeof(struct ElementFrequency));
    if (resized_frequencies != NULL) {
        frequencies = resized_frequencies;
    }

    *out_freq_size = unique_count;
    return frequencies;
}

int main() {
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 1, 5, 2};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t freq_size = 0;

    struct ElementFrequency* freqs = get_frequencies(arr, size, &freq_size);

    if (freqs != NULL) {
        for (size_t i = 0; i < freq_size; ++i) {
            printf("Element: %d, Frequency: %d\n", freqs[i].element, freqs[i].frequency);
        }
        free(freqs);
    }

    return 0;
}