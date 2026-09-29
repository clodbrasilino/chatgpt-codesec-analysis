#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
    size_t capacity;
} Dict;

int dict_init(Dict *d) {
    d->entries = NULL;
    d->size = 0;
    d->capacity = 0;
    return 0;
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

int dict_add(Dict *d, const char *key, int value) {
    for (size_t i = 0; i < d->size; i++) {
        if (strcmp(d->entries[i].key, key) == 0) {
            d->entries[i].value += value;
            return 0;
        }
    }
    if (d->size >= d->capacity) {
        size_t new_capacity = d->capacity == 0 ? 4 : d->capacity * 2;
        Entry *new_entries = realloc(d->entries, new_capacity * sizeof(Entry));
        if (new_entries == NULL) return -1;
        d->entries = new_entries;
        d->capacity = new_capacity;
    }
    char *new_key = malloc(strlen(key) + 1);
    if (new_key == NULL) return -1;
    strcpy(new_key, key);
    d->entries[d->size].key = new_key;
    d->entries[d->size].value = value;
    d->size++;
    return 0;
}

int dict_combine(Dict *result, const Dict *d1, const Dict *d2) {
    if (dict_init(result) != 0) return -1;
    for (size_t i = 0; i < d1->size; i++) {
        if (dict_add(result, d1->entries[i].key, d1->entries[i].value) != 0) {
            dict_free(result);
            return -1;
        }
    }
    for (size_t i = 0; i < d2->size; i++) {
        if (dict_add(result, d2->entries[i].key, d2->entries[i].value) != 0) {
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

    dict_add(&d1, "apple", 10);
    dict_add(&d1, "banana", 5);
    dict_add(&d2, "banana", 3);
    dict_add(&d2, "cherry", 7);

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