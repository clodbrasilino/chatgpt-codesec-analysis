#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    void *value;
} Pair;

typedef struct {
    Pair *elements;
    int size;
} Dictionary;

void freeDictionary(Dictionary *dict) {
    for (int i = 0; i < dict->size; i++) {
        free(dict->elements[i].key);
    }
    free(dict->elements);
}

Dictionary* createDictionary(int size) {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (!dict) return NULL;

    dict->elements = (Pair*)calloc(size, sizeof(Pair));
    if (!dict->elements) {
        free(dict);
        return NULL;
    }

    dict->size = size;
    return dict;
}

void addElement(Dictionary *dict, char *key, void *value) {
    if (dict->size <= 0) return;

    dict->elements[dict->size - 1].key = strdup(key);
    dict->elements[dict->size - 1].value = value;

    dict->size--;
}

Dictionary* mergeDictionaries(Dictionary *dict1, Dictionary *dict2) {
    Dictionary *result = createDictionary(dict1->size + dict2->size);
    if (!result) return NULL;

    for (int i = 0; i < dict1->size; i++) {
        addElement(result, dict1->elements[i].key, dict1->elements[i].value);
    }

    for (int i = 0; i < dict2->size; i++) {
        addElement(result, dict2->elements[i].key, dict2->elements[i].value);
    }

    return result;
}

void printDictionary(Dictionary *dict, void (*printValue)(void*)) {
    for (int i = 0; i < dict->size; i++) {
        printf("%s: ", dict->elements[i].key);
        printValue(dict->elements[i].value);
        printf("\n");
    }
}

void printInt(void *ptr) {
    printf("%d", *(int*)ptr);
}

int main() {
    Dictionary *dict1 = createDictionary(2);
    Dictionary *dict2 = createDictionary(2);

    int a1 = 10;
    int a2 = 20;
    int b1 = 30;
    int b2 = 40;

    addElement(dict1, "a1", &a1);
    addElement(dict1, "a2", &a2);
    addElement(dict2, "b1", &b1);
    addElement(dict2, "b2", &b2);

    Dictionary *mergedDict = mergeDictionaries(dict1, dict2);
    if (mergedDict) {
        printDictionary(mergedDict, printInt);
        freeDictionary(mergedDict);
    }

    freeDictionary(dict1);
    freeDictionary(dict2);

    return 0;
}