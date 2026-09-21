#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct dict_entry {
    char *key;
    void *value;
    struct dict_entry *next;
} dict_entry;

typedef struct {
    dict_entry **buckets;
    size_t size;
    size_t count;
} dictionary;

static size_t hash_key(const char *key, size_t size) {
    size_t hash = 5381;
    int c;
    while ((c = *key++))
        hash = ((hash << 5) + hash) + c;
    return hash % size;
}

dictionary *dict_create(size_t size) {
    dictionary *d = malloc(sizeof(dictionary));
    if (!d) return NULL;
    d->buckets = calloc(size, sizeof(dict_entry *));
    if (!d->buckets) {
        free(d);
        return NULL;
    }
    d->size = size;
    d->count = 0;
    return d;
}

void dict_destroy(dictionary *d) {
    if (!d) return;
    for (size_t i = 0; i < d->size; i++) {
        dict_entry *entry = d->buckets[i];
        while (entry) {
            dict_entry *next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    free(d->buckets);
    free(d);
}

int dict_is_empty(const dictionary *d) {
    if (!d) return 1;
    return d->count == 0;
}

int dict_insert(dictionary *d, const char *key, void *value) {
    if (!d || !key) return -1;

    size_t key_len = strnlen(key, SIZE_MAX);
    if (key_len == SIZE_MAX) return -1;

    size_t alloc_size = key_len + 1;
    if (alloc_size <= key_len) return -1;

    size_t index = hash_key(key, d->size);

    dict_entry *entry = malloc(sizeof(dict_entry));
    if (!entry) return -1;

    entry->key = malloc(alloc_size);
    if (!entry->key) {
        free(entry);
        return -1;
    }

    memcpy(entry->key, key, alloc_size);
    entry->value = value;
    entry->next = d->buckets[index];
    d->buckets[index] = entry;
    d->count++;
    return 0;
}

int main(void) {
    dictionary *d = dict_create(10);
    if (!d) return 1;

    if (dict_is_empty(d)) {
        printf("Dictionary is empty\n");
    } else {
        printf("Dictionary is not empty\n");
    }

    int value = 42;
    if (dict_insert(d, "key1", &value) == 0) {
        if (dict_is_empty(d)) {
            printf("Dictionary is empty\n");
        } else {
            printf("Dictionary is not empty\n");
        }
    }

    dict_destroy(d);
    return 0;
}