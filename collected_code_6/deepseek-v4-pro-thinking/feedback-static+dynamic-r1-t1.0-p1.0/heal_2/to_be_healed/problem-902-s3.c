#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 8

typedef struct {
    char *key;
    int value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dict;

Dict *dict_create(void) {
    Dict *dict = malloc(sizeof(*dict));
    if (dict == NULL) {
        return NULL;
    }
    dict->entries = malloc(INITIAL_CAPACITY * sizeof(*dict->entries));
    if (dict->entries == NULL) {
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = INITIAL_CAPACITY;
    return dict;
}

static int dict_find_index(const Dict *dict, const char *key) {
    size_t i;
    for (i = 0; i < dict->size; ++i) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            return (int)i;
        }
    }
    return -1;
}

int dict_add(Dict *dict, const char *key, int value) {
    int index;
    if (dict == NULL || key == NULL) {
        return -1;
    }
    index = dict_find_index(dict, key);
    if (index >= 0) {
        dict->entries[index].value = value;
        return 0;
    }
    if (dict->size == dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        DictEntry *new_entries = realloc(dict->entries, new_capacity * sizeof(*new_entries));
        if (new_entries == NULL) {
            return -1;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }
    {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t key_length = strlen(key);
        char *key_copy = malloc(key_length + 1);
        if (key_copy == NULL) {
            return -1;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(key_copy, key, key_length + 1);
        dict->entries[dict->size].key = key_copy;
        dict->entries[dict->size].value = value;
        dict->size++;
    }
    return 0;
}

void dict_free(Dict *dict) {
    size_t i;
    if (dict == NULL) {
        return;
    }
    for (i = 0; i < dict->size; ++i) {
        free(dict->entries[i].key);
    }
    free(dict->entries);
    free(dict);
}

Dict *dict_combine(const Dict *a, const Dict *b) {
    Dict *result;
    size_t i;
    if (a == NULL || b == NULL) {
        return NULL;
    }
    result = dict_create();
    if (result == NULL) {
        return NULL;
    }
    for (i = 0; i < a->size; ++i) {
        if (dict_add(result, a->entries[i].key, a->entries[i].value) != 0) {
            dict_free(result);
            return NULL;
        }
    }
    for (i = 0; i < b->size; ++i) {
        int index = dict_find_index(result, b->entries[i].key);
        if (index >= 0) {
            result->entries[index].value += b->entries[i].value;
        } else {
            if (dict_add(result, b->entries[i].key, b->entries[i].value) != 0) {
                dict_free(result);
                return NULL;
            }
        }
    }
    return result;
}

int main(void) {
    Dict *a = dict_create();
    Dict *b = dict_create();
    Dict *combined = NULL;
    size_t i;

    if (a == NULL || b == NULL) {
        dict_free(a);
        dict_free(b);
        return 1;
    }

    if (dict_add(a, "apple", 3) != 0 ||
        dict_add(a, "banana", 2) != 0 ||
        dict_add(b, "apple", 5) != 0 ||
        dict_add(b, "cherry", 7) != 0) {
        dict_free(a);
        dict_free(b);
        return 1;
    }

    combined = dict_combine(a, b);
    if (combined == NULL) {
        dict_free(a);
        dict_free(b);
        return 1;
    }

    for (i = 0; i < combined->size; ++i) {
        printf("%s: %d\n", combined->entries[i].key, combined->entries[i].value);
    }

    dict_free(combined);
    dict_free(b);
    dict_free(a);
    return 0;
}