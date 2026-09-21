#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dict;

char *string_duplicate(const char *s) {
    if (!s) return NULL;
    size_t len = strnlen(s, SIZE_MAX - 1) + 1;
    char *copy = malloc(len);
    if (copy) {
        snprintf(copy, len, "%s", s);
    }
    return copy;
}

Dict dict_create(size_t capacity) {
    Dict d;
    d.size = 0;
    d.capacity = capacity;
    if (capacity > 0) {
        d.entries = malloc(capacity * sizeof(DictEntry));
        if (!d.entries) {
            d.capacity = 0;
            d.entries = NULL;
        }
    } else {
        d.entries = NULL;
    }
    return d;
}

int dict_insert(Dict *d, const char *key, const char *value) {
    if (!d || !key || !value) {
        return -1;
    }
    
    for (size_t i = 0; i < d->size; i++) {
        if (strcmp(d->entries[i].key, key) == 0) {
            char *new_val = string_duplicate(value);
            if (!new_val) {
                return -1;
            }
            free(d->entries[i].value);
            d->entries[i].value = new_val;
            return 0;
        }
    }
    
    if (d->size >= d->capacity) {
        size_t new_cap = d->capacity == 0 ? 4 : d->capacity * 2;
        DictEntry *new_entries = realloc(d->entries, new_cap * sizeof(DictEntry));
        if (!new_entries) {
            return -1;
        }
        d->entries = new_entries;
        d->capacity = new_cap;
    }
    
    char *new_key = string_duplicate(key);
    char *new_val = string_duplicate(value);
    
    if (!new_key || !new_val) {
        free(new_key);
        free(new_val);
        return -1;
    }
    
    d->entries[d->size].key = new_key;
    d->entries[d->size].value = new_val;
    d->size++;
    
    return 0;
}

int dict_merge(Dict *dest, const Dict *src) {
    if (!dest || !src) {
        return -1;
    }
    for (size_t i = 0; i < src->size; i++) {
        if (dict_insert(dest, src->entries[i].key, src->entries[i].value) != 0) {
            return -1;
        }
    }
    return 0;
}

void dict_free(Dict *d) {
    if (!d) {
        return;
    }
    for (size_t i = 0; i < d->size; i++) {
        free(d->entries[i].key);
        free(d->entries[i].value);
    }
    free(d->entries);
    d->entries = NULL;
    d->size = 0;
    d->capacity = 0;
}

int main(void) {
    Dict d1 = dict_create(2);
    Dict d2 = dict_create(2);

    dict_insert(&d1, "a", "1");
    dict_insert(&d1, "b", "2");

    dict_insert(&d2, "b", "3");
    dict_insert(&d2, "c", "4");

    if (dict_merge(&d1, &d2) != 0) {
        fprintf(stderr, "Merge failed\n");
        dict_free(&d1);
        dict_free(&d2);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < d1.size; i++) {
        printf("%s: %s\n", d1.entries[i].key, d1.entries[i].value);
    }

    dict_free(&d1);
    dict_free(&d2);

    return EXIT_SUCCESS;
}