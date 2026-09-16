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

Dict *dict_create(size_t capacity) {
    Dict *d = malloc(sizeof(Dict));
    if (d == NULL) return NULL;
    d->entries = malloc(sizeof(Entry) * capacity);
    if (d->entries == NULL) {
        free(d);
        return NULL;
    }
    d->size = 0;
    d->capacity = capacity;
    return d;
}

void dict_free(Dict *d) {
    if (d == NULL) return;
    for (size_t i = 0; i < d->size; i++) {
        free(d->entries[i].key);
    }
    free(d->entries);
    free(d);
}

int dict_insert(Dict *d, const char *key, int value) {
    if (d == NULL || key == NULL) return -1;
    for (size_t i = 0; i < d->size; i++) {
        if (strcmp(d->entries[i].key, key) == 0) {
            d->entries[i].value = value;
            return 0;
        }
    }
    if (d->size >= d->capacity) {
        size_t new_capacity = d->capacity == 0 ? 4 : d->capacity * 2;
        Entry *temp = realloc(d->entries, sizeof(Entry) * new_capacity);
        if (temp == NULL) return -1;
        d->entries = temp;
        d->capacity = new_capacity;
    }
    char *new_key = strdup(key);
    if (new_key == NULL) return -1;
    d->entries[d->size].key = new_key;
    d->entries[d->size].value = value;
    d->size++;
    return 0;
}

Dict *dict_merge(const Dict *d1, const Dict *d2) {
    if (d1 == NULL || d2 == NULL) return NULL;
    size_t initial_capacity = d1->size + d2->size;
    if (initial_capacity == 0) initial_capacity = 4;
    Dict *merged = dict_create(initial_capacity);
    if (merged == NULL) return NULL;
    for (size_t i = 0; i < d1->size; i++) {
        if (dict_insert(merged, d1->entries[i].key, d1->entries[i].value) != 0) {
            dict_free(merged);
            return NULL;
        }
    }
    for (size_t i = 0; i < d2->size; i++) {
        if (dict_insert(merged, d2->entries[i].key, d2->entries[i].value) != 0) {
            dict_free(merged);
            return NULL;
        }
    }
    return merged;
}

int main(void) {
    Dict *d1 = dict_create(4);
    if (d1 == NULL) return 1;
    Dict *d2 = dict_create(4);
    if (d2 == NULL) {
        dict_free(d1);
        return 1;
    }
    if (dict_insert(d1, "a", 1) != 0 || dict_insert(d1, "b", 2) != 0) {
        dict_free(d1);
        dict_free(d2);
        return 1;
    }
    if (dict_insert(d2, "b", 3) != 0 || dict_insert(d2, "c", 4) != 0) {
        dict_free(d1);
        dict_free(d2);
        return 1;
    }
    Dict *merged = dict_merge(d1, d2);
    if (merged == NULL) {
        dict_free(d1);
        dict_free(d2);
        return 1;
    }
    for (size_t i = 0; i < merged->size; i++) {
        printf("%s: %d\n", merged->entries[i].key, merged->entries[i].value);
    }
    dict_free(merged);
    dict_free(d1);
    dict_free(d2);
    return 0;
}