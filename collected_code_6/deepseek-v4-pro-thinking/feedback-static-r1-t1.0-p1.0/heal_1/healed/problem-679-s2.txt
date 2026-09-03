#include <stdio.h>
#include <stddef.h>

#define DICT_CAPACITY 32
#define KEY_LENGTH 64

typedef struct {
    char key[KEY_LENGTH];
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

int main(void) {
    dict_t dict = {
        .entries = {
            {"alpha"},
            {"beta"},
            {"gamma"}
        },
        .size = 3
    };

    const char *key = dict_get_key_at_index(&dict, 1);
    if (key != NULL) {
        printf("%s\n", key);
    }

    return 0;
}