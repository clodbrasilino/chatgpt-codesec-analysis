#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int dict_init(Dict *dict)
{
    dict->count = 0;
    dict->capacity = 4;
    dict->entries = malloc(dict->capacity * sizeof(Entry));
    if (dict->entries == NULL) {
        return -1;
    }
    return 0;
}

static Entry *dict_find(Dict *dict, const char *key)
{
    size_t i;
    for (i = 0; i < dict->count; i++) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            return &dict->entries[i];
        }
    }
    return NULL;
}

static int entry_add_value(Entry *entry, const char *value)
{
    char *copy;
    if (entry->count == entry->capacity) {
        size_t new_capacity = entry->capacity * 2;
        char **tmp = realloc(entry->values, new_capacity * sizeof(char *));
        if (tmp == NULL) {
            return -1;
        }
        entry->values = tmp;
        entry->capacity = new_capacity;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    copy = malloc(strlen(value) + 1);
    if (copy == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(copy, value);
    entry->values[entry->count] = copy;
    entry->count++;
    return 0;
}

static int dict_add(Dict *dict, const char *key, const char *value)
{
    Entry *entry = dict_find(dict, key);
    if (entry != NULL) {
        return entry_add_value(entry, value);
    }
    if (dict->count == dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        Entry *tmp = realloc(dict->entries, new_capacity * sizeof(Entry));
        if (tmp == NULL) {
            return -1;
        }
        dict->entries = tmp;
        dict->capacity = new_capacity;
    }
    entry = &dict->entries[dict->count];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    entry->key = malloc(strlen(key) + 1);
    if (entry->key == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(entry->key, key);
    entry->capacity = 4;
    entry->count = 0;
    entry->values = malloc(entry->capacity * sizeof(char *));
    if (entry->values == NULL) {
        free(entry->key);
        return -1;
    }
    if (entry_add_value(entry, value) != 0) {
        free(entry->values);
        free(entry->key);
        return -1;
    }
    dict->count++;
    return 0;
}

static void dict_free(Dict *dict)
{
    size_t i;
    size_t j;
    if (dict->entries == NULL) {
        return;
    }
    for (i = 0; i < dict->count; i++) {
        for (j = 0; j < dict->entries[i].count; j++) {
            free(dict->entries[i].values[j]);
        }
        free(dict->entries[i].values);
        free(dict->entries[i].key);
    }
    free(dict->entries);
    dict->entries = NULL;
    dict->count = 0;
    dict->capacity = 0;
}

static void dict_print(const Dict *dict)
{
    size_t i;
    size_t j;
    for (i = 0; i < dict->count; i++) {
        printf("%s: [", dict->entries[i].key);
        for (j = 0; j < dict->entries[i].count; j++) {
            printf("%s", dict->entries[i].values[j]);
            if (j + 1 < dict->entries[i].count) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

static int group_pairs(Dict *dict, const char *pairs[][2], size_t num_pairs)
{
    size_t i;
    for (i = 0; i < num_pairs; i++) {
        if (pairs[i][0] == NULL || pairs[i][1] == NULL) {
            return -1;
        }
        if (dict_add(dict, pairs[i][0], pairs[i][1]) != 0) {
            return -1;
        }
    }
    return 0;
}

int main(void)
{
    Dict dict;
    const char *pairs[][2] = {
        {"fruit", "apple"},
        {"vegetable", "carrot"},
        {"fruit", "banana"},
        {"fruit", "cherry"},
        {"vegetable", "potato"},
        {"grain", "rice"}
    };
    size_t num_pairs = sizeof(pairs) / sizeof(pairs[0]);

    if (dict_init(&dict) != 0) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }

    if (group_pairs(&dict, pairs, num_pairs) != 0) {
        fprintf(stderr, "Failed to group pairs\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    dict_print(&dict);
    dict_free(&dict);
    return EXIT_SUCCESS;
}