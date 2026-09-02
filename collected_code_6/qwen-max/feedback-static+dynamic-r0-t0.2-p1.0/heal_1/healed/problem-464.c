#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    int count;
} Dictionary;

bool areAllValuesSame(Dictionary *dict) {
    if (dict->count <= 1) return true;

    int firstValue = dict->entries[0].value;
    for (int i = 1; i < dict->count; ++i) {
        if (dict->entries[i].value != firstValue) {
            return false;
        }
    }
    return true;
}

int main() {
    Dictionary dict = {
        .entries = (DictionaryEntry[]) {
            {1},
            {1},
            {1}
        },
        .count = 3
    };

    if (areAllValuesSame(&dict)) {
        printf("All values in the dictionary are the same.\n");
    } else {
        printf("Not all values in the dictionary are the same.\n");
    }

    return 0;
}