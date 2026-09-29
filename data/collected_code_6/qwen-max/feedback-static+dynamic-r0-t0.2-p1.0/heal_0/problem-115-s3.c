#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int size;
} Dictionary;

bool areAllDictionariesEmpty(Dictionary *dicts, int count) {
    for (int i = 0; i < count; ++i) {
        if (dicts[i].size != 0) {
            return false;
        }
    }
    return true;
}

int main() {
    Dictionary dicts[] = {{0}, {0}, {0}};
    int count = sizeof(dicts) / sizeof(dicts[0]);
    
    if (areAllDictionariesEmpty(dicts, count)) {
        printf("All dictionaries are empty.\n");
    } else {
        printf("Not all dictionaries are empty.\n");
    }
    
    return 0;
}