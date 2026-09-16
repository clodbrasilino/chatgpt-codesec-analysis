#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} dict_entry;

typedef struct {
    dict_entry *entries;
    size_t size;
    size_t capacity;
} dictionary;

dictionary *create_dictionary(size_t initial_capacity) {
    dictionary *d = (dictionary *)malloc(sizeof(dictionary));
    d->entries = (dict_entry *)malloc(initial_capacity * sizeof(dict_entry));
    d->size = 0;
    d->capacity = initial_capacity;
    return d;
}

void free_dictionary(dictionary *d) {
    for (size_t i = 0; i < d->size; ++i) {
        free(d->entries[i].key);
    }
    free(d->entries);
    free(d);
}

int add_entry(dictionary *d, const char *key, int value) {
    if (d->size >= d->capacity) {
        return -1;
    }
    dict_entry *e = &d->entries[d->size++];
    e->key = strdup(key);
    if (e->key == NULL) {
        return -1;
    }
    e->value = value;
    return 0;
}

int find_entry(const dictionary *d, const char *key) {
    for (size_t i = 0; i < d->size; ++i) {
        if (strcmp(d->entries[i].key, key) == 0) {
            return d->entries[i].value;
        }
    }
    return -1;
}

dictionary *merge_dictionaries(const dictionary *d1, const dictionary *d2, const dictionary *d3) {
    dictionary *merged = create_dictionary(d1->size + d2->size + d3->size);
    for (size_t i = 0; i < d1->size; ++i) {
        if (add_entry(merged, d1->entries[i].key, d1->entries[i].value) != 0) {
            free_dictionary(merged);
            return NULL;
        }
    }
    for (size_t i = 0; i < d2->size; ++i) {
        if (add_entry(merged, d2->entries[i].key, d2->entries[i].value) != 0) {
            free_dictionary(merged);
            return NULL;
        }
    }
    for (size_t i = 0; i < d3->size; ++i) {
        if (add_entry(merged, d3->entries[i].key, d3->entries[i].value) != 0) {
            free_dictionary(merged);
            return NULL;
        }
    }
    return merged;
}

int main() {
    dictionary *d1 = create_dictionary(4);
    add_entry(d1, "a", 1);
    add_entry(d1, "b", 2);

    dictionary *d2 = create_dictionary(4);
    add_entry(d2, "c", 3);
    add_entry(d2, "d", 4);

    dictionary *d3 = create_dictionary(4);
    add_entry(d3, "e", 5);
    add_entry(d3, "f", 6);

    dictionary *merged = merge_dictionaries(d1, d2, d3);
    if (merged) {
        for (size_t i = 0; i < merged->size; ++i) {
            printf("%s: %d\n", merged->entries[i].key, merged->entries[i].value);
        }
        free_dictionary(merged);
    }

    free_dictionary(d1);
    free_dictionary(d2);
    free_dictionary(d3);

    return 0;
}