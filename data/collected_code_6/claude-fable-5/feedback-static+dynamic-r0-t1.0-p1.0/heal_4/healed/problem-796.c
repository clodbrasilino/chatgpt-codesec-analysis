#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_KEY_LEN 256

typedef struct {
    char *key;
    int value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t count;
    size_t capacity;
} Dict;

static size_t safe_strnlen(const char *s, size_t maxlen)
{
    size_t i;

    for (i = 0; i < maxlen; i++) {
        if (s[i] == '\0') {
            break;
        }
    }
    return i;
}

static Dict *dict_create(size_t capacity)
{
    Dict *dict;

    if (capacity == 0 || capacity > SIZE_MAX / sizeof(DictEntry)) {
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
    dict->count = 0;
    dict->capacity = capacity;
    return dict;
}

static int dict_add(Dict *dict, const char *key, int value)
{
    char *key_copy;
    size_t len;
    size_t alloc_size;
    size_t i;

    if (dict == NULL || key == NULL) {
        return -1;
    }
    if (dict->count >= dict->capacity) {
        return -1;
    }
    len = safe_strnlen(key, MAX_KEY_LEN);
    if (len >= MAX_KEY_LEN) {
        return -1;
    }
    alloc_size = len + 1;
    key_copy = malloc(alloc_size);
    if (key_copy == NULL) {
        return -1;
    }
    for (i = 0; i < len; i++) {
        key_copy[i] = key[i];
    }
    key_copy[len] = '\0';
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
        dict->entries[i].key = NULL;
    }
    free(dict->entries);
    dict->entries = NULL;
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