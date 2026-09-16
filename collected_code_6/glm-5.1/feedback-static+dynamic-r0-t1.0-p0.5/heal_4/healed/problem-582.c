#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DictEntry {
    char *key;
    void *value;
    struct DictEntry *next;
} DictEntry;

typedef struct Dictionary {
    DictEntry **buckets;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary *dict_create(size_t capacity) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->buckets = calloc(capacity, sizeof(DictEntry *));
    if (!dict->buckets) {
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

void dict_destroy(Dictionary *dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->capacity; i++) {
        DictEntry *entry = dict->buckets[i];
        while (entry) {
            DictEntry *next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    free(dict->buckets);
    free(dict);
}

int dict_is_empty(const Dictionary *dict) {
    if (!dict) {
        fprintf(stderr, "dict_is_empty called with NULL\n");
        return -1;
    }
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

    const Dictionary *null_dict = NULL;
    int empty_status = dict_is_empty(null_dict);
    if (empty_status == 1) {
        printf("Dictionary is empty\n");
    } else if (empty_status == 0) {
        printf("Dictionary is not empty\n");
    } else {
        printf("Invalid dictionary\n");
    }

    return 0;
}