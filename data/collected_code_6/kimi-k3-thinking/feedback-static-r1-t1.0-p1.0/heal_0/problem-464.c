#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY ((size_t)8)

typedef struct {
    char *key;
    int value;
} Entry;

typedef struct {
    Entry *entries;
    size_t count;
    size_t capacity;
} Dictionary;

static bool dict_init(Dictionary *dict, size_t capacity)
{
    if (dict == NULL) {
        return false;
    }
    if (capacity == 0u) {
        capacity = INITIAL_CAPACITY;
    }
    dict->entries = malloc(capacity * sizeof(*dict->entries));
    if (dict->entries == NULL) {
        dict->count = 0u;
        dict->capacity = 0u;
        return false;
    }
    dict->count = 0u;
    dict->capacity = capacity;
    return true;
}

static bool dict_insert(Dictionary *dict, const char *key, int value)
{
    if (dict == NULL || key == NULL || dict->entries == NULL) {
        return false;
    }
    if (dict->count == dict->capacity) {
        if (dict->capacity > SIZE_MAX / 2u) {
            return false;
        }
        size_t new_capacity = dict->capacity * 2u;
        Entry *new_entries = realloc(dict->entries,
                                     new_capacity * sizeof(*new_entries));
        if (new_entries == NULL) {
            return false;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }
    size_t key_length = strlen(key) + 1u;
    char *key_copy = malloc(key_length);
    if (key_copy == NULL) {
        return false;
    }
    memcpy(key_copy, key, key_length);
    dict->entries[dict->count].key = key_copy;
    dict->entries[dict->count].value = value;
    dict->count++;
    return true;
}

static bool dict_all_values_same(const Dictionary *dict, bool *all_same)
{
    if (dict == NULL || all_same == NULL) {
        return false;
    }
    if (dict->count == 0u) {
        *all_same = true;
        return true;
    }
    if (dict->entries == NULL) {
        return false;
    }
    int first_value = dict->entries[0].value;
    for (size_t i = 1u; i < dict->count; i++) {
        if (dict->entries[i].value != first_value) {
            *all_same = false;
            return true;
        }
    }
    *all_same = true;
    return true;
}

static void dict_free(Dictionary *dict)
{
    if (dict == NULL) {
        return;
    }
    for (size_t i = 0u; i < dict->count; i++) {
        free(dict->entries[i].key);
        dict->entries[i].key = NULL;
    }
    free(dict->entries);
    dict->entries = NULL;
    dict->count = 0u;
    dict->capacity = 0u;
}

int main(void)
{
    Dictionary dict;
    if (!dict_init(&dict, INITIAL_CAPACITY)) {
        fprintf(stderr, "error: failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }

    bool ok = dict_insert(&dict, "alpha", 42) &&
              dict_insert(&dict, "beta", 42) &&
              dict_insert(&dict, "gamma", 42) &&
              dict_insert(&dict, "delta", 42);
    if (!ok) {
        fprintf(stderr, "error: failed to insert entry\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    bool all_same = false;
    if (!dict_all_values_same(&dict, &all_same)) {
        fprintf(stderr, "error: failed to inspect dictionary\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }
    printf("All values same: %s\n", all_same ? "true" : "false");

    if (!dict_insert(&dict, "epsilon", 7)) {
        fprintf(stderr, "error: failed to insert entry\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }
    if (!dict_all_values_same(&dict, &all_same)) {
        fprintf(stderr, "error: failed to inspect dictionary\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }
    printf("All values same: %s\n", all_same ? "true" : "false");

    dict_free(&dict);

    Dictionary empty_dict;
    if (!dict_init(&empty_dict, 0u)) {
        fprintf(stderr, "error: failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }
    if (!dict_all_values_same(&empty_dict, &all_same)) {
        fprintf(stderr, "error: failed to inspect dictionary\n");
        dict_free(&empty_dict);
        return EXIT_FAILURE;
    }
    printf("Empty dictionary all values same: %s\n",
           all_same ? "true" : "false");
    dict_free(&empty_dict);

    return EXIT_SUCCESS;
}