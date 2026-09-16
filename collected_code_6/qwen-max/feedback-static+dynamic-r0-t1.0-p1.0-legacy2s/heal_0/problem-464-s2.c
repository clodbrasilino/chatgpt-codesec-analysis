#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char *key;
    int value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t count;
} Dictionary;

bool areAllValuesTheSame(Dictionary *dict) {
    if (dict == NULL || dict->count == 0) {
        return false;
    }

    int firstValue = dict->entries[0].value;
    for (size_t i = 1; i < dict->count; ++i) {
        if (dict->entries[i].value != firstValue) {
            return false;
        }
    }
    return true;
}

int main() {
    Dictionary dict;
    dict.count = 4;
    dict.entries = (DictionaryEntry *)malloc(dict.count * sizeof(DictionaryEntry));

    dict.entries[0] = (DictionaryEntry){"apple", 5};
    dict.entries[1] = (DictionaryEntry){"banana", 5};
    dict.entries[2] = (DictionaryEntry){"cherry", 5};
    dict.entries[3] = (DictionaryEntry){"date", 5};

    if (areAllValuesTheSame(&dict)) {
        printf("All values are the same.\n");
    } else {
        printf("Not all values are the same.\n");
    }

    free(dict.entries);
    return 0;
}