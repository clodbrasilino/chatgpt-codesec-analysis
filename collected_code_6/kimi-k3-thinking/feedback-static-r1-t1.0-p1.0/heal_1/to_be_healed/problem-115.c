#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_KEY_LEN 64
#define MAX_VALUE_LEN 128

typedef struct {
    char key[MAX_KEY_LEN];
    char value[MAX_VALUE_LEN];
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static bool dict_init(Dictionary *dict, size_t capacity)
{
    if (dict == NULL) {
        return false;
    }
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;
    if (capacity > 0) {
        dict->entries = calloc(capacity, sizeof(Entry));
        if (dict->entries == NULL) {
            return false;
        }
        dict->capacity = capacity;
    }
    return true;
}

static bool dict_put(Dictionary *dict, const char *key, const char *value)
{
    Entry *new_entries;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
     */
    size_t new_capacity;

    if (dict == NULL || key == NULL || value == NULL) {
        return false;
    }
    if (dict->size == dict->capacity) {
        new_capacity = (dict->capacity == 0) ? 4 : dict->capacity * 2;
        new_entries = realloc(dict->entries, new_capacity * sizeof(Entry));
        if (new_entries == NULL) {
            return false;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }
    snprintf(dict->entries[dict->size].key, MAX_KEY_LEN, "%s", key);
    snprintf(dict->entries[dict->size].value, MAX_VALUE_LEN, "%s", value);
    dict->size++;
    return true;
}

static bool dict_is_empty(const Dictionary *dict)
{
    return dict == NULL || dict->size == 0;
}

static void dict_free(Dictionary *dict)
{
    if (dict != NULL) {
        free(dict->entries);
        dict->entries = NULL;
        dict->size = 0;
        dict->capacity = 0;
    }
}

bool all_dicts_empty(const Dictionary *dicts, size_t count)
{
    size_t i;

    if (dicts == NULL) {
        return true;
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
    Dictionary dicts[3];
    size_t i;
    bool result;

    for (i = 0; i < 3; i++) {
        if (!dict_init(&dicts[i], 0)) {
            size_t j;
            for (j = 0; j < i; j++) {
                dict_free(&dicts[j]);
            }
            fprintf(stderr, "Failed to initialize dictionary %zu\n", i);
            return EXIT_FAILURE;
        }
    }

    result = all_dicts_empty(dicts, 3);
    printf("All dictionaries empty: %s\n", result ? "true" : "false");

    if (!dict_put(&dicts[1], "name", "Alice")) {
        fprintf(stderr, "Failed to add entry\n");
        for (i = 0; i < 3; i++) {
            dict_free(&dicts[i]);
        }
        return EXIT_FAILURE;
    }

    result = all_dicts_empty(dicts, 3);
    printf("All dictionaries empty: %s\n", result ? "true" : "false");

    for (i = 0; i < 3; i++) {
        dict_free(&dicts[i]);
    }

    return EXIT_SUCCESS;
}