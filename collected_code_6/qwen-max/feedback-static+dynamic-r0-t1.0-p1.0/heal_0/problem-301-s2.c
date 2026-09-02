#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* key;
    void* value;
} DictionaryEntry;

typedef struct {
    int size;
    DictionaryEntry* entries;
} Dictionary;

int findDepth(Dictionary* dict) {
    if (dict == NULL || dict->entries == NULL) return 0;
    int maxDepth = 0;
    for (int i = 0; i < dict->size; ++i) {
        int depth = 1 + findDepth((Dictionary*)dict->entries[i].value);
        if (depth > maxDepth) maxDepth = depth;
    }
    return maxDepth;
}

int main() {
    Dictionary* sampleDict = (Dictionary*)malloc(sizeof(Dictionary));
    sampleDict->size = 1;
    sampleDict->entries = (DictionaryEntry*)malloc(sampleDict->size * sizeof(DictionaryEntry));

    sampleDict->entries[0].key = "level1";
    Dictionary* nestedDict = (Dictionary*)malloc(sizeof(Dictionary));
    nestedDict->size = 1;
    nestedDict->entries = (DictionaryEntry*)malloc(nestedDict->size * sizeof(DictionaryEntry));
    nestedDict->entries[0].key = "level2";
    nestedDict->entries[0].value = NULL; // No further nesting
    sampleDict->entries[0].value = nestedDict;

    printf("Depth: %d\n", findDepth(sampleDict));

    // Clean up
    free(nestedDict->entries);
    free(nestedDict);
    free(sampleDict->entries);
    free(sampleDict);

    return 0;
}