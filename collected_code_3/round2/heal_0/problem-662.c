#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char key[MAX_SIZE];
    char value[MAX_SIZE];
} dict;

int compare(const void *a, const void *b) {
    dict *dictA = (dict *)a;
    dict *dictB = (dict *)b;
    return strcmp(dictA->key, dictB->key);
}

void sort_dict(dict *dictionary, int size) {
    qsort(dictionary, size, sizeof(dict), compare);
}

int main() {
    dict dictionary[3] = {{"apple", "fruit"}, {"carrot", "vegetable"}, {"banana", "fruit"}};
    int size = sizeof(dictionary) / sizeof(dictionary[0]);

    sort_dict(dictionary, size);

    for(int i = 0; i < size; i++) {
        printf("%s: %s\n", dictionary[i].key, dictionary[i].value);
    }

    return 0;
}