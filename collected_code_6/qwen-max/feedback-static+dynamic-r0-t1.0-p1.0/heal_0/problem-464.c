#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    int count;
} Dictionary;

int all_values_same(Dictionary *dict) {
    if (dict->count <= 1) {
        return 1;
    }
    int first_value = dict->entries[0].value;
    for (int i = 1; i < dict->count; i++) {
        if (dict->entries[i].value != first_value) {
            return 0;
        }
    }
    return 1;
}

int main() {
    Dictionary dict = {
        .entries = (DictionaryEntry[]){
            {"a", 1},
            {"b", 1},
            {"c", 1}
        },
        .count = 3
    };

    if (all_values_same(&dict)) {
        printf("All values are the same.\n");
    } else {
        printf("Values are not the same.\n");
    }

    return 0;
}