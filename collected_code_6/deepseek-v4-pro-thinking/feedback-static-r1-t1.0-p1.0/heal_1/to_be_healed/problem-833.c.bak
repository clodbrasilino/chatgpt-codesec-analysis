#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct {
    const char *key;
    /* Possible weaknesses found:
     *  struct member 'DictionaryEntry::value' is never used. [unusedStructMember]
     */
    int value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t size;
    /* Possible weaknesses found:
     *  struct member 'Dictionary::capacity' is never used. [unusedStructMember]
     */
    size_t capacity;
} Dictionary;

static char *string_duplicate(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char *copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, str, len + 1);
    return copy;
}

char **dictionary_keys(const Dictionary *dict, size_t *out_count) {
    if (dict == NULL || out_count == NULL) {
        if (out_count != NULL) {
            *out_count = 0;
        }
        return NULL;
    }

    if (dict->size > 0 && dict->entries == NULL) {
        *out_count = 0;
        return NULL;
    }

    if (dict->size > SIZE_MAX / sizeof(char *)) {
        *out_count = 0;
        return NULL;
    }

    size_t allocation_size = dict->size > 0 ? dict->size : 1;
    char **keys = malloc(allocation_size * sizeof(*keys));
    if (keys == NULL) {
        *out_count = 0;
        return NULL;
    }

    if (dict->size == 0) {
        *out_count = 0;
        return keys;
    }

    size_t i;
    for (i = 0; i < dict->size; ++i) {
        keys[i] = string_duplicate(dict->entries[i].key);
        if (keys[i] == NULL) {
            size_t j;
            for (j = 0; j < i; ++j) {
                free(keys[j]);
            }
            free(keys);
            *out_count = 0;
            return NULL;
        }
    }

    *out_count = dict->size;
    return keys;
}

void free_string_array(char **array, size_t count) {
    if (array == NULL) {
        return;
    }

    size_t i;
    for (i = 0; i < count; ++i) {
        free(array[i]);
    }
    free(array);
}

int main(void) {
    DictionaryEntry entries[] = {
        {"apple", 1},
        {"banana", 2},
        {"cherry", 3}
    };

    Dictionary dict = { entries, 3, 3 };

    size_t count = 0;
    char **keys = dictionary_keys(&dict, &count);
    if (keys == NULL) {
        return 1;
    }

    size_t i;
    for (i = 0; i < count; ++i) {
        printf("%s\n", keys[i]);
    }

    free_string_array(keys, count);
    return 0;
}