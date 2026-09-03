#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    int count;
} Dictionary;

int compare(const void *a, const void *b) {
    return strcmp(((DictionaryEntry *)a)->value, ((DictionaryEntry *)b)->value);
}

void extractUniqueValues(Dictionary *dict, char ***uniqueValues, int *uniqueCount) {
    qsort(dict->entries, dict->count, sizeof(DictionaryEntry), compare);

    *uniqueCount = 0;
    *uniqueValues = (char **)malloc(dict->count * sizeof(char *));
    if (*uniqueValues == NULL) {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < dict->count; ++i) {
        if (i == 0 || strcmp(dict->entries[i].value, dict->entries[i - 1].value) != 0) {
            (*uniqueValues)[*uniqueCount] = strdup(dict->entries[i].value);
            if ((*uniqueValues)[*uniqueCount] == NULL) {
                exit(EXIT_FAILURE);
            }
            (*uniqueCount)++;
        }
    }
}

int main() {
    Dictionary dict = {
        .entries = (DictionaryEntry[]) {
            {"key1", "value1"},
            {"key2", "value2"},
            {"key3", "value1"},
            {"key4", "value3"},
            {"key5", "value2"}
        },
        .count = 5
    };

    char **uniqueValues;
    int uniqueCount;

    extractUniqueValues(&dict, &uniqueValues, &uniqueCount);

    for (int i = 0; i < uniqueCount; ++i) {
        printf("%s\n", uniqueValues[i]);
        free(uniqueValues[i]);
    }
    free(uniqueValues);

    return 0;
}