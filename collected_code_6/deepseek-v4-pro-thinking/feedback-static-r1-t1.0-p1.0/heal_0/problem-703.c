#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *key;
    int value;
} dict_entry;

typedef struct {
    dict_entry *entries;
    size_t size;
    size_t capacity;
} dictionary;

bool dictionary_init(dictionary *dict, size_t capacity) {
    if (!dict || capacity == 0) {
        return false;
    }
    dict->entries = malloc(capacity * sizeof(*dict->entries));
    if (!dict->entries) {
        return false;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return true;
}

void dictionary_free(dictionary *dict) {
    if (!dict) {
        return;
    }
    for (size_t i = 0; i < dict->size; ++i) {
        free(dict->entries[i].key);
    }
    free(dict->entries);
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;
}

bool dictionary_add(dictionary *dict, const char *key, int value) {
    if (!dict || !key) {
        return false;
    }
    for (size_t i = 0; i < dict->size; ++i) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            dict->entries[i].value = value;
            return true;
        }
    }
    if (dict->size >= dict->capacity) {
        return false;
    }
    char *key_copy = malloc(strlen(key) + 1);
    if (!key_copy) {
        return false;
    }
    strcpy(key_copy, key);
    dict->entries[dict->size].key = key_copy;
    dict->entries[dict->size].value = value;
    ++dict->size;
    return true;
}

bool dictionary_contains(const dictionary *dict, const char *key) {
    if (!dict || !key) {
        return false;
    }
    for (size_t i = 0; i < dict->size; ++i) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            return true;
        }
    }
    return false;
}

int main(void) {
    dictionary dict;
    if (!dictionary_init(&dict, 10)) {
        return 1;
    }
    dictionary_add(&dict, "apple", 1);
    dictionary_add(&dict, "banana", 2);
    printf("%d\n", dictionary_contains(&dict, "apple"));
    printf("%d\n", dictionary_contains(&dict, "grape"));
    dictionary_free(&dict);
    return 0;
}