#include <stdio.h>
#include <stdlib.h>

struct ElementFrequency {
    int element;
    int frequency;
};

struct ElementFrequency* get_frequencies(const int* list, size_t size, size_t* out_size) {
    if (list == NULL || out_size == NULL) {
        return NULL;
    }

    struct ElementFrequency* frequencies = malloc(size * sizeof(struct ElementFrequency));
    if (frequencies == NULL) {
        return NULL;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < size; ++i) {
        int current_element = list[i];
        int found = 0;

        for (size_t j = 0; j < unique_count; ++j) {
            if (frequencies[j].element == current_element) {
                frequencies[j].frequency++;
                found = 1;
                break;
            }
        }

        if (!found) {
            frequencies[unique_count].element = current_element;
            frequencies[unique_count].frequency = 1;
            unique_count++;
        }
    }

    *out_size = unique_count;

    if (unique_count > 0) {
        struct ElementFrequency* temp = realloc(frequencies, unique_count * sizeof(struct ElementFrequency));
        if (temp != NULL) {
            frequencies = temp;
        }
    }

    return frequencies;
}

int main(void) {
    int numbers[] = {1, 2, 2, 3, 1, 4, 2, 5, 3};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    size_t freq_size = 0;

    struct ElementFrequency* freqs = get_frequencies(numbers, size, &freq_size);

    if (freqs != NULL) {
        for (size_t i = 0; i < freq_size; ++i) {
            printf("%d: %d\n", freqs[i].element, freqs[i].frequency);
        }
        free(freqs);
    } else {
        printf("Failed to allocate memory or invalid input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}