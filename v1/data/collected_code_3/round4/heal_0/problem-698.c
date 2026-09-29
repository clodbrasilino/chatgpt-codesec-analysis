#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key1;
    int key2;
    int value;
} Tuple;

int compare(const void *a, const void *b) {
    Tuple *tupleA = (Tuple *)a;
    Tuple *tupleB = (Tuple *)b;
    return (tupleA->key1 * tupleA->key2) - (tupleB->key1 * tupleB->key2);
}

void sortDictionary(Tuple *dictionary, int size) {
    qsort(dictionary, size, sizeof(Tuple), compare);
}

int main() {
    Tuple dictionary[] = {
        {2, 3, 6},
        {1, 2, 2},
        {4, 5, 20},
        {3, 2, 6}
    };

    int size = sizeof(dictionary) / sizeof(Tuple);

    sortDictionary(dictionary, size);

    for(int i = 0; i < size; i++) {
        printf("Key1: %d, Key2: %d, Value: %d\n", dictionary[i].key1, dictionary[i].key2, dictionary[i].value);
    }

    return 0;
}