#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static char *duplicate_string(const char *s) {
    if (s == NULL) {
        return NULL;
    }
    size_t length = strlen(s);
    char *copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, s, length + 1);
    return copy;
}

static void dictionary_init(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;
}

static void dictionary_free(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->size; ++i) {
        free(dict->entries[i].key);
        free(dict->entries[i].value);
    }
    free(dict->entries);
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;
}

static int dictionary_set(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return 0;
    }

    for (size_t i = 0; i < dict->size; ++i) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            char *new_value = duplicate_string(value);
            if (new_value == NULL) {
                return 0;
            }
            free(dict->entries[i].value);
            dict->entries[i].value = new_value;
            return 1;
        }
    }

    if (dict->size == dict->capacity) {
        size_t new_capacity = (dict->capacity == 0) ? 8 : dict->capacity * 2;
        Entry *new_entries = realloc(dict->entries, new_capacity * sizeof(Entry));
        if (new_entries == NULL) {
            return 0;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }

    char *key_copy = duplicate_string(key);
    if (key_copy == NULL) {
        return 0;
    }

    char *value_copy = duplicate_string(value);
    if (value_copy == NULL) {
        free(key_copy);
        return 0;
    }

    dict->entries[dict->size].key = key_copy;
    dict->entries[dict->size].value = value_copy;
    ++dict->size;
    return 1;
}

Dictionary *merge_dictionaries(const Dictionary *first, const Dictionary *second) {
    if (first == NULL || second == NULL) {
        return NULL;
    }

    Dictionary *merged = malloc(sizeof(Dictionary));
    if (merged == NULL) {
        return NULL;
    }

    dictionary_init(merged);

    for (size_t i = 0; i < first->size; ++i) {
        if (!dictionary_set(merged, first->entries[i].key, first->entries[i].value)) {
            dictionary_free(merged);
            free(merged);
            return NULL;
        }
    }

    for (size_t i = 0; i < second->size; ++i) {
        if (!dictionary_set(merged, second->entries[i].key, second->entries[i].value)) {
            dictionary_free(merged);
            free(merged);
            return NULL;
        }
    }

    return merged;
}

static void dictionary_print(const Dictionary *dict) {
    if (dict == NULL) {
        return;
    }

    for (size_t i = 0; i < dict->size; ++i) {
        printf("%s: %s\n", dict->entries[i].key, dict->entries[i].value);
    }
}

int main(void) {
    Dictionary first;
    Dictionary second;
    Dictionary *merged = NULL;
    int status = EXIT_SUCCESS;

    dictionary_init(&first);
    dictionary_init(&second);

    if (!dictionary_set(&first, "key1", "value1") ||
        !dictionary_set(&first, "key2", "value2") ||
        !dictionary_set(&second, "key2", "newvalue2") ||
        !dictionary_set(&second, "key3", "value3")) {
        status = EXIT_FAILURE;
    } else {
        merged = merge_dictionaries(&first, &second);
        if (merged == NULL) {
            status = EXIT_FAILURE;
        } else {
            dictionary_print(merged);
        }
    }

    if (merged != NULL) {
        dictionary_free(merged);
        free(merged);
    }

    dictionary_free(&first);
    dictionary_free(&second);

    return status;
}