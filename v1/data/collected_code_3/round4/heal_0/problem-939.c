#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 3

typedef struct {
    char key[50];
    int value;
} Dictionary;

int compare(const void *a, const void *b) {
    return strcmp(((Dictionary *)a)->key, ((Dictionary *)b)->key);
}

void sortDictionary(Dictionary *dict, int size) {
    qsort(dict, size, sizeof(Dictionary), compare);
}

int main() {
    Dictionary dict[SIZE] = {
        {"apple", 1},
        {"banana", 2},
        {"cherry", 3}
    };

    sortDictionary(dict, SIZE);

    for(int i = 0; i < SIZE; i++) {
        printf("%s: %d\n", dict[i].key, dict[i].value);
    }

    return 0;
}