#include <stdio.h>
#include <stddef.h>

#define DICT_CAPACITY 32

typedef struct {
    const char *key;
    int value;
} dict_entry_t;

typedef struct {
    dict_entry_t entries[DICT_CAPACITY];
    size_t size;
} dict_t;

const char *dict_get_key_at_index(const dict_t *dict, size_t index) {
    if (dict == NULL || index >= dict->size) {
        return NULL;
    }
    return dict->entries[index].key;
}

int dict_get_value_at_index(const dict_t *dict, size_t index, int *out_value) {
    if (dict == NULL || out_value == NULL || index >= dict->size) {
        return -1;
    }
    *out_value = dict->entries[index].value;
    return 0;
}

int main(void) {
    dict_t dict = {
        .entries = {
            {"alpha", 10},
            {"beta",  20},
            {"gamma", 30}
        },
        .size = 3
    };

    const char *key = dict_get_key_at_index(&dict, 1);
    if (key != NULL) {
        int value = 0;
        if (dict_get_value_at_index(&dict, 1, &value) == 0) {
            printf("%s %d\n", key, value);
        }
    }

    return 0;
}