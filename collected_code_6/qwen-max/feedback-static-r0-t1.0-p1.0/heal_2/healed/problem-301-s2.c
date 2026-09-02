#include <stdio.h>
#include <stdlib.h>

typedef struct DictionaryEntry {
    char *key;
    void *value;
    struct DictionaryEntry *next;
} DictionaryEntry;

typedef struct Dictionary {
    int size;
    DictionaryEntry **buckets;
} Dictionary;

int max(int a, int b) { return (a > b) ? a : b; }

int dictionary_depth(Dictionary *dict) {
    if (!dict || !dict->buckets) return 0;
    int depth = 0;
    for (int i = 0; i < dict->size; ++i) {
        DictionaryEntry *entry = dict->buckets[i];
        while (entry) {
            depth = max(depth, 1 + ((Dictionary*)entry->value)->size);
            entry = entry->next;
        }
    }
    return depth;
}

int main() {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    dict->size = 3;
    dict->buckets = (DictionaryEntry **)calloc(dict->size, sizeof(DictionaryEntry *));

    // Add entries to the dictionary as needed

    int depth = dictionary_depth(dict);

    printf("Depth: %d\n", depth);

    for (int i = 0; i < dict->size; ++i) {
        DictionaryEntry *entry = dict->buckets[i];
        while (entry) {
            DictionaryEntry *temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp->value); 
            free(temp);
        }
    }
    free(dict->buckets);
    free(dict);

    return 0;
}