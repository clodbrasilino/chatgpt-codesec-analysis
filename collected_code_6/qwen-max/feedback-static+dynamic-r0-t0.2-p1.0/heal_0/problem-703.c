#include <stdio.h>
#include <stdbool.h>

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    int size;
} Dictionary;

bool isKeyPresent(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->size; ++i) {
        if (dict->entries[i].key != NULL && key != NULL && strcmp(dict->entries[i].key, key) == 0) {
            return true;
        }
    }
    return false;
}

int main() {
    DictionaryEntry entries[] = {
        {"one", "1"},
        {"two", "2"},
        {"three", "3"}
    };
    Dictionary dict = {entries, 3};

    const char *keyToFind = "two";
    if (isKeyPresent(&dict, keyToFind)) {
        printf("Key '%s' is present in the dictionary.\n", keyToFind);
    } else {
        printf("Key '%s' is not present in the dictionary.\n", keyToFind);
    }

    return 0;
}