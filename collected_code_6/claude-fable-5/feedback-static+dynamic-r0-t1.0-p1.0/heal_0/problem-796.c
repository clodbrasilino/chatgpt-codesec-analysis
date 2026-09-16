#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t count;
    size_t capacity;
} Dict;

static Dict *dict_create(size_t capacity)
{
    Dict *dict = malloc(sizeof(Dict));
    if (dict == NULL) {
        return NULL;
    }
    dict->entries = malloc(capacity * sizeof(DictEntry));
    if (dict->entries == NULL) {
        free(dict);
        return NULL;
    }
    dict->count = 0;
    dict->capacity = capacity;
    return dict;
}

static int dict_add(Dict *dict, const char *key, int value)
{
    char *key_copy;
    size_t len;

    if (dict == NULL || key == NULL) {
        return -1;
    }
    if (dict->count >= dict->capacity) {
        return -1;
    }
    len = strlen(key) + 1;
    key_copy = malloc(len);
    if (key_copy == NULL) {
        return -1;
    }
    memcpy(key_copy, key, len);
    dict->entries[dict->count].key = key_copy;
    dict->entries[dict->count].value = value;
    dict->count++;
    return 0;
}

static void dict_destroy(Dict *dict)
{
    size_t i;

    if (dict == NULL) {
        return;
    }
    for (i = 0; i < dict->count; i++) {
        free(dict->entries[i].key);
    }
    free(dict->entries);
    free(dict);
}

static int dict_sum(const Dict *dict, long *result)
{
    size_t i;
    long sum = 0;

    if (dict == NULL || result == NULL) {
        return -1;
    }
    for (i = 0; i < dict->count; i++) {
        sum += (long)dict->entries[i].value;
    }
    *result = sum;
    return 0;
}

int main(void)
{
    Dict *dict;
    long total;

    dict = dict_create(10);
    if (dict == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    if (dict_add(dict, "apple", 100) != 0 ||
        dict_add(dict, "banana", 200) != 0 ||
        dict_add(dict, "cherry", 300) != 0) {
        fprintf(stderr, "Failed to add entries\n");
        dict_destroy(dict);
        return EXIT_FAILURE;
    }

    if (dict_sum(dict, &total) != 0) {
        fprintf(stderr, "Failed to compute sum\n");
        dict_destroy(dict);
        return EXIT_FAILURE;
    }

    printf("Sum of all items: %ld\n", total);

    dict_destroy(dict);
    return EXIT_SUCCESS;
}