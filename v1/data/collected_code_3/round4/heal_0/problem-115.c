#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int count;
} Dictionary;

bool areAllDictionariesEmpty(Dictionary* list, int size) {
    for(int i = 0; i < size; i++) {
        if(list[i].count != 0) {
            return false;
        }
    }
    return true;
}

int main() {
    Dictionary list[3] = {{0}, {0}, {0}};
    if(areAllDictionariesEmpty(list, 3)) {
        printf("All dictionaries are empty.\n");
    } else {
        printf("Not all dictionaries are empty.\n");
    }
    return 0;
}