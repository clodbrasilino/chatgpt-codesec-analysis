#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple key;
    int value;
} DictionaryItem;

int tupleProduct(Tuple tuple) {
    return tuple.first * tuple.second;
}

int compare(const void *a, const void *b) {
    DictionaryItem *item1 = (DictionaryItem *)a;
    DictionaryItem *item2 = (DictionaryItem *)b;

    int product1 = tupleProduct(item1->key);
    int product2 = tupleProduct(item2->key);

    if (product1 < product2) {
        return -1;
    } else if (product1 > product2) {
        return 1;
    } else {
        return 0;
    }
}

void sortDictionary(DictionaryItem *dictionary, int size) {
    qsort(dictionary, size, sizeof(DictionaryItem), compare);
}

int main() {
    DictionaryItem dictionary[] = {
        { {2, 3}, 10 },
        { {5, 4}, 12 },
        { {1, 7}, 15 },
        { {3, 3}, 20 }
    };
    int size = sizeof(dictionary) / sizeof(DictionaryItem);

    sortDictionary(dictionary, size);

    for (int i = 0; i < size; i++) {
        printf("{{%d, %d}, %d}\n", dictionary[i].key.first, dictionary[i].key.second, dictionary[i].value);
    }

    return 0;
}