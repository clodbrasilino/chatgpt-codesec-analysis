#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    char **keys;
    char **values;
    int size;
} Dictionary;

bool isDictionaryEmpty(Dictionary *dict) {
    return dict->size == 0;
}

bool areAllDictionariesEmpty(Dictionary **dicts, int dictCount) {
    for (int i = 0; i < dictCount; i++) {
        if (!isDictionaryEmpty(dicts[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    Dictionary *dict1 = malloc(sizeof(Dictionary));
    if(dict1 == NULL) return -1;
    dict1->size = 0;

    Dictionary *dict2 = malloc(sizeof(Dictionary));
    if(dict2 == NULL) {
        free(dict1);
        return -1;
    }
    dict2->size = 0;

    Dictionary *dicts[] = {dict1, dict2};

    if (areAllDictionariesEmpty(dicts, 2)) {
        printf("All dictionaries are empty\n");
    } else {
        printf("Not all dictionaries are empty\n");
    }

    free(dict1);
    free(dict2);

    return 0;
}