#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    int value;
} DictItem;

typedef struct {
    DictItem* items;
    size_t size;
} Dictionary;

typedef struct {
    int* values;
    size_t size;
} UniqueValues;

UniqueValues* extractUniqueValues(const Dictionary* dict) {
    if (dict == NULL || dict->items == NULL || dict->size == 0) {
        return NULL;
    }

    UniqueValues* uniqueVals = (UniqueValues*)malloc(sizeof(UniqueValues));
    if (uniqueVals == NULL) {
        return NULL;
    }

    uniqueVals->values = (int*)malloc(dict->size * sizeof(int));
    if (uniqueVals->values == NULL) {
        free(uniqueVals);
        return NULL;
    }

    uniqueVals->size = 0;

    for (size_t i = 0; i < dict->size; i++) {
        int val = dict->items[i].value;
        int isUnique = 1;
        for (size_t j = 0; j < uniqueVals->size; j++) {
            if (uniqueVals->values[j] == val) {
                isUnique = 0;
                break;
            }
        }
        if (isUnique) {
            uniqueVals->values[uniqueVals->size] = val;
            uniqueVals->size++;
        }
    }

    int* temp = (int*)realloc(uniqueVals->values, uniqueVals->size * sizeof(int));
    if (temp != NULL || uniqueVals->size == 0) {
        uniqueVals->values = temp;
    }

    return uniqueVals;
}

void freeUniqueValues(UniqueValues* uv) {
    if (uv != NULL) {
        if (uv->values != NULL) {
            free(uv->values);
        }
        free(uv);
    }
}

int main(void) {
    DictItem items[] = {
        {"A", 10},
        {"B", 20},
        {"C", 10},
        {"D", 30},
        {"E", 20}
    };
    
    Dictionary dict = {items, 5};

    for (size_t i = 0; i < dict.size; i++) {
        printf("%s: %d\n", dict.items[i].key, dict.items[i].value);
    }

    UniqueValues* uniqueParams = extractUniqueValues(&dict);
    
    if (uniqueParams != NULL) {
        for (size_t i = 0; i < uniqueParams->size; i++) {
            printf("%d\n", uniqueParams->values[i]);
        }
        freeUniqueValues(uniqueParams);
    }

    return 0;
}