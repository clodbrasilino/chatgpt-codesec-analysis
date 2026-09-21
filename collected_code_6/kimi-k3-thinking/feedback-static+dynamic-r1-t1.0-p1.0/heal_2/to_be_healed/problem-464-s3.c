#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    char *key;
    int value;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static char *copy_key(const char *src)
{
    size_t len;
    char *dst;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(src);
    if (len == SIZE_MAX) {
        return NULL;
    }
    dst = malloc(len + 1);
    if (dst == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dst, src, len + 1);
    return dst;
}

bool dict_init(Dictionary *dict, size_t capacity)
{
    if (dict == NULL || capacity == 0) {
        return false;
    }
    if (capacity > SIZE_MAX / sizeof(*dict->entries)) {
        return false;
    }
    dict->entries = calloc(capacity, sizeof(*dict->entries));
    if (dict->entries == NULL) {
        dict->size = 0;
        dict->capacity = 0;
        return false;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return true;
}

void dict_free(Dictionary *dict)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (dict != NULL) {
        if (dict->entries != NULL) {
            for (i = 0; i < dict->size; i++) {
                free(dict->entries[i].key);
                dict->entries[i].key = NULL;
            }
            free(dict->entries);
        }
        dict->entries = NULL;
        dict->size = 0;
        dict->capacity = 0;
    }
}

bool dict_add(Dictionary *dict, const char *key, int value)
{
    char *key_copy;

    if (dict == NULL || key == NULL || dict->entries == NULL ||
        dict->size >= dict->capacity) {
        return false;
    }
    key_copy = copy_key(key);
    if (key_copy == NULL) {
        return false;
    }
    dict->entries[dict->size].key = key_copy;
    dict->entries[dict->size].value = value;
    dict->size++;
    return true;
}

bool all_values_same(const Dictionary *dict, bool *result)
{
    size_t i;
    int first;

    if (dict == NULL || result == NULL ||
        (dict->size > 0 && dict->entries == NULL)) {
        return false;
    }
    if (dict->size == 0) {
        *result = true;
        return true;
    }
    first = dict->entries[0].value;
    for (i = 1; i < dict->size; i++) {
        if (dict->entries[i].value != first) {
            *result = false;
            return true;
        }
    }
    *result = true;
    return true;
}

int main(void)
{
    Dictionary dict;
    bool result;

    if (!dict_init(&dict, 8)) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }

    if (!dict_add(&dict, "alpha", 5) ||
        !dict_add(&dict, "beta", 5) ||
        !dict_add(&dict, "gamma", 5)) {
        fprintf(stderr, "Failed to add entries\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    if (!all_values_same(&dict, &result)) {
        fprintf(stderr, "Error checking values\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }
    printf("All values same: %s\n", result ? "true" : "false");

    if (!dict_add(&dict, "delta", 7)) {
        fprintf(stderr, "Failed to add entry\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    if (!all_values_same(&dict, &result)) {
        fprintf(stderr, "Error checking values\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }
    printf("All values same after adding delta: %s\n",
           result ? "true" : "false");

    dict_free(&dict);
    return EXIT_SUCCESS;
}