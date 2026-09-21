#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DICT_MAX_STRING_LEN 4096

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static size_t bounded_strlen(const char *s, size_t maxlen)
{
    const char *end;

    if (s == NULL) {
        return maxlen;
    }
    end = memchr(s, '\0', maxlen);
    if (end == NULL) {
        return maxlen;
    }
    return (size_t)(end - s);
}

static char *bounded_strdup(const char *s, size_t maxlen)
{
    size_t len;
    char *copy;

    len = bounded_strlen(s, maxlen);
    if (len >= maxlen) {
        return NULL;
    }

    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, s, len + 1);

    return copy;
}

static void dict_init(Dictionary *dict, size_t capacity)
{
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;

    if (capacity > 0) {
        dict->entries = calloc(capacity, sizeof(*dict->entries));
        if (dict->entries != NULL) {
            dict->capacity = capacity;
        }
    }
}

static int dict_add(Dictionary *dict, const char *key, const char *value)
{
    char *key_copy;
    char *value_copy;

    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    if (dict->entries == NULL || dict->size >= dict->capacity) {
        return -1;
    }

    key_copy = bounded_strdup(key, DICT_MAX_STRING_LEN);
    if (key_copy == NULL) {
        return -1;
    }

    value_copy = bounded_strdup(value, DICT_MAX_STRING_LEN);
    if (value_copy == NULL) {
        free(key_copy);
        return -1;
    }

    dict->entries[dict->size].key = key_copy;
    dict->entries[dict->size].value = value_copy;
    dict->size++;

    return 0;
}

static const char *dict_get_key_by_index(const Dictionary *dict, size_t index)
{
    if (dict == NULL || dict->entries == NULL || index >= dict->size) {
        return NULL;
    }
    return dict->entries[index].key;
}

static const char *dict_get_value_by_index(const Dictionary *dict, size_t index)
{
    if (dict == NULL || dict->entries == NULL || index >= dict->size) {
        return NULL;
    }
    return dict->entries[index].value;
}

static void dict_free(Dictionary *dict)
{
    if (dict == NULL) {
        return;
    }
    if (dict->entries != NULL) {
        for (size_t i = 0; i < dict->size; i++) {
            free(dict->entries[i].key);
            free(dict->entries[i].value);
        }
        free(dict->entries);
        dict->entries = NULL;
    }
    dict->size = 0;
    dict->capacity = 0;
}

int main(void)
{
    Dictionary dict;
    const char *key;

    dict_init(&dict, 4);

    if (dict_add(&dict, "name", "Alice") != 0 ||
        dict_add(&dict, "city", "Paris") != 0 ||
        dict_add(&dict, "lang", "C") != 0) {
        fprintf(stderr, "Error: failed to add dictionary entry\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < dict.size; i++) {
        const char *value;

        key = dict_get_key_by_index(&dict, i);
        value = dict_get_value_by_index(&dict, i);
        if (key != NULL && value != NULL) {
            printf("[%zu] %s = %s\n", i, key, value);
        }
    }

    key = dict_get_key_by_index(&dict, 10);
    if (key == NULL) {
        printf("Index 10 is out of range\n");
    }

    dict_free(&dict);

    return EXIT_SUCCESS;
}