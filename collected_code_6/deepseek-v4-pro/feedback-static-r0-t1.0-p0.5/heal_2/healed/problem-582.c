#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static unsigned long hash_string(const char *str, size_t len) {
    unsigned long hash = 5381;
    for (size_t i = 0; i < len; i++) {
        hash = ((hash << 5) + hash) + (unsigned char)str[i];
    }
    return hash;
}

dictionary *dict_create(size_t size) {
    if (size == 0) return NULL;
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
    if (!d || !key || d->size == 0) return -1;

    size_t key_len = 0;
    while (key[key_len] != '\0') {
        if (key_len >= SIZE_MAX / 2) return -1;
        key_len++;
    }

    unsigned long hash = hash_string(key, key_len);
    size_t index = hash % d->size;

    char *key_copy = malloc(key_len + 1);
    if (!key_copy) return -1;
    for (size_t i = 0; i <= key_len; i++) {
        key_copy[i] = key[i];
    }

    dict_entry *entry = malloc(sizeof(dict_entry));
    if (!entry) {
        free(key_copy);
        return -1;
    }

    entry->key = key_copy;
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