#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    Dict *dict = malloc(sizeof(Dict));
    if (!dict) return NULL;
    if (size == 0) size = 1;
    dict->buckets = calloc(size, sizeof(Entry *));
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
    if (!dict || !key || dict->size == 0) return 0;
    size_t index = hash(key) % dict->size;
    Entry *entry = dict->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) return 1;
        entry = entry->next;
    }
    return 0;
}

void dict_insert(Dict *dict, const char *key, int value) {
    if (!dict || !key || dict->size == 0) return;
    size_t index = hash(key) % dict->size;
    Entry *entry = dict->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value;
            return;
        }
        entry = entry->next;
    }
    Entry *new_entry = malloc(sizeof(Entry));
    if (!new_entry) return;
    size_t key_len = strlen(key);
    size_t buf_size = key_len + 1;
    new_entry->key = malloc(buf_size);
    if (!new_entry->key) {
        free(new_entry);
        return;
    }
    snprintf(new_entry->key, buf_size, "%s", key);
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