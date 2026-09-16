#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int frequency;
} FrequencyMap;

int find_frequency(int **lists, int *list_sizes, int num_lists, FrequencyMap **out_map) {
    int total_elements = 0;
    for (int i = 0; i < num_lists; i++) {
        total_elements += list_sizes[i];
    }

    if (total_elements == 0) {
        *out_map = NULL;
        return 0;
    }

    int *temp = malloc(total_elements * sizeof(int));
    if (!temp) {
        *out_map = NULL;
        return -1;
    }

    int index = 0;
    for (int i = 0; i < num_lists; i++) {
        for (int j = 0; j < list_sizes[i]; j++) {
            temp[index++] = lists[i][j];
        }
    }

    for (int i = 0; i < total_elements - 1; i++) {
        for (int j = 0; j < total_elements - i - 1; j++) {
            if (temp[j] > temp[j + 1]) {
                int swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }

    FrequencyMap *map = malloc(total_elements * sizeof(FrequencyMap));
    if (!map) {
        free(temp);
        *out_map = NULL;
        return -1;
    }

    int unique_count = 0;
    int current_freq = 1;

    for (int i = 1; i < total_elements; i++) {
        if (temp[i] == temp[i - 1]) {
            current_freq++;
        } else {
            map[unique_count].value = temp[i - 1];
            map[unique_count].frequency = current_freq;
            unique_count++;
            current_freq = 1;
        }
    }
    map[unique_count].value = temp[total_elements - 1];
    map[unique_count].frequency = current_freq;
    unique_count++;

    free(temp);

    FrequencyMap *shrunk_map = realloc(map, unique_count * sizeof(FrequencyMap));
    if (shrunk_map) {
        map = shrunk_map;
    }

    *out_map = map;
    return unique_count;
}

int main() {
    int row1[] = {1, 2, 3, 2};
    int row2[] = {4, 2, 5, 5};
    int row3[] = {1, 5, 2};

    int num_lists = 3;
    int *lists[] = {row1, row2, row3};
    int list_sizes[] = {4, 4, 3};

    FrequencyMap *result_map = NULL;
    int map_size = find_frequency(lists, list_sizes, num_lists, &result_map);

    if (map_size < 0) {
        return 1;
    }

    for (int i = 0; i < map_size; i++) {
        printf("%d: %d\n", result_map[i].value, result_map[i].frequency);
    }

    free(result_map);
    result_map = NULL;

    return 0;
}