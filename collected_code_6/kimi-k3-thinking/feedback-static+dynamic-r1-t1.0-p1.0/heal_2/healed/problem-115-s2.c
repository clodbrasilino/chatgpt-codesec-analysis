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

static size_t safe_strnlen(const char *s, size_t maxlen)
{
    size_t len = 0;

    if (s == NULL) {
        return 0;
    }
    while (len < maxlen && s[len] != '\0') {
        len++;
    }
    return len;
}

void dict_init(Dict *dict)
{
    if (dict == NULL) {
        return;
    }
    dict->size = 0;
    memset(dict->entries, 0, sizeof(dict->entries));
}

bool dict_insert(Dict *dict, const char *key, const char *value)
{
    size_t key_len;
    size_t value_len;
    char *key_copy;
    char *value_copy;

    if (dict == NULL || key == NULL || value == NULL) {
        return false;
    }
    if (dict->size >= MAX_ENTRIES) {
        return false;
    }

    key_len = safe_strnlen(key, MAX_KEY_LEN);
    value_len = safe_strnlen(value, MAX_VALUE_LEN);

    if (key_len >= MAX_KEY_LEN || value_len >= MAX_VALUE_LEN) {
        return false;
    }

    key_copy = malloc(key_len + 1);
    if (key_copy == NULL) {
        return false;
    }

    value_copy = malloc(value_len + 1);
    if (value_copy == NULL) {
        free(key_copy);
        return false;
    }

    snprintf(key_copy, key_len + 1, "%s", key);
    snprintf(value_copy, value_len + 1, "%s", value);

    dict->entries[dict->size].key = key_copy;
    dict->entries[dict->size].value = value_copy;
    dict->size++;

    return true;
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