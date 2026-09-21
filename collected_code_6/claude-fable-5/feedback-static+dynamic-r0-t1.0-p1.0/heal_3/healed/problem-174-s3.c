#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define INITIAL_CAPACITY 4
#define MAX_STRING_LENGTH 4096

typedef struct {
    char *key;
    char **values;
    size_t count;
    size_t capacity;
} Entry;

typedef struct {
    Entry *entries;
    size_t count;
    size_t capacity;
} Dict;

static size_t bounded_length(const char *src, size_t max_len)
{
    size_t len = 0U;

    while (len < max_len && src[len] != '\0') {
        len++;
    }
    return len;
}

static char *duplicate_string(const char *src)
{
    size_t len;
    size_t i;
    char *copy;

    if (src == NULL) {
        return NULL;
    }
    len = bounded_length(src, MAX_STRING_LENGTH);
    if (len >= MAX_STRING_LENGTH) {
        return NULL;
    }
    if (len >= SIZE_MAX - 1U) {
        return NULL;
    }
    copy = malloc(len + 1U);
    if (copy == NULL) {
        return NULL;
    }
    for (i = 0U; i < len; i++) {
        copy[i] = src[i];
    }
    copy[len] = '\0';
    return copy;
}

static int dict_init(Dict *dict)
{
    if (dict == NULL) {
        return -1;
    }
    dict->entries = malloc(INITIAL_CAPACITY * sizeof(Entry));
    if (dict->entries == NULL) {
        return -1;
    }
    dict->count = 0U;
    dict->capacity = INITIAL_CAPACITY;
    return 0;
}

static Entry *dict_find(Dict *dict, const char *key)
{
    size_t i;

    for (i = 0U; i < dict->count; i++) {
        if (dict->entries[i].key != NULL &&
            strncmp(dict->entries[i].key, key, MAX_STRING_LENGTH) == 0) {
            return &dict->entries[i];
        }
    }
    return NULL;
}

static int entry_add_value(Entry *entry, const char *value)
{
    char *copy;

    if (entry == NULL || value == NULL) {
        return -1;
    }
    if (entry->count == entry->capacity) {
        size_t new_capacity;
        char **new_values;

        if (entry->capacity > SIZE_MAX / 2U) {
            return -1;
        }
        new_capacity = entry->capacity * 2U;
        if (new_capacity > SIZE_MAX / sizeof(char *)) {
            return -1;
        }
        new_values = realloc(entry->values, new_capacity * sizeof(char *));
        if (new_values == NULL) {
            return -1;
        }
        entry->values = new_values;
        entry->capacity = new_capacity;
    }
    copy = duplicate_string(value);
    if (copy == NULL) {
        return -1;
    }
    entry->values[entry->count] = copy;
    entry->count++;
    return 0;
}

static int dict_add(Dict *dict, const char *key, const char *value)
{
    Entry *entry;

    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    entry = dict_find(dict, key);
    if (entry == NULL) {
        if (dict->count == dict->capacity) {
            size_t new_capacity;
            Entry *new_entries;

            if (dict->capacity > SIZE_MAX / 2U) {
                return -1;
            }
            new_capacity = dict->capacity * 2U;
            if (new_capacity > SIZE_MAX / sizeof(Entry)) {
                return -1;
            }
            new_entries = realloc(dict->entries, new_capacity * sizeof(Entry));
            if (new_entries == NULL) {
                return -1;
            }
            dict->entries = new_entries;
            dict->capacity = new_capacity;
        }
        entry = &dict->entries[dict->count];
        entry->key = duplicate_string(key);
        if (entry->key == NULL) {
            return -1;
        }
        entry->values = malloc(INITIAL_CAPACITY * sizeof(char *));
        if (entry->values == NULL) {
            free(entry->key);
            entry->key = NULL;
            return -1;
        }
        entry->count = 0U;
        entry->capacity = INITIAL_CAPACITY;
        dict->count++;
    }
    return entry_add_value(entry, value);
}

static void dict_free(Dict *dict)
{
    size_t i;
    size_t j;

    if (dict == NULL || dict->entries == NULL) {
        return;
    }
    for (i = 0U; i < dict->count; i++) {
        for (j = 0U; j < dict->entries[i].count; j++) {
            free(dict->entries[i].values[j]);
        }
        free(dict->entries[i].values);
        free(dict->entries[i].key);
    }
    free(dict->entries);
    dict->entries = NULL;
    dict->count = 0U;
    dict->capacity = 0U;
}

static void dict_print(const Dict *dict)
{
    size_t i;
    size_t j;

    if (dict == NULL) {
        return;
    }
    for (i = 0U; i < dict->count; i++) {
        printf("%s: [", dict->entries[i].key);
        for (j = 0U; j < dict->entries[i].count; j++) {
            printf("%s", dict->entries[i].values[j]);
            if (j + 1U < dict->entries[i].count) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

int main(void)
{
    Dict dict;
    size_t i;
    static const char *pairs[][2] = {
        {"fruit", "apple"},
        {"vegetable", "carrot"},
        {"fruit", "banana"},
        {"vegetable", "potato"},
        {"fruit", "cherry"},
        {"grain", "rice"}
    };
    size_t pair_count = sizeof(pairs) / sizeof(pairs[0]);

    if (dict_init(&dict) != 0) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < pair_count; i++) {
        if (dict_add(&dict, pairs[i][0], pairs[i][1]) != 0) {
            fprintf(stderr, "Failed to add pair (%s, %s)\n",
                    pairs[i][0], pairs[i][1]);
            dict_free(&dict);
            return EXIT_FAILURE;
        }
    }

    dict_print(&dict);
    dict_free(&dict);
    return EXIT_SUCCESS;
}