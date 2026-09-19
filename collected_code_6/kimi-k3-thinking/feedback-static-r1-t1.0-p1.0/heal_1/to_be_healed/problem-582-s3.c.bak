#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static char *dict_copy_string(const char *src)
{
    size_t len;
    char *dest;

    if (src == NULL) {
        return NULL;
    }
    len = strlen(src);
    dest = malloc(len + 1);
    if (dest == NULL) {
        return NULL;
    }
    memcpy(dest, src, len + 1);
    return dest;
}

bool dict_init(Dictionary *dict, size_t capacity)
{
    if (dict == NULL) {
        return false;
    }
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;
    if (capacity > 0) {
        if (capacity > SIZE_MAX / sizeof(DictEntry)) {
            return false;
        }
        dict->entries = calloc(capacity, sizeof(DictEntry));
        if (dict->entries == NULL) {
            return false;
        }
        dict->capacity = capacity;
    }
    return true;
}

bool dict_is_empty(const Dictionary *dict)
{
    if (dict == NULL) {
        return true;
    }
    return dict->size == 0;
}

bool dict_set(Dictionary *dict, const char *key, const char *value)
{
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
     */
    size_t new_capacity;
    DictEntry *new_entries;
    char *new_key;
    char *new_value;

    if (dict == NULL || key == NULL || value == NULL) {
        return false;
    }

    for (i = 0; i < dict->size; i++) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            new_value = dict_copy_string(value);
            if (new_value == NULL) {
                return false;
            }
            free(dict->entries[i].value);
            dict->entries[i].value = new_value;
            return true;
        }
    }

    if (dict->size == dict->capacity) {
        new_capacity = (dict->capacity == 0) ? 4 : dict->capacity * 2;
        if (new_capacity < dict->capacity ||
            new_capacity > SIZE_MAX / sizeof(DictEntry)) {
            return false;
        }
        new_entries = realloc(dict->entries, new_capacity * sizeof(DictEntry));
        if (new_entries == NULL) {
            return false;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }

    new_key = dict_copy_string(key);
    if (new_key == NULL) {
        return false;
    }
    new_value = dict_copy_string(value);
    if (new_value == NULL) {
        free(new_key);
        return false;
    }

    dict->entries[dict->size].key = new_key;
    dict->entries[dict->size].value = new_value;
    dict->size++;
    return true;
}

void dict_free(Dictionary *dict)
{
    size_t i;

    if (dict == NULL) {
        return;
    }
    for (i = 0; i < dict->size; i++) {
        free(dict->entries[i].key);
        free(dict->entries[i].value);
    }
    free(dict->entries);
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;
}

int main(void)
{
    Dictionary dict;

    if (!dict_init(&dict, 0)) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }

    printf("Dictionary is %s\n", dict_is_empty(&dict) ? "empty" : "not empty");

    if (!dict_set(&dict, "language", "C")) {
        fprintf(stderr, "Failed to insert entry\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    printf("Dictionary is %s\n", dict_is_empty(&dict) ? "empty" : "not empty");

    dict_free(&dict);
    return EXIT_SUCCESS;
}