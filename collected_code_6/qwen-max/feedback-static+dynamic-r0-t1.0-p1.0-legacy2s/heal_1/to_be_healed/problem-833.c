#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *key;
    void *value;
    struct DictionaryEntry *next;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *head;
} Dictionary;

void dictionary_add(Dictionary *dict, char *key, void *value) {
    DictionaryEntry *newEntry = (DictionaryEntry *)malloc(sizeof(DictionaryEntry));
    newEntry->key = key;
    newEntry->value = value;
    /* Possible weaknesses found:
     *  assignment to 'struct DictionaryEntry *' from incompatible pointer type 'DictionaryEntry *' [-Wincompatible-pointer-types]
     */
    newEntry->next = dict->head;
    dict->head = newEntry;
}

char **dictionary_keys(Dictionary *dict, int *keysCount) {
    *keysCount = 0;
    DictionaryEntry *current = dict->head;
    while (current) {
        (*keysCount)++;
        /* Possible weaknesses found:
         *  assignment to 'DictionaryEntry *' from incompatible pointer type 'struct DictionaryEntry *' [-Wincompatible-pointer-types]
         */
        current = current->next;
    }
    if (*keysCount == 0) return NULL;
    
    char **keys = (char **)malloc(*keysCount * sizeof(char *));
    int index = 0;
    current = dict->head;
    while (current) {
        keys[index++] = current->key;
        /* Possible weaknesses found:
         *  assignment to 'DictionaryEntry *' from incompatible pointer type 'struct DictionaryEntry *' [-Wincompatible-pointer-types]
         */
        current = current->next;
    }
    return keys;
}

int main() {
    Dictionary dict = { .head = NULL };
    dictionary_add(&dict, "apple", (void*)"fruit");
    dictionary_add(&dict, "carrot", (void*)"vegetable");

    int keysCount;
    char **keys = dictionary_keys(&dict, &keysCount);
    
    for (int i = 0; i < keysCount; i++) {
        printf("%s\n", keys[i]);
        free(keys[i]);
    }
    free(keys);

    return 0;
}