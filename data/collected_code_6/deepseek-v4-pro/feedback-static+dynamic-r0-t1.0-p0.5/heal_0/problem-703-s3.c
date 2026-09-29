#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Entry {
    char *key;
    int value;
    struct Entry *next;
} Entry;

typedef struct Dictionary {
    Entry **buckets;
    size_t size;
} Dictionary;

unsigned long hash(const char *str, size_t size) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % size;
}

Dictionary *create_dictionary(size_t size) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->size = size;
    dict->buckets = calloc(size, sizeof(Entry *));
    if (!dict->buckets) {
        free(dict);
        return NULL;
    }
    return dict;
}

void dictionary_insert(Dictionary *dict, const char *key, int value) {
    if (!dict || !key) return;
    unsigned long index = hash(key, dict->size);
    Entry *entry = malloc(sizeof(Entry));
    if (!entry) return;
    entry->key = malloc(strlen(key) + 1);
    if (!entry->key) {
        free(entry);
        return;
    }
    strcpy(entry->key, key);
    entry->value = value;
    entry->next = dict->buckets[index];
    dict->buckets[index] = entry;
}

int dictionary_contains(Dictionary *dict, const char *key) {
    if (!dict || !key) return 0;
    unsigned long index = hash(key, dict->size);
    Entry *current = dict->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void dictionary_free(Dictionary *dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->size; i++) {
        Entry *current = dict->buckets[i];
        while (current) {
            Entry *next = current->next;
            free(current->key);
            free(current);
            current = next;
        }
    }
    free(dict->buckets);
    free(dict);
}

int main(void) {
    Dictionary *dict = create_dictionary(10);
    if (!dict) return 1;

    dictionary_insert(dict, "apple", 1);
    dictionary_insert(dict, "banana", 2);
    dictionary_insert(dict, "cherry", 3);

    const char *keys_to_check[] = {"apple", "grape", "banana", "mango"};
    size_t num_keys = sizeof(keys_to_check) / sizeof(keys_to_check[0]);

    for (size_t i = 0; i < num_keys; i++) {
        if (dictionary_contains(dict, keys_to_check[i])) {
            printf("%s is present in the dictionary.\n", keys_to_check[i]);
        } else {
            printf("%s is not present in the dictionary.\n", keys_to_check[i]);
        }
    }

    dictionary_free(dict);
    return 0;
}