#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_SIZE 256
#define DICTIONARY_SIZE 1000

typedef struct {
    char key[MAX_KEY_SIZE];
    int value;
} DictEntry;

typedef struct {
    DictEntry entries[DICTIONARY_SIZE];
    int size;
} Dictionary;

void insert(Dictionary *dict, const char *key, int value) {
    for (int i = 0; i < dict->size; i++) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            dict->entries[i].value += value;
            return;
        }
    }
    if (dict->size < DICTIONARY_SIZE) {
        strcpy(dict->entries[dict->size].key, key);
        dict->entries[dict->size].value = value;
        dict->size++;
    }
}

void combine(Dictionary *dict1, const Dictionary *dict2) {
    for (int i = 0; i < dict2->size; i++) {
        insert(dict1, dict2->entries[i].key, dict2->entries[i].value);
    }
}

int main() {
    Dictionary dict1 = { .size = 0 };
    Dictionary dict2 = { .size = 0 };

    insert(&dict1, "foo", 1);
    insert(&dict1, "bar", 2);
    
    insert(&dict2, "foo", 3);
    insert(&dict2, "baz", 4);

    combine(&dict1, &dict2);

    for (int i = 0; i < dict1.size; i++) {
        printf("%s: %d\n", dict1.entries[i].key, dict1.entries[i].value);
    }

    return 0;
}
