#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *key;
    size_t key_len;
    int value;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
    size_t capacity;
} Dict;

void dict_init(Dict *d) {
    d->entries = NULL;
    d->size = 0;
    d->capacity = 0;
}

void dict_free(Dict *d) {
    if (d == NULL) return;
    for (size_t i = 0; i < d->size; i++) {
        free(d->entries[i].key);
    }
    free(d->entries);
    d->entries = NULL;
    d->size = 0;
    d->capacity = 0;
}

int dict_add(Dict *d, const char *key, size_t key_len, int value) {
    if (d == NULL || key == NULL) return -1;
    for (size_t i = 0; i < d->size; i++) {
        if (d->entries[i].key_len == key_len && memcmp(d->entries[i].key, key, key_len) == 0) {
            d->entries[i].value += value;
            return 0;
        }
    }
    if (d->size >= d->capacity) {
        size_t new_capacity = d->capacity == 0 ? 4 : d->capacity * 2;
        if (new_capacity < d->capacity) return -1;
        if (new_capacity > SIZE_MAX / sizeof(Entry)) return -1;
        Entry *new_entries = realloc(d->entries, new_capacity * sizeof(Entry));
        if (new_entries == NULL) return -1;
        d->entries = new_entries;
        d->capacity = new_capacity;
    }
    size_t dest_size = key_len + 1;
    if (dest_size == 0) return -1;
    char *new_key = malloc(dest_size);
    if (new_key == NULL) return -1;
    if (dest_size < key_len) {
        free(new_key);
        return -1;
    }
    memcpy(new_key, key, key_len);
    new_key[key_len] = '\0';
    d->entries[d->size].key = new_key;
    d->entries[d->size].key_len = key_len;
    d->entries[d->size].value = value;
    d->size++;
    return 0;
}

int dict_combine(Dict *result, const Dict *d1, const Dict *d2) {
    if (result == NULL || d1 == NULL || d2 == NULL) return -1;
    dict_init(result);
    for (size_t i = 0; i < d1->size; i++) {
        if (dict_add(result, d1->entries[i].key, d1->entries[i].key_len, d1->entries[i].value) != 0) {
            dict_free(result);
            return -1;
        }
    }
    for (size_t i = 0; i < d2->size; i++) {
        if (dict_add(result, d2->entries[i].key, d2->entries[i].key_len, d2->entries[i].value) != 0) {
            dict_free(result);
            return -1;
        }
    }
    return 0;
}

int main(void) {
    Dict d1;
    Dict d2;
    Dict combined;

    dict_init(&d1);
    dict_init(&d2);

    dict_add(&d1, "apple", sizeof("apple") - 1, 10);
    dict_add(&d1, "banana", sizeof("banana") - 1, 5);
    dict_add(&d2, "banana", sizeof("banana") - 1, 3);
    dict_add(&d2, "cherry", sizeof("cherry") - 1, 7);

    if (dict_combine(&combined, &d1, &d2) == 0) {
        for (size_t i = 0; i < combined.size; i++) {
            printf("%s: %d\n", combined.entries[i].key, combined.entries[i].value);
        }
        dict_free(&combined);
    }

    dict_free(&d1);
    dict_free(&d2);

    return 0;
}