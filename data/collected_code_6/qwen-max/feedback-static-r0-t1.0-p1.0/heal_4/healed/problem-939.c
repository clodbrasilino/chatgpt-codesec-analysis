#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry entries[2];
    int count;
} Dictionary;

int compare(const void *a, const void *b) {
    Dictionary *dictA = (Dictionary *)a;
    Dictionary *dictB = (Dictionary *)b;
    return strcmp(dictA->entries[0].value, dictB->entries[0].value);
}

void sortDictionaries(Dictionary *dictionaries, int size) {
    qsort(dictionaries, size, sizeof(Dictionary), compare);
}

void printDictionary(Dictionary dict) {
    for (int i = 0; i < dict.count; i++) {
        printf("%s: %s\n", dict.entries[i].key, dict.entries[i].value);
    }
    printf("\n");
}

int main() {
    Dictionary dictionaries[3] = {
        {{.key = "name", .value = "Alice"}, {.key = "age", .value = "30"}},
        {{.key = "name", .value = "Bob"}, {.key = "age", .value = "25"}},
        {{.key = "name", .value = "Charlie"}, {.key = "age", .value = "35"}}
    };

    dictionaries[0].count = 2;
    dictionaries[1].count = 2;
    dictionaries[2].count = 2;

    sortDictionaries(dictionaries, 3);

    for (int i = 0; i < 3; i++) {
        printDictionary(dictionaries[i]);
    }

    return 0;
}