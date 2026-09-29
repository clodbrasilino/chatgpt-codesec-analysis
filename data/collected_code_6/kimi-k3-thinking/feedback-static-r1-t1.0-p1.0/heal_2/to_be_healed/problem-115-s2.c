#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ENTRIES 16
#define MAX_KEY_LEN 64
#define MAX_VALUE_LEN 128
#define NUM_DICTS 3

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry entries[MAX_ENTRIES];
    size_t size;
} Dict;

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t len = 0;

    if (s == NULL) {
        return 0;
    }
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

static char *bounded_strdup(const char *src, size_t max_len)
{
    size_t len;
    char *copy;

    if (src == NULL) {
        return NULL;
    }
    len = bounded_strlen(src, max_len);
    if (len >= max_len) {
        return NULL;
    }
    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, src, len);
    copy[len] = '\0';
    return copy;
}

void dict_init(Dict *dict)
{
    if (dict == NULL) {
        return;
    }
    dict->size = 0;
    memset(dict->entries, 0, sizeof(dict->entries));
}

void dict_free(Dict *dict)
{
    size_t i;

    if (dict == NULL) {
        return;
    }
    for (i = 0; i < dict->size; i++) {
        free(dict->entries[i].key);
        free(dict->entries[i].value);
        dict->entries[i].key = NULL;
        dict->entries[i].value = NULL;
    }
    dict->size = 0;
}

bool dict_insert(Dict *dict, const char *key, const char *value)
{
    char *key_copy;
    char *value_copy;

    if (dict == NULL || key == NULL || value == NULL) {
        return false;
    }
    if (dict->size >= MAX_ENTRIES) {
        return false;
    }
    key_copy = bounded_strdup(key, MAX_KEY_LEN);
    if (key_copy == NULL) {
        return false;
    }
    value_copy = bounded_strdup(value, MAX_VALUE_LEN);
    if (value_copy == NULL) {
        free(key_copy);
        return false;
    }
    dict->entries[dict->size].key = key_copy;
    dict->entries[dict->size].value = value_copy;
    dict->size++;
    return true;
}

bool dict_is_empty(const Dict *dict)
{
    if (dict == NULL) {
        return false;
    }
    return dict->size == 0;
}

bool all_dicts_empty(const Dict *dicts, size_t count)
{
    size_t i;

    if (count == 0) {
        return true;
    }
    if (dicts == NULL) {
        return false;
    }
    for (i = 0; i < count; i++) {
        if (!dict_is_empty(&dicts[i])) {
            return false;
        }
    }
    return true;
}

int main(void)
{
    Dict dicts[NUM_DICTS];
    size_t i;

    for (i = 0; i < NUM_DICTS; i++) {
        dict_init(&dicts[i]);
    }

    if (all_dicts_empty(dicts, NUM_DICTS)) {
        printf("All dictionaries are empty.\n");
    } else {
        printf("Not all dictionaries are empty.\n");
    }

    if (!dict_insert(&dicts[1], "name", "example")) {
        fprintf(stderr, "Error: failed to insert entry.\n");
        for (i = 0; i < NUM_DICTS; i++) {
            dict_free(&dicts[i]);
        }
        return EXIT_FAILURE;
    }

    if (all_dicts_empty(dicts, NUM_DICTS)) {
        printf("All dictionaries are empty.\n");
    } else {
        printf("Not all dictionaries are empty.\n");
    }

    for (i = 0; i < NUM_DICTS; i++) {
        dict_free(&dicts[i]);
    }

    return EXIT_SUCCESS;
}