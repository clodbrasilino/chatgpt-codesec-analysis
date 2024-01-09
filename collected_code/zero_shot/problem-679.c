#include <stdio.h>
#include <string.h>

struct Dictionary {
    char key[100];
    int value;
};

int accessDictionaryElementByKeyIndex(struct Dictionary dict[], int size, char key[]) {
    for (int i = 0; i < size; i++) {
        if (strcmp(dict[i].key, key) == 0) {
            return dict[i].value;
        }
    }
    return -1; // Key not found
}