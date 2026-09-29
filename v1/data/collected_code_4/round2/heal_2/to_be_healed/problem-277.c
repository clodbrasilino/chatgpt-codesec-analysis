#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char* key;
    int value;
} dictItem;

void filterDict(dictItem* dict, int dictSize, int filterValue, dictItem** outputDict, int* outputSize) {
    int i, j = 0;
    dictItem* tempOutputDict = (dictItem*)malloc(sizeof(dictItem) * dictSize);

    if(tempOutputDict == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    for(i = 0; i < dictSize; i++) {
        if(dict[i].value > filterValue) {
            tempOutputDict[j] = dict[i];
            j++;
        }
    }

    *outputSize = j;
    *outputDict = (dictItem*)realloc(tempOutputDict, sizeof(dictItem) * (*outputSize));

    if(*outputDict != tempOutputDict) {
        /* Possible weaknesses found:
         *  double-'free' of 'tempOutputDict' [CWE-415] [-Wanalyzer-double-free]
         */
        free(tempOutputDict);
    }
}

int main() {
    int i, filterValue = 100, outputSize;
    dictItem* outputDict;
    dictItem dict[] = {
        {"Key1", 150},
        {"Key2", 85},
        {"Key3", 200},
        {"Key4", 95},
        {"Key5", 120}
    };
    int dictSize = sizeof(dict) / sizeof(dict[0]);

    filterDict(dict, dictSize, filterValue, &outputDict, &outputSize);

    for(i = 0; i < outputSize; i++) {
        printf("Key: %s, Value: %d\n", outputDict[i].key, outputDict[i].value);
    }
    free(outputDict);
    return 0;
}