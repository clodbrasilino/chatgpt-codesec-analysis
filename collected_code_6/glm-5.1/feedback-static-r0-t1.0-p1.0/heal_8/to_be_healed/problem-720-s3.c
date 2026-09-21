#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[64];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char value[128];
} DictEntry;

typedef struct {
    DictEntry* entries;
    size_t capacity;
    size_t size;
} Dictionary;

typedef struct {
    Dictionary** dictionaries;
    size_t capacity;
    size_t size;
} Tuple;

Tuple* tuple_create(size_t capacity) {
    Tuple* t = malloc(sizeof(Tuple));
    if (!t) return NULL;
    t->dictionaries = malloc(sizeof(Dictionary*) * capacity);
    if (!t->dictionaries) {
        free(t);
        return NULL;
    }
    t->capacity = capacity;
    t->size = 0;
    return t;
}

Dictionary* dictionary_create(size_t capacity) {
    Dictionary* d = malloc(sizeof(Dictionary));
    if (!d) return NULL;
    d->entries = malloc(sizeof(DictEntry) * capacity);
    if (!d->entries) {
        free(d);
        return NULL;
    }
    d->capacity = capacity;
    d->size = 0;
    return d;
}

int dictionary_add_entry(Dictionary* d, const char* key, const char* value) {
    if (!d || !key || !value || d->size >= d->capacity) return -1;
    snprintf(d->entries[d->size].key, sizeof(d->entries[d->size].key), "%s", key);
    snprintf(d->entries[d->size].value, sizeof(d->entries[d->size].value), "%s", value);
    d->size++;
    return 0;
}

int tuple_add_dictionary(Tuple* t, Dictionary* d) {
    if (!t || !d || t->size >= t->capacity) return -1;
    t->dictionaries[t->size] = d;
    t->size++;
    return 0;
}

void dictionary_free(Dictionary* d) {
    if (!d) return;
    free(d->entries);
    free(d);
}

void tuple_free(Tuple* t) {
    if (!t) return;
    for (size_t i = 0; i < t->size; i++) {
        dictionary_free(t->dictionaries[i]);
    }
    free(t->dictionaries);
    free(t);
}

int main(void) {
    Tuple* t = tuple_create(2);
    if (!t) return EXIT_FAILURE;

    Dictionary* d1 = dictionary_create(3);
    if (!d1) {
        tuple_free(t);
        return EXIT_FAILURE;
    }

    if (dictionary_add_entry(d1, "id", "123") != 0) {
        dictionary_free(d1);
        tuple_free(t);
        return EXIT_FAILURE;
    }
    
    if (dictionary_add_entry(d1, "name", "Alice") != 0) {
        dictionary_free(d1);
        tuple_free(t);
        return EXIT_FAILURE;
    }

    if (tuple_add_dictionary(t, d1) != 0) {
        dictionary_free(d1);
        tuple_free(t);
        return EXIT_FAILURE;
    }

    Dictionary* d2 = dictionary_create(2);
    if (!d2) {
        tuple_free(t);
        return EXIT_FAILURE;
    }

    if (dictionary_add_entry(d2, "status", "active") != 0) {
        dictionary_free(d2);
        tuple_free(t);
        return EXIT_FAILURE;
    }

    if (tuple_add_dictionary(t, d2) != 0) {
        dictionary_free(d2);
        tuple_free(t);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < t->size; i++) {
        printf("Dictionary %zu:\n", i);
        for (size_t j = 0; j < t->dictionaries[i]->size; j++) {
            printf("  %s: %s\n", t->dictionaries[i]->entries[j].key, t->dictionaries[i]->entries[j].value);
        }
    }

    tuple_free(t);
    return EXIT_SUCCESS;
}