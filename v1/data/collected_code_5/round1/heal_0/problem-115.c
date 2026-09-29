#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DICTIONARY_SIZE 20
#define KEY_SIZE 100
#define DICTIONARY_LIST_SIZE 10

struct dictionary {
    char keys[DICTIONARY_SIZE][KEY_SIZE];
    int values[DICTIONARY_SIZE];
    int size;
};

void initDictionary(struct dictionary *dict) {
    dict->size = 0;
}

void addElement(struct dictionary *dict, char* key, int value) {
    strcpy(dict->keys[dict->size], key);
    dict->values[dict->size] = value;
    dict->size++;
}

int isEmpty(struct dictionary *dict) {
    return dict->size == 0;
}

int areAllDictionariesEmpty(struct dictionary *dictList) {
    for (int i = 0; i < DICTIONARY_LIST_SIZE; i++) {
        if (!isEmpty(&dictList[i])) {
            return 0;
        }
    }
    return 1;
}

int main() {
    struct dictionary dictList[DICTIONARY_LIST_SIZE];

    for (int i = 0; i < DICTIONARY_LIST_SIZE; i++) {
        initDictionary(&dictList[i]);
    }

    if (areAllDictionariesEmpty(dictList)) {
        printf("All dictionaries are empty\n");
    } else {
        printf("Not all dictionaries are empty\n");
    }

    addElement(&dictList[0], "Hello", 1);

    if (areAllDictionariesEmpty(dictList)) {
        printf("All dictionaries are empty\n");
    } else {
        printf("Not all dictionaries are empty\n");
    }

    return 0;
}