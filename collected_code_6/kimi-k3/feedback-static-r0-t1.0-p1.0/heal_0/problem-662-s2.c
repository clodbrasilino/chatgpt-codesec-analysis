#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    int value;
} DictEntry;

int compare(const void *a, const void *b) {
    return ((DictEntry *)a)->value - ((DictEntry *)b)->value;
}

void sort_dict(DictEntry *dict, size_t size) {
    qsort(dict, size, sizeof(DictEntry), compare);
}

int main() {
    DictEntry dict[] = {
        {"apple", 5},
        {"banana", 2},
        {"cherry", 8},
        {"date", 1}
    };
    size_t size = sizeof(dict) / sizeof(dict[0]);

    sort_dict(dict, size);

    for (size_t i = 0; i < size; i++) {
        printf("%s: %d\n", dict[i].key, dict[i].value);
    }

    return 0;
}