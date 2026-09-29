#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int count;
} Dictionary;

int areAllDictionariesEmpty(Dictionary** dictList, int size) {
    for(int i = 0; i < size; i++) {
        if(dictList[i]->count != 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int size = 3;
    Dictionary** dictList = malloc(size * sizeof(Dictionary*));
    if(dictList == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for(int i = 0; i < size; i++) {
        dictList[i] = malloc(sizeof(Dictionary));
        if(dictList[i] == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }

        dictList[i]->count = 0;
    }

    if(areAllDictionariesEmpty(dictList, size)) {
        printf("All dictionaries are empty\n");
    } else {
        printf("Not all dictionaries are empty\n");
    }

    for(int i = 0; i < size; i++) {
        free(dictList[i]);
    }
    free(dictList);

    return 0;
}