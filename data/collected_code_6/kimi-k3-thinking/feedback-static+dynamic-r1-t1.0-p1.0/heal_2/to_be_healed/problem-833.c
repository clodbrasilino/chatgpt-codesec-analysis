#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static size_t safe_strnlen(const char *s, size_t max_len) {
    size_t len = 0;
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

static char *str_dup(const char *s) {
    size_t len;
    char *copy;

    if (s == NULL) {
        return NULL;
    }

    len = safe_strnlen(s, MAX_STRING_LENGTH);
    if (len == MAX_STRING_LENGTH) {
        return NULL;
    }

    copy = (char *)malloc(len + 1);
    if (copy != NULL) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, s, len);
        copy[len] = '\0';
    }
    return copy;
}

void dict_init(Dictionary *dict) {
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;
}

int dict_set(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }

    if (safe_strnlen(key, MAX_STRING_LENGTH) == MAX_STRING_LENGTH ||
        safe_strnlen(value, MAX_STRING_LENGTH) == MAX_STRING_LENGTH) {
        return -1;
    }

    for (size_t i = 0; i < dict->size; i++) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            char *new_value = str_dup(value);
            if (new_value == NULL) {
                return -1;
            }
            free(dict->entries[i].value);
            dict->entries[i].value = new_value;
            return 0;
        }
    }

    if (dict->size == dict->capacity) {
        size_t new_capacity = (dict->capacity == 0) ? 8 : dict->capacity * 2;
        DictEntry *new_entries;

        if (new_capacity < dict->capacity ||
            new_capacity > SIZE_MAX / sizeof(DictEntry)) {
            return -1;
        }

        new_entries = (DictEntry *)realloc(dict->entries,
                                           new_capacity * sizeof(DictEntry));
        if (new_entries == NULL) {
            return -1;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }

    char *new_key = str_dup(key);
    if (new_key == NULL) {
        return -1;
    }

    char *new_value = str_dup(value);
    if (new_value == NULL) {
        free(new_key);
        return -1;
    }

    dict->entries[dict->size].key = new_key;
    dict->entries[dict->size].value = new_value;
    dict->size++;
    return 0;
}

char **dict_keys(const Dictionary *dict, size_t *count) {
    char **keys;

    if (dict == NULL || count == NULL) {
        return NULL;
    }

    *count = dict->size;

    if (dict->size == 0) {
        return NULL;
    }

    if (dict->size > SIZE_MAX / sizeof(char *)) {
        *count = 0;
        return NULL;
    }

    keys = (char **)malloc(dict->size * sizeof(char *));
    if (keys == NULL) {
        *count = 0;
        return NULL;
    }

    for (size_t i = 0; i < dict->size; i++) {
        keys[i] = str_dup(dict->entries[i].key);
        if (keys[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(keys[j]);
            }
            free(keys);
            *count = 0;
            return NULL;
        }
    }

    return keys;
}

void keys_free(char **keys, size_t count) {
    if (keys == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(keys[i]);
    }
    free(keys);
}

void dict_free(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->entries[i].key);
        free(dict->entries[i].value);
    }
    free(dict->entries);
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;
}

int main(void) {
    Dictionary dict;
    dict_init(&dict);

    if (dict_set(&dict, "name", "Alice") != 0 ||
        dict_set(&dict, "age", "30") != 0 ||
        dict_set(&dict, "city", "New York") != 0) {
        fprintf(stderr, "Failed to add dictionary entries\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    size_t count = 0;
    char **keys = dict_keys(&dict, &count);

    if (keys == NULL && count != 0) {
        fprintf(stderr, "Failed to retrieve keys\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    printf("Dictionary keys:\n");
    for (size_t i = 0; i < count; i++) {
        printf("  %s\n", keys[i]);
    }

    keys_free(keys, count);
    dict_free(&dict);

    return EXIT_SUCCESS;
}