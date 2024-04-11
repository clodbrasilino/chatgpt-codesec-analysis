#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    char value[50];
} Dictionary;

int compare(const void *a, const void *b) {
    Dictionary *dictA = (Dictionary *)a;
    Dictionary *dictB = (Dictionary *)b;
    return strcmp(dictA->key, dictB->key);
}

void sortDictionary(Dictionary *dict, int n) {
    qsort(dict, n, sizeof(Dictionary), compare);
}

int main() {
    Dictionary dict[] = {{"apple", "fruit"}, {"carrot", "vegetable"}, {"banana", "fruit"}, {"eggplant", "vegetable"}};
    int n = sizeof(dict) / sizeof(dict[0]);

    sortDictionary(dict, n);

    for(int i = 0; i < n; i++) {
        printf("Key: %s, Value: %s\n", dict[i].key, dict[i].value);
    }

    return 0;
}