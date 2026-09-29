#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16
#define MAX_KEY_LENGTH 1024

typedef struct {
    char *key;
    int value;
} Entry;

typedef struct {
    Entry *entries;
    size_t count;
    size_t capacity;
} Dictionary;

static size_t bounded_key_length(const char *key, size_t max_length)
{
    size_t length = 0;

    while (length < max_length && key[length] != '\0') {
        length++;
    }
    return length;
}

static int dictionary_init(Dictionary *dict)
{
    if (dict == NULL) {
        return 0;
    }
    dict->entries = malloc(INITIAL_CAPACITY * sizeof(Entry));
    if (dict->entries == NULL) {
        dict->count = 0;
        dict->capacity = 0;
        return 0;
    }
    dict->count = 0;
    dict->capacity = INITIAL_CAPACITY;
    return 1;
}

static int dictionary_contains(const Dictionary *dict, const char *key)
{
    if (dict == NULL || key == NULL || dict->entries == NULL) {
        return 0;
    }
    for (size_t i = 0; i < dict->count; i++) {
        if (dict->entries[i].key != NULL &&
            strcmp(dict->entries[i].key, key) == 0) {
            return 1;
        }
    }
    return 0;
}

static int dictionary_insert(Dictionary *dict, const char *key, int value)
{
    size_t key_len;
    char *key_copy;
    int written;

    if (dict == NULL || key == NULL) {
        return 0;
    }

    key_len = bounded_key_length(key, MAX_KEY_LENGTH);
    if (key_len == MAX_KEY_LENGTH) {
        return 0;
    }
    key_len += 1;

    if (dictionary_contains(dict, key)) {
        return 1;
    }

    if (dict->count == dict->capacity) {
        size_t new_capacity = (dict->capacity == 0) ? INITIAL_CAPACITY
                                                    : dict->capacity * 2;
        Entry *new_entries = realloc(dict->entries,
                                     new_capacity * sizeof(Entry));
        if (new_entries == NULL) {
            return 0;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }

    key_copy = malloc(key_len);
    if (key_copy == NULL) {
        return 0;
    }
    written = snprintf(key_copy, key_len, "%s", key);
    if (written < 0 || (size_t)written >= key_len) {
        free(key_copy);
        return 0;
    }

    dict->entries[dict->count].key = key_copy;
    dict->entries[dict->count].value = value;
    dict->count++;
    return 1;
}

static void dictionary_free(Dictionary *dict)
{
    if (dict == NULL) {
        return;
    }
    if (dict->entries != NULL) {
        for (size_t i = 0; i < dict->count; i++) {
            free(dict->entries[i].key);
            dict->entries[i].key = NULL;
        }
        free(dict->entries);
        dict->entries = NULL;
    }
    dict->count = 0;
    dict->capacity = 0;
}

int main(void)
{
    Dictionary dict;

    if (!dictionary_init(&dict)) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }

    if (!dictionary_insert(&dict, "apple", 1) ||
        !dictionary_insert(&dict, "banana", 2) ||
        !dictionary_insert(&dict, "cherry", 3)) {
        fprintf(stderr, "Failed to insert into dictionary\n");
        dictionary_free(&dict);
        return EXIT_FAILURE;
    }

    if (dictionary_contains(&dict, "banana")) {
        printf("Key 'banana' is present in the dictionary\n");
    } else {
        printf("Key 'banana' is not present in the dictionary\n");
    }

    if (dictionary_contains(&dict, "grape")) {
        printf("Key 'grape' is present in the dictionary\n");
    } else {
        printf("Key 'grape' is not present in the dictionary\n");
    }

    dictionary_free(&dict);
    return EXIT_SUCCESS;
}