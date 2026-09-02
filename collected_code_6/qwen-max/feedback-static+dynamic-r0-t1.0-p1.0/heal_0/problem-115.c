#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int size;
} Dictionary;

bool areAllDictionariesEmpty(Dictionary *dictionaries, int count) {
    for (int i = 0; i < count; i++) {
        if (dictionaries[i].size != 0) {
            return false;
        }
    }
    return true;
}

int main() {
    Dictionary dictionaries[] = {{0}, {0}, {0}};
    int count = sizeof(dictionaries) / sizeof(dictionaries[0]);
    bool result = areAllDictionariesEmpty(dictionaries, count);
    
    if (result) {
        printf("All dictionaries are empty.\n");
    } else {
        printf("Not all dictionaries are empty.\n");
    }
    
    return 0;
}