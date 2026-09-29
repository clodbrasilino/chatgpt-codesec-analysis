#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int frequency;
} FrequencyMap;

typedef struct {
    int *data;
    size_t size;
} List;

void find_frequency(List *lists, size_t num_lists, FrequencyMap **freq_map, size_t *map_size) {
    if (!lists || num_lists == 0 || !freq_map || !map_size) {
        return;
    }

    size_t capacity = 10;
    *map_size = 0;
    *freq_map = (FrequencyMap *)malloc(capacity * sizeof(FrequencyMap));
    
    if (!*freq_map) {
        return;
    }

    for (size_t i = 0; i < num_lists; ++i) {
        if (!lists[i].data) {
            continue;
        }
        for (size_t j = 0; j < lists[i].size; ++j) {
            int current = lists[i].data[j];
            int found = 0;
            
            for (size_t k = 0; k < *map_size; ++k) {
                if ((*freq_map)[k].id == current) {
                    (*freq_map)[k].frequency++;
                    found = 1;
                    break;
                }
            }
            
            if (!found) {
                if (*map_size == capacity) {
                    capacity *= 2;
                    FrequencyMap *temp = (FrequencyMap *)realloc(*freq_map, capacity * sizeof(FrequencyMap));
                    if (!temp) {
                        free(*freq_map);
                        *freq_map = NULL;
                        *map_size = 0;
                        return;
                    }
                    *freq_map = temp;
                }
                (*freq_map)[*map_size].id = current;
                (*freq_map)[*map_size].frequency = 1;
                (*map_size)++;
            }
        }
    }
}

int main(void) {
    int data1[] = {1, 2, 3};
    int data2[] = {2, 3, 4, 2};
    int data3[] = {1, 5};

    List lists[3];
    lists[0].data = data1;
    lists[0].size = sizeof(data1) / sizeof(data1[0]);
    lists[1].data = data2;
    lists[1].size = sizeof(data2) / sizeof(data2[0]);
    lists[2].data = data3;
    lists[2].size = sizeof(data3) / sizeof(data3[0]);

    FrequencyMap *freq_map = NULL;
    size_t map_size = 0;

    find_frequency(lists, 3, &freq_map, &map_size);

    if (freq_map) {
        for (size_t i = 0; i < map_size; ++i) {
            printf("%d: %d\n", freq_map[i].id, freq_map[i].frequency);
        }
        free(freq_map);
    }

    return 0;
}