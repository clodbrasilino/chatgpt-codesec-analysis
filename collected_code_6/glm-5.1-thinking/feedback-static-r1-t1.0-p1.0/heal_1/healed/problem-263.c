#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dict;

Dict dict_create(size_t capacity) {
    Dict d = {NULL, 0, 0};
    if (capacity > 0) {
        d.entries = calloc(capacity, sizeof(DictEntry));
        if (d.entries) {
            d.capacity = capacity;
        }
    }
    return d;
}

void dict_free(Dict *d) {
    if (d) {
        for (size_t i = 0; i < d->size; i++) {
            free(d->entries[i].key);
            free(d->entries[i].value);
        }
        free(d->entries);
        d->entries = NULL;
        d->size = 0;
        d->capacity = 0;
    }
}

int dict_set(Dict *d, const char *key, const char *value) {
    if (!d || !key || !value) return -1;
    
    for (size_t i = 0; i < d->size; i++) {
        if (strcmp(d->entries[i].key, key) == 0) {
            char *new_value = strdup(value);
            if (!new_value) return -1;
            free(d->entries[i].value);
            d->entries[i].value = new_value;
            return 0;
        }
    }
    
    if (d->size >= d->capacity) {
        size_t new_cap = d->capacity == 0 ? 4 : d->capacity * 2;
        DictEntry *new_entries = realloc(d->entries, new_cap * sizeof(DictEntry));
        if (!new_entries) return -1;
        d->entries = new_entries;
        d->capacity = new_cap;
    }
    
    char *new_key = strdup(key);
    if (!new_key) return -1;
    
    char *new_value = strdup(value);
    if (!new_value) {
        free(new_key);
        return -1;
    }
    
    d->entries[d->size].key = new_key;
    d->entries[d->size].value = new_value;
    d->size++;
    
    return 0;
}

int dict_merge(Dict *dest, const Dict *src) {
    if (!dest || !src) return -1;
    for (size_t i = 0; i < src->size; i++) {
        if (dict_set(dest, src->entries[i].key, src->entries[i].value) != 0) {
            return -1;
        }
    }
    return 0;
}

int main(void) {
    Dict d1 = dict_create(2);
    Dict d2 = dict_create(2);
    
    if (dict_set(&d1, "a", "1") != 0 ||
        dict_set(&d1, "b", "2") != 0 ||
        dict_set(&d2, "b", "3") != 0 ||
        dict_set(&d2, "c", "4") != 0) {
        fprintf(stderr, "Dict set failed\n");
        dict_free(&d1);
        dict_free(&d2);
        return 1;
    }
    
    if (dict_merge(&d1, &d2) != 0) {
        fprintf(stderr, "Dict merge failed\n");
        dict_free(&d1);
        dict_free(&d2);
        return 1;
    }
    
    for (size_t i = 0; i < d1.size; i++) {
        printf("%s: %s\n", d1.entries[i].key, d1.entries[i].value);
    }
    
    dict_free(&d1);
    dict_free(&d2);
    
    return 0;
}