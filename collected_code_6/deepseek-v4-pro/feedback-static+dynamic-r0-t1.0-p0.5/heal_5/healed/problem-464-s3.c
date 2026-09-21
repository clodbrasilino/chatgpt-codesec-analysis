#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_KEY_LENGTH 64
#define MAX_VALUE_LENGTH 64
#define MAX_DICT_SIZE 100

typedef struct {
    char key[MAX_KEY_LENGTH];
    char value[MAX_VALUE_LENGTH];
} DictEntry;

typedef struct {
    DictEntry entries[MAX_DICT_SIZE];
    int size;
} Dictionary;

static bool safe_copy(char *dest, const char *src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return false;
    }
    
    size_t i;
    for (i = 0; i < dest_size - 1; i++) {
        if (src[i] == '\0') {
            break;
        }
    }
    
    if (i >= dest_size - 1 && src[i] != '\0') {
        return false;
    }
    
    size_t src_len = i;
    for (i = 0; i < src_len; i++) {
        dest[i] = src[i];
    }
    dest[src_len] = '\0';
    return true;
}

bool all_values_same(const Dictionary *dict) {
    if (dict == NULL || dict->size <= 0 || dict->size > MAX_DICT_SIZE) {
        return false;
    }

    const char *first_value = dict->entries[0].value;
    for (int i = 1; i < dict->size; i++) {
        size_t j;
        for (j = 0; j < MAX_VALUE_LENGTH; j++) {
            if (first_value[j] != dict->entries[i].value[j]) {
                return false;
            }
            if (first_value[j] == '\0') {
                break;
            }
        }
    }
    return true;
}

int main(void) {
    Dictionary dict;
    memset(&dict, 0, sizeof(dict));
    dict.size = 0;

    if (dict.size < MAX_DICT_SIZE) {
        if (safe_copy(dict.entries[dict.size].key, "a", MAX_KEY_LENGTH) &&
            safe_copy(dict.entries[dict.size].value, "same", MAX_VALUE_LENGTH)) {
            dict.size++;
        }
    }

    if (dict.size < MAX_DICT_SIZE) {
        if (safe_copy(dict.entries[dict.size].key, "b", MAX_KEY_LENGTH) &&
            safe_copy(dict.entries[dict.size].value, "same", MAX_VALUE_LENGTH)) {
            dict.size++;
        }
    }

    if (dict.size < MAX_DICT_SIZE) {
        if (safe_copy(dict.entries[dict.size].key, "c", MAX_KEY_LENGTH) &&
            safe_copy(dict.entries[dict.size].value, "same", MAX_VALUE_LENGTH)) {
            dict.size++;
        }
    }

    if (all_values_same(&dict)) {
        printf("All values are the same.\n");
    } else {
        printf("Values are not all the same.\n");
    }

    if (dict.size < MAX_DICT_SIZE) {
        if (safe_copy(dict.entries[dict.size].key, "d", MAX_KEY_LENGTH) &&
            safe_copy(dict.entries[dict.size].value, "different", MAX_VALUE_LENGTH)) {
            dict.size++;
        }
    }

    if (all_values_same(&dict)) {
        printf("All values are the same.\n");
    } else {
        printf("Values are not all the same.\n");
    }

    return 0;
}