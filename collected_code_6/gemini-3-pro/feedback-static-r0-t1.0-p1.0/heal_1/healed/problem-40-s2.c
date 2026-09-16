#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} Frequency;

void free_frequencies(Frequency* freq_list) {
    if (freq_list != NULL) {
        free(freq_list);
    }
}

Frequency* find_frequencies(int** list_of_lists, int num_lists, const int* list_sizes, int* num_unique_elements) {
    if (list_of_lists == NULL || list_sizes == NULL || num_unique_elements == NULL) {
        return NULL;
    }

    int total_elements = 0;
    for (int i = 0; i < num_lists; i++) {
        total_elements += list_sizes[i];
    }

    if (total_elements == 0) {
        *num_unique_elements = 0;
        return NULL;
    }

    Frequency* freq_list = (Frequency*)malloc(total_elements * sizeof(Frequency));
    if (freq_list == NULL) {
        return NULL;
    }

    *num_unique_elements = 0;

    for (int i = 0; i < num_lists; i++) {
        if (list_of_lists[i] == NULL) {
            continue;
        }
        for (int j = 0; j < list_sizes[i]; j++) {
            int current_value = list_of_lists[i][j];
            int found = 0;

            for (int k = 0; k < *num_unique_elements; k++) {
                if (freq_list[k].value == current_value) {
                    freq_list[k].count++;
                    found = 1;
                    break;
                }
            }

            if (!found) {
                freq_list[*num_unique_elements].value = current_value;
                freq_list[*num_unique_elements].count = 1;
                (*num_unique_elements)++;
            }
        }
    }

    return freq_list;
}

int main(void) {
    int list1[] = {1, 2, 3};
    int list2[] = {2, 3, 4, 2};
    int list3[] = {5, 1};

    int* list_of_lists[] = {list1, list2, list3};
    int list_sizes[] = {3, 4, 2};
    int num_lists = 3;
    int num_unique_elements = 0;

    Frequency* freq_list = find_frequencies(list_of_lists, num_lists, list_sizes, &num_unique_elements);

    if (freq_list != NULL) {
        for (int i = 0; i < num_unique_elements; i++) {
            printf("Element: %d, Frequency: %d\n", freq_list[i].value, freq_list[i].count);
        }
        free_frequencies(freq_list);
    }

    return 0;
}