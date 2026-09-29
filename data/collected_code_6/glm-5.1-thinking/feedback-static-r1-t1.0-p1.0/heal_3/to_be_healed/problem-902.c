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
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t existing_len = strlen(d->entries[i].key);
        if (existing_len == key_len && memcmp(d->entries[i].key, key, key_len) == 0) {
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
    char *new_key = malloc(key_len + 1);
    if (new_key == NULL) return -1;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(new_key, key, key_len);
    new_key[key_len] = '\0';
    d->entries[d->size].key = new_key;
    d->entries[d->size].value = value;
    d->size++;
    return 0;
}

int dict_combine(Dict *result, const Dict *d1, const Dict *d2) {
    if (result == NULL || d1 == NULL || d2 == NULL) return -1;
    dict_init(result);
    for (size_t i = 0; i < d1->size; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(d1->entries[i].key);
        if (dict_add(result, d1->entries[i].key, len, d1->entries[i].value) != 0) {
            dict_free(result);
            return -1;
        }
    }
    for (size_t i = 0; i < d2->size; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(d2->entries[i].key);
        if (dict_add(result, d2->entries[i].key, len, d2->entries[i].value) != 0) {
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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    dict_add(&d1, "apple", strlen("apple"), 10);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    dict_add(&d1, "banana", strlen("banana"), 5);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    dict_add(&d2, "banana", strlen("banana"), 3);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    dict_add(&d2, "cherry", strlen("cherry"), 7);

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