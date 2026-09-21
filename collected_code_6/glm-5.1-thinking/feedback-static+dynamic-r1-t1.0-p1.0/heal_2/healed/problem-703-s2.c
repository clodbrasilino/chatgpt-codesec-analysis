#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Entry {
    char *key;
    int value;
    struct Entry *next;
} Entry;

typedef struct {
    Entry **buckets;
    size_t size;
} Dict;

unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = (unsigned char)*str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

Dict *dict_create(size_t size) {
    if (size == 0) return NULL;
    Dict *dict = malloc(sizeof(*dict));
    if (!dict) return NULL;
    dict->buckets = calloc(size, sizeof(*dict->buckets));
    if (!dict->buckets) {
        free(dict);
        return NULL;
    }
    dict->size = size;
    return dict;
}

void dict_destroy(Dict *dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->size; i++) {
        Entry *entry = dict->buckets[i];
        while (entry) {
            Entry *next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    free(dict->buckets);
    free(dict);
}

int dict_contains(Dict *dict, const char *key) {
    if (!dict || !key) return 0;
    size_t index = hash(key) % dict->size;
    Entry *entry = dict->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) return 1;
        entry = entry->next;
    }
    return 0;
}

void dict_insert(Dict *dict, const char *key, int value) {
    if (!dict || !key) return;
    size_t index = hash(key) % dict->size;
    Entry *entry = dict->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value;
            return;
        }
        entry = entry->next;
    }
    Entry *new_entry = malloc(sizeof(*new_entry));
    if (!new_entry) return;
    size_t key_len = strnlen(key, SIZE_MAX);
    if (key_len == SIZE_MAX) {
        free(new_entry);
        return;
    }
    new_entry->key = malloc(key_len + 1);
    if (!new_entry->key) {
        free(new_entry);
        return;
    }
    memcpy(new_entry->key, key, key_len + 1);
    new_entry->value = value;
    new_entry->next = dict->buckets[index];
    dict->buckets[index] = new_entry;
}

int main(void) {
    Dict *dict = dict_create(16);
    if (!dict) return EXIT_FAILURE;

    dict_insert(dict, "apple", 1);
    dict_insert(dict, "banana", 2);
    dict_insert(dict, "cherry", 3);

    printf("Contains 'apple': %d\n", dict_contains(dict, "apple"));
    printf("Contains 'grape': %d\n", dict_contains(dict, "grape"));
    printf("Contains NULL: %d\n", dict_contains(dict, NULL));

    dict_destroy(dict);
    return EXIT_SUCCESS;
}