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
} Dictionary;

Dictionary create_dictionary(size_t capacity) {
    Dictionary d;
    d.entries = (DictEntry *)malloc(capacity * sizeof(DictEntry));
    d.size = 0;
    d.capacity = capacity;
    return d;
}

void free_dictionary(Dictionary *d) {
    for (size_t i = 0; i < d->size; i++) {
        free(d->entries[i].key);
        free(d->entries[i].value);
    }
    free(d->entries);
    d->entries = NULL;
    d->size = 0;
    d->capacity = 0;
}

int insert_dictionary(Dictionary *d, const char *key, const char *value) {
    if (d->size >= d->capacity) {
        size_t new_capacity = d->capacity == 0 ? 4 : d->capacity * 2;
        DictEntry *new_entries = (DictEntry *)realloc(d->entries, new_capacity * sizeof(DictEntry));
        if (!new_entries) return 0;
        d->entries = new_entries;
        d->capacity = new_capacity;
    }
    d->entries[d->size].key = strdup(key);
    d->entries[d->size].value = strdup(value);
    if (!d->entries[d->size].key || !d->entries[d->size].value) {
        free(d->entries[d->size].key);
        free(d->entries[d->size].value);
        return 0;
    }
    d->size++;
    return 1;
}

Dictionary merge_dictionaries(const Dictionary *d1, const Dictionary *d2, const Dictionary *d3) {
    size_t total_size = d1->size + d2->size + d3->size;
    Dictionary merged = create_dictionary(total_size > 0 ? total_size : 1);
    if (!merged.entries && total_size > 0) {
        return merged;
    }
    for (size_t i = 0; i < d1->size; i++) {
        if (!insert_dictionary(&merged, d1->entries[i].key, d1->entries[i].value)) {
            free_dictionary(&merged);
            merged = create_dictionary(0);
            return merged;
        }
    }
    for (size_t i = 0; i < d2->size; i++) {
        if (!insert_dictionary(&merged, d2->entries[i].key, d2->entries[i].value)) {
            free_dictionary(&merged);
            merged = create_dictionary(0);
            return merged;
        }
    }
    for (size_t i = 0; i < d3->size; i++) {
        if (!insert_dictionary(&merged, d3->entries[i].key, d3->entries[i].value)) {
            free_dictionary(&merged);
            merged = create_dictionary(0);
            return merged;
        }
    }
    return merged;
}

int main(void) {
    Dictionary d1 = create_dictionary(2);
    Dictionary d2 = create_dictionary(2);
    Dictionary d3 = create_dictionary(2);

    insert_dictionary(&d1, "a", "1");
    insert_dictionary(&d1, "b", "2");
    insert_dictionary(&d2, "c", "3");
    insert_dictionary(&d2, "d", "4");
    insert_dictionary(&d3, "e", "5");
    insert_dictionary(&d3, "f", "6");

    Dictionary merged = merge_dictionaries(&d1, &d2, &d3);

    for (size_t i = 0; i < merged.size; i++) {
        printf("%s: %s\n", merged.entries[i].key, merged.entries[i].value);
    }

    free_dictionary(&d1);
    free_dictionary(&d2);
    free_dictionary(&d3);
    free_dictionary(&merged);

    return 0;
}