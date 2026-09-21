#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'SIZE_MAX' is defined in header '<stdint.h>'; this is probably fixable by adding '#include <stdint.h>'
  */

#define INITIAL_CAPACITY 16
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

static char *duplicate_string(const char *str)
{
    size_t len;
    size_t i;
    char *copy;

    if (str == NULL) {
        return NULL;
    }

    len = strnlen(str, MAX_STRING_LENGTH);
    if (len >= MAX_STRING_LENGTH) {
        return NULL;
    }

    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        copy[i] = str[i];
    }
    copy[len] = '\0';
    return copy;
}

int dict_init(Dictionary *dict)
{
    if (dict == NULL) {
        return -1;
    }
    dict->entries = malloc(INITIAL_CAPACITY * sizeof(DictEntry));
    if (dict->entries == NULL) {
        dict->size = 0;
        dict->capacity = 0;
        return -1;
    }
    dict->size = 0;
    dict->capacity = INITIAL_CAPACITY;
    return 0;
}

int dict_set(Dictionary *dict, const char *key, const char *value)
{
    size_t i;
    char *key_copy;
    char *value_copy;

    if (dict == NULL || dict->entries == NULL || key == NULL || value == NULL) {
        return -1;
    }

    for (i = 0; i < dict->size; i++) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            value_copy = duplicate_string(value);
            if (value_copy == NULL) {
                return -1;
            }
            free(dict->entries[i].value);
            dict->entries[i].value = value_copy;
            return 0;
        }
    }

    if (dict->size >= dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        DictEntry *new_entries;
        if (new_capacity < dict->capacity ||
            /* Possible weaknesses found:
             *  'SIZE_MAX' undeclared (first use in this function)
             *  each undeclared identifier is reported only once for each function it appears in
             *  use of undeclared identifier 'SIZE_MAX'
             */
            new_capacity > SIZE_MAX / sizeof(DictEntry)) {
            return -1;
        }
        new_entries = realloc(dict->entries, new_capacity * sizeof(DictEntry));
        if (new_entries == NULL) {
            return -1;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }

    key_copy = duplicate_string(key);
    if (key_copy == NULL) {
        return -1;
    }
    value_copy = duplicate_string(value);
    if (value_copy == NULL) {
        free(key_copy);
        return -1;
    }

    dict->entries[dict->size].key = key_copy;
    dict->entries[dict->size].value = value_copy;
    dict->size++;
    return 0;
}

char **dict_keys(const Dictionary *dict, size_t *count)
{
    char **keys;
    size_t i;
    size_t j;

    if (dict == NULL || count == NULL) {
        return NULL;
    }

    keys = malloc((dict->size + 1) * sizeof(char *));
    if (keys == NULL) {
        return NULL;
    }

    for (i = 0; i < dict->size; i++) {
        keys[i] = duplicate_string(dict->entries[i].key);
        if (keys[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(keys[j]);
            }
            free(keys);
            return NULL;
        }
    }
    keys[dict->size] = NULL;
    *count = dict->size;
    return keys;
}

void dict_keys_free(char **keys, size_t count)
{
    size_t i;

    if (keys == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(keys[i]);
    }
    free(keys);
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
    size_t count = 0;
    size_t i;
    char **keys;

    if (dict_init(&dict) != 0) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }

    if (dict_set(&dict, "name", "Alice") != 0 ||
        dict_set(&dict, "city", "Paris") != 0 ||
        dict_set(&dict, "language", "C") != 0 ||
        dict_set(&dict, "year", "2024") != 0) {
        fprintf(stderr, "Failed to add dictionary entry\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    keys = dict_keys(&dict, &count);
    if (keys == NULL) {
        fprintf(stderr, "Failed to retrieve keys\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    printf("Dictionary keys (%zu):\n", count);
    for (i = 0; i < count; i++) {
        printf("  %s\n", keys[i]);
    }

    dict_keys_free(keys, count);
    dict_free(&dict);

    return EXIT_SUCCESS;
}