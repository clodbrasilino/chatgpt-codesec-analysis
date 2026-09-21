#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Entry {
    char *key;
    int value;
    struct Entry *next;
} Entry;

typedef struct {
    Entry **buckets;
    size_t capacity;
} Dictionary;

static unsigned long hash_key(const char *key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

Dictionary *dict_create(size_t capacity) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }
    dict->buckets = calloc(capacity, sizeof(Entry *));
    if (!dict->buckets) {
        free(dict);
        return NULL;
    }
    dict->capacity = capacity;
    return dict;
}

int dict_insert(Dictionary *dict, const char *key, int value) {
    if (!dict || !key) {
        return 0;
    }
    size_t index = hash_key(key) % dict->capacity;
    Entry *current = dict->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return 1;
        }
        current = current->next;
    }
    Entry *new_entry = malloc(sizeof(Entry));
    if (!new_entry) {
        return 0;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(key) + 1;
    new_entry->key = malloc(len);
    if (!new_entry->key) {
        free(new_entry);
        return 0;
    }
    snprintf(new_entry->key, len, "%s", key);
    new_entry->value = value;
    new_entry->next = dict->buckets[index];
    dict->buckets[index] = new_entry;
    return 1;
}

int dict_contains(Dictionary *dict, const char *key) {
    if (!dict || !key) {
        return 0;
    }
    size_t index = hash_key(key) % dict->capacity;
    Entry *current = dict->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void dict_destroy(Dictionary *dict) {
    if (!dict) {
        return;
    }
    for (size_t i = 0; i < dict->capacity; i++) {
        Entry *current = dict->buckets[i];
        while (current) {
            Entry *next = current->next;
            free(current->key);
            free(current);
            current = next;
        }
    }
    free(dict->buckets);
    free(dict);
}

int main(void) {
    Dictionary *dict = dict_create(32);
    if (!dict) {
        return EXIT_FAILURE;
    }
    if (!dict_insert(dict, "apple", 1)) {
        dict_destroy(dict);
        return EXIT_FAILURE;
    }
    if (!dict_insert(dict, "banana", 2)) {
        dict_destroy(dict);
        return EXIT_FAILURE;
    }
    printf("Contains 'apple': %d\n", dict_contains(dict, "apple"));
    printf("Contains 'banana': %d\n", dict_contains(dict, "banana"));
    printf("Contains 'cherry': %d\n", dict_contains(dict, "cherry"));
    printf("Contains NULL: %d\n", dict_contains(dict, NULL));
    dict_destroy(dict);
    return EXIT_SUCCESS;
}