#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct DictionaryEntry {
    char *key;
    void *value;
    struct DictionaryEntry *next;
} DictionaryEntry;

typedef struct {
    DictionaryEntry **buckets;
    size_t capacity;
    size_t size;
} Dictionary;

Dictionary* dictionary_create(size_t capacity);
void dictionary_destroy(Dictionary *dict);
bool dictionary_is_empty(const Dictionary *dict);

Dictionary* dictionary_create(size_t capacity) {
    if (capacity == 0) {
        return NULL;
    }

    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }

    dict->buckets = calloc(capacity, sizeof(DictionaryEntry *));
    if (!dict->buckets) {
        free(dict);
        return NULL;
    }

    dict->capacity = capacity;
    dict->size = 0;

    return dict;
}

void dictionary_destroy(Dictionary *dict) {
    if (!dict) {
        return;
    }

    for (size_t i = 0; i < dict->capacity; ++i) {
        DictionaryEntry *entry = dict->buckets[i];
        while (entry) {
            DictionaryEntry *next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }

    free(dict->buckets);
    free(dict);
}

bool dictionary_is_empty(const Dictionary *dict) {
    if (!dict) {
        return true;
    }
    return dict->size == 0;
}

int main(void) {
    Dictionary *dict = dictionary_create(16);
    if (!dict) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (dictionary_is_empty(dict)) {
        printf("Dictionary is empty\n");
    } else {
        printf("Dictionary is not empty\n");
    }

    dictionary_destroy(dict);
    dict = NULL;

    return EXIT_SUCCESS;
}