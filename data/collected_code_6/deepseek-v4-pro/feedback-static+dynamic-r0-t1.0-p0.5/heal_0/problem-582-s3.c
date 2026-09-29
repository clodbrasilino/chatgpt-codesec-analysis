#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Entry {
    char *key;
    int value;
    struct Entry *next;
} Entry;

typedef struct Dictionary {
    Entry **buckets;
    size_t size;
    size_t count;
} Dictionary;

Dictionary *create_dictionary(size_t size) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->buckets = (Entry **)calloc(size, sizeof(Entry *));
    if (dict->buckets == NULL) {
        free(dict);
        return NULL;
    }
    dict->size = size;
    dict->count = 0;
    return dict;
}

void destroy_dictionary(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->size; i++) {
        Entry *entry = dict->buckets[i];
        while (entry != NULL) {
            Entry *next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    free(dict->buckets);
    free(dict);
}

int is_dictionary_empty(const Dictionary *dict) {
    if (dict == NULL) {
        return 1;
    }
    return dict->count == 0;
}

int main(void) {
    Dictionary *dict = create_dictionary(10);
    if (dict == NULL) {
        return 1;
    }

    if (is_dictionary_empty(dict)) {
        printf("Dictionary is empty\n");
    } else {
        printf("Dictionary is not empty\n");
    }

    destroy_dictionary(dict);
    return 0;
}