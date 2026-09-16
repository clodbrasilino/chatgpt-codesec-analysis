#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} Frequency;

void calculate_frequency(const int *list, size_t size, Frequency **freq_list, size_t *freq_size) {
    if (list == NULL || freq_list == NULL || freq_size == NULL || size == 0) {
        if (freq_size) *freq_size = 0;
        if (freq_list) *freq_list = NULL;
        return;
    }

    Frequency *temp_freq = malloc(size * sizeof(Frequency));
    if (temp_freq == NULL) {
        *freq_size = 0;
        *freq_list = NULL;
        return;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < size; ++i) {
        int found = 0;
        for (size_t j = 0; j < unique_count; ++j) {
            if (temp_freq[j].value == list[i]) {
                temp_freq[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            temp_freq[unique_count].value = list[i];
            temp_freq[unique_count].count = 1;
            unique_count++;
        }
    }

    Frequency *final_freq = realloc(temp_freq, unique_count * sizeof(Frequency));
    if (final_freq == NULL && unique_count > 0) {
        free(temp_freq);
        *freq_size = 0;
        *freq_list = NULL;
        return;
    }

    *freq_list = final_freq;
    *freq_size = unique_count;
}

int main(void) {
    int arr[] = {4, 2, 2, 8, 3, 3, 1, 4, 4};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    Frequency *freq_list = NULL;
    size_t freq_size = 0;

    calculate_frequency(arr, size, &freq_list, &freq_size);

    if (freq_list != NULL) {
        for (size_t i = 0; i < freq_size; ++i) {
            printf("Element: %d, Frequency: %d\n", freq_list[i].value, freq_list[i].count);
        }
        free(freq_list);
    } else {
        printf("Failed to calculate frequencies or list is empty.\n");
    }

    return 0;
}