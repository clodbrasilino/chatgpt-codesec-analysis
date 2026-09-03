#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char *key;
    int value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    int size;
} Dictionary;

bool areAllValuesSame(Dictionary *dict) {
    if (dict->size == 0) return true;
    int firstValue = dict->entries[0].value;
    for (int i = 1; i < dict->size; ++i) {
        if (dict->entries[i].value != firstValue) {
            return false;
        }
    }
    return true;
}

int main() {
    Dictionary dict = { .size = 3, .entries = (DictionaryEntry[]) {
        { .key = "one", .value = 42 },
        { .key = "two", .value = 42 },
        { .key = "three", .value = 42 }
    }};

    if (areAllValuesSame(&dict)) {
        printf("All values are the same.\n");
    } else {
        printf("Not all values are the same.\n");
    }

    return 0;
}