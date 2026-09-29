#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DictEntry {
    char *key;
    void *value;
    struct DictEntry *next;
} DictEntry;

typedef struct Dictionary {
    DictEntry **entries;
    size_t capacity;
    size_t size;
} Dictionary;

Dictionary *dict_create(size_t capacity) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->entries = calloc(capacity, sizeof(DictEntry *));
    if (!dict->entries) {
        free(dict);
        return NULL;
    }
    dict->capacity = capacity;
    dict->size = 0;
    return dict;
}

void dict_destroy(Dictionary *dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->capacity; i++) {
        DictEntry *entry = dict->entries[i];
        while (entry) {
            DictEntry *next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    free(dict->entries);
    free(dict);
}

int dict_is_empty(const Dictionary *dict) {
    if (!dict) return 1;
    return dict->size == 0;
}

int main(void) {
    Dictionary *dict = dict_create(16);
    if (!dict) {
        fprintf(stderr, "Allocation failed\n");
        return 1;
    }

    if (dict_is_empty(dict)) {
        printf("Dictionary is empty\n");
    } else {
        printf("Dictionary is not empty\n");
    }

    dict_destroy(dict);
    dict = NULL;

    if (dict == NULL) {
        printf("NULL dictionary is empty\n");
    } else {
        printf("NULL dictionary is not empty\n");
    }

    return 0;
}