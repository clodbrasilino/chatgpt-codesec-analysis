#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_KEY_LEN 64

typedef struct {
    char key[MAX_KEY_LEN];
    int value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dict;

Dict *dict_create(size_t capacity);
void dict_destroy(Dict *dict);
bool dict_add(Dict *dict, const char *key, int value);
bool all_values_same(const Dict *dict);

Dict *dict_create(size_t capacity)
{
    Dict *dict = NULL;

    if (capacity == 0) {
        return NULL;
    }

    dict = malloc(sizeof(Dict));
    if (dict == NULL) {
        return NULL;
    }

    dict->entries = malloc(capacity * sizeof(DictEntry));
    if (dict->entries == NULL) {
        free(dict);
        return NULL;
    }

    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

void dict_destroy(Dict *dict)
{
    if (dict != NULL) {
        free(dict->entries);
        dict->entries = NULL;
        free(dict);
    }
}

bool dict_add(Dict *dict, const char *key, int value)
{
    size_t key_len;

    if (dict == NULL || key == NULL) {
        return false;
    }

    if (dict->size >= dict->capacity) {
        return false;
    }

    key_len = strlen(key);
    if (key_len >= MAX_KEY_LEN) {
        return false;
    }

    memcpy(dict->entries[dict->size].key, key, key_len + 1);
    dict->entries[dict->size].value = value;
    dict->size++;
    return true;
}

bool all_values_same(const Dict *dict)
{
    size_t i;
    int first_value;

    if (dict == NULL || dict->size == 0) {
        return true;
    }

    first_value = dict->entries[0].value;
    for (i = 1; i < dict->size; i++) {
        if (dict->entries[i].value != first_value) {
            return false;
        }
    }
    return true;
}

int main(void)
{
    Dict *dict1 = NULL;
    Dict *dict2 = NULL;
    int status = EXIT_SUCCESS;

    dict1 = dict_create(10);
    if (dict1 == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    dict2 = dict_create(10);
    if (dict2 == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        dict_destroy(dict1);
        return EXIT_FAILURE;
    }

    if (!dict_add(dict1, "apple", 5) ||
        !dict_add(dict1, "banana", 5) ||
        !dict_add(dict1, "cherry", 5)) {
        fprintf(stderr, "Failed to add entries to dict1\n");
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (!dict_add(dict2, "apple", 5) ||
        !dict_add(dict2, "banana", 3) ||
        !dict_add(dict2, "cherry", 5)) {
        fprintf(stderr, "Failed to add entries to dict2\n");
        status = EXIT_FAILURE;
        goto cleanup;
    }

    printf("dict1 all values same: %s\n", all_values_same(dict1) ? "true" : "false");
    printf("dict2 all values same: %s\n", all_values_same(dict2) ? "true" : "false");

cleanup:
    dict_destroy(dict1);
    dict_destroy(dict2);
    return status;
}