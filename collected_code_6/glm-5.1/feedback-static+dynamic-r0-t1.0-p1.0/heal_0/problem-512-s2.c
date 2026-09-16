#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { TUPLE_INT, TUPLE_LIST } TupleType;

typedef struct TupleElement {
    TupleType type;
    union {
        int int_val;
        struct {
            struct TupleElement *items;
            size_t count;
        } list_val;
    };
} TupleElement;

typedef struct FrequencyMap {
    int key;
    int count;
} FrequencyMap;

void count_recursive(TupleElement element, FrequencyMap **map, size_t *size, size_t *capacity) {
    if (element.type == TUPLE_INT) {
        for (size_t i = 0; i < *size; i++) {
            if ((*map)[i].key == element.int_val) {
                (*map)[i].count++;
                return;
            }
        }
        if (*size >= *capacity) {
            *capacity = (*capacity == 0) ? 8 : *capacity * 2;
            FrequencyMap *new_map = realloc(*map, *capacity * sizeof(FrequencyMap));
            if (!new_map) {
                exit(EXIT_FAILURE);
            }
            *map = new_map;
        }
        (*map)[*size].key = element.int_val;
        (*map)[*size].count = 1;
        (*size) += 1;
    } else if (element.type == TUPLE_LIST) {
        for (size_t i = 0; i < element.list_val.count; i++) {
            count_recursive(element.list_val.items[i], map, size, capacity);
        }
    }
}

FrequencyMap* count_element_frequency(TupleElement root, size_t *out_size) {
    FrequencyMap *map = NULL;
    size_t size = 0;
    size_t capacity = 0;

    count_recursive(root, &map, &size, &capacity);

    *out_size = size;
    return map;
}

void free_tuple(TupleElement element) {
    if (element.type == TUPLE_LIST) {
        for (size_t i = 0; i < element.list_val.count; i++) {
            free_tuple(element.list_val.items[i]);
        }
        free(element.list_val.items);
    }
}

int main(void) {
    TupleElement inner_items[3];
    inner_items[0].type = TUPLE_INT;
    inner_items[0].int_val = 5;
    inner_items[1].type = TUPLE_INT;
    inner_items[1].int_val = 3;
    inner_items[2].type = TUPLE_INT;
    inner_items[2].int_val = 5;

    TupleElement inner_list;
    inner_list.type = TUPLE_LIST;
    inner_list.list_val.items = inner_items;
    inner_list.list_val.count = 3;

    TupleElement root_items[4];
    root_items[0].type = TUPLE_INT;
    root_items[0].int_val = 1;
    root_items[1].type = TUPLE_INT;
    root_items[1].int_val = 2;
    root_items[2] = inner_list;
    root_items[3].type = TUPLE_INT;
    root_items[3].int_val = 1;

    TupleElement root;
    root.type = TUPLE_LIST;
    root.list_val.items = root_items;
    root.list_val.count = 4;

    size_t freq_size = 0;
    FrequencyMap *freq = count_element_frequency(root, &freq_size);

    for (size_t i = 0; i < freq_size; i++) {
        printf("%d: %d\n", freq[i].key, freq[i].count);
    }

    free(freq);
    free_tuple(root);

    return 0;
}