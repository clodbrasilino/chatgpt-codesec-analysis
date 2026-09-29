#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_KEY_LEN 64

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[MAX_KEY_LEN];
    int value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static size_t bounded_strnlen(const char *s, size_t max_len)
{
    size_t len = 0;

    while (len < max_len && s[len] != '\0') {
        len++;
    }

    return len;
}

Dictionary *dict_create(size_t capacity)
{
    Dictionary *dict;

    if (capacity == 0 || capacity > SIZE_MAX / sizeof(DictEntry)) {
        return NULL;
    }

    dict = malloc(sizeof(*dict));
    if (dict == NULL) {
        return NULL;
    }

    dict->entries = calloc(capacity, sizeof(*dict->entries));
    if (dict->entries == NULL) {
        free(dict);
        return NULL;
    }

    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

bool dict_add(Dictionary *dict, const char *key, int value)
{
    size_t key_len;
    int written;

    if (dict == NULL || key == NULL || dict->entries == NULL) {
        return false;
    }
    if (dict->size >= dict->capacity) {
        return false;
    }

    key_len = bounded_strnlen(key, MAX_KEY_LEN);
    if (key_len >= MAX_KEY_LEN) {
        return false;
    }

    written = snprintf(dict->entries[dict->size].key,
                       sizeof(dict->entries[dict->size].key),
                       "%s", key);
    if (written < 0 ||
        (size_t)written >= sizeof(dict->entries[dict->size].key)) {
        dict->entries[dict->size].key[0] = '\0';
        return false;
    }

    dict->entries[dict->size].value = value;
    dict->size++;
    return true;
}

bool dict_all_values_same(const Dictionary *dict, bool *result)
{
    int first_value;
    size_t i;

    if (dict == NULL || result == NULL ||
        dict->entries == NULL || dict->size == 0) {
        return false;
    }

    *result = true;
    first_value = dict->entries[0].value;

    for (i = 1; i < dict->size; i++) {
        if (dict->entries[i].value != first_value) {
            *result = false;
            break;
        }
    }

    return true;
}

void dict_destroy(Dictionary *dict)
{
    if (dict != NULL) {
        free(dict->entries);
        free(dict);
    }
}

int main(void)
{
    Dictionary *dict;
    bool all_same = false;
    char *long_key;

    dict = dict_create(4);
    if (dict == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    if (!dict_add(dict, "a", 5) ||
        !dict_add(dict, "b", 5) ||
        !dict_add(dict, "c", 5)) {
        fprintf(stderr, "Failed to add entries\n");
        dict_destroy(dict);
        return EXIT_FAILURE;
    }

    if (dict_all_values_same(dict, &all_same)) {
        printf("All values same: %s\n", all_same ? "true" : "false");
    } else {
        printf("Dictionary is empty or invalid\n");
    }

    dict_destroy(dict);
    dict = NULL;

    dict = dict_create(4);
    if (dict == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    if (!dict_add(dict, "x", 10) ||
        !dict_add(dict, "y", 20)) {
        fprintf(stderr, "Failed to add entries\n");
        dict_destroy(dict);
        return EXIT_FAILURE;
    }

    if (dict_all_values_same(dict, &all_same)) {
        printf("All values same: %s\n", all_same ? "true" : "false");
    } else {
        printf("Dictionary is empty or invalid\n");
    }

    long_key = malloc(MAX_KEY_LEN + 16);
    if (long_key == NULL) {
        fprintf(stderr, "Failed to allocate long key\n");
        dict_destroy(dict);
        return EXIT_FAILURE;
    }
    memset(long_key, 'k', MAX_KEY_LEN + 15);
    long_key[MAX_KEY_LEN + 15] = '\0';

    if (dict_add(dict, long_key, 99)) {
        printf("Overlong key accepted (unexpected)\n");
    } else {
        printf("Overlong key rejected (expected)\n");
    }

    free(long_key);
    long_key = NULL;

    if (!dict_add(dict, "z", 30) || !dict_add(dict, "w", 40)) {
        fprintf(stderr, "Failed to add entries\n");
        dict_destroy(dict);
        return EXIT_FAILURE;
    }

    if (dict_add(dict, "overflow", 50)) {
        printf("Add beyond capacity accepted (unexpected)\n");
    } else {
        printf("Add beyond capacity rejected (expected)\n");
    }

    dict_destroy(dict);
    dict = NULL;

    return EXIT_SUCCESS;
}