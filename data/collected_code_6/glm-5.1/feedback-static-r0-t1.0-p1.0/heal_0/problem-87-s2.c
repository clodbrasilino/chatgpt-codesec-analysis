#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary *dict_create(size_t capacity) {
    Dictionary *d = malloc(sizeof(Dictionary));
    if (!d) return NULL;
    d->entries = malloc(capacity * sizeof(Entry));
    if (!d->entries) {
        free(d);
        return NULL;
    }
    d->size = 0;
    d->capacity = capacity;
    return d;
}

int dict_insert(Dictionary *d, const char *key, const char *value) {
    if (!d || !key || !value) return -1;
    for (size_t i = 0; i < d->size; i++) {
        if (strcmp(d->entries[i].key, key) == 0) {
            char *new_val = strdup(value);
            if (!new_val) return -1;
            free(d->entries[i].value);
            d->entries[i].value = new_val;
            return 0;
        }
    }
    if (d->size >= d->capacity) {
        size_t new_cap = d->capacity * 2;
        Entry *new_entries = realloc(d->entries, new_cap * sizeof(Entry));
        if (!new_entries) return -1;
        d->entries = new_entries;
        d->capacity = new_cap;
    }
    d->entries[d->size].key = strdup(key);
    d->entries[d->size].value = strdup(value);
    if (!d->entries[d->size].key || !d->entries[d->size].value) {
        free(d->entries[d->size].key);
        free(d->entries[d->size].value);
        return -1;
    }
    d->size++;
    return 0;
}

void dict_free(Dictionary *d) {
    if (!d) return;
    for (size_t i = 0; i < d->size; i++) {
        free(d->entries[i].key);
        free(d->entries[i].value);
    }
    free(d->entries);
    free(d);
}

Dictionary *merge_three_dictionaries(const Dictionary *d1, const Dictionary *d2, const Dictionary *d3) {
    if (!d1 || !d2 || !d3) return NULL;
    size_t total_capacity = d1->size + d2->size + d3->size;
    if (total_capacity == 0) total_capacity = 1;
    Dictionary *merged = dict_create(total_capacity);
    if (!merged) return NULL;
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
    for (size_t i = 0; i < d3->size; i++) {
        if (dict_insert(merged, d3->entries[i].key, d3->entries[i].value) != 0) {
            dict_free(merged);
            return NULL;
        }
    }
    return merged;
}

void dict_print(const Dictionary *d) {
    if (!d) return;
    for (size_t i = 0; i < d->size; i++) {
        printf("\"%s\": \"%s\"\n", d->entries[i].key, d->entries[i].value);
    }
}

int main(void) {
    Dictionary *d1 = dict_create(4);
    Dictionary *d2 = dict_create(4);
    Dictionary *d3 = dict_create(4);
    if (!d1 || !d2 || !d3) {
        dict_free(d1);
        dict_free(d2);
        dict_free(d3);
        return EXIT_FAILURE;
    }
    dict_insert(d1, "a", "1");
    dict_insert(d1, "b", "2");
    dict_insert(d2, "b", "3");
    dict_insert(d2, "c", "4");
    dict_insert(d3, "d", "5");
    Dictionary *result = merge_three_dictionaries(d1, d2, d3);
    if (!result) {
        dict_free(d1);
        dict_free(d2);
        dict_free(d3);
        return EXIT_FAILURE;
    }
    dict_print(result);
    dict_free(d1);
    dict_free(d2);
    dict_free(d3);
    dict_free(result);
    return EXIT_SUCCESS;
}