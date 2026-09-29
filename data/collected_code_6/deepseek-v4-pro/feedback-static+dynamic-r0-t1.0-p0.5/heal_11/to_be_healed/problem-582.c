#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

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
    while ((c = (unsigned char)*key++) != '\0')
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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t key_len = strlen(key);
    if (key_len >= d->size * 32) return -1;

    size_t alloc_size = key_len + 1;

    size_t index = hash_key(key, d->size);

    dict_entry *entry = malloc(sizeof(dict_entry));
    if (!entry) return -1;

    entry->key = malloc(alloc_size);
    if (!entry->key) {
        free(entry);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(entry->key, key, alloc_size);
    entry->value = value;
    entry->next = d->buckets[index];
    d->buckets[index] = entry;
    d->count++;
    return 0;
}

void *dict_find(const dictionary *d, const char *key) {
    if (!d || !key) return NULL;
    size_t index = hash_key(key, d->size);
    dict_entry *entry = d->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0)
            return entry->value;
        entry = entry->next;
    }
    return NULL;
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

    const int *found = (const int *)dict_find(d, "key1");
    if (found) {
        printf("Found value: %d\n", *found);
    }

    dict_destroy(d);
    return 0;
}