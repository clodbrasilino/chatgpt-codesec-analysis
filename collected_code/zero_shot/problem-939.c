#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Dictionary;

int compare(const void* a, const void* b) {
    const Dictionary* dictA = (const Dictionary*)a;
    const Dictionary* dictB = (const Dictionary*)b;

    return dictA->key - dictB->key;
}

void sortDictionaries(Dictionary* dicts, int numDicts) {
    qsort(dicts, numDicts, sizeof(Dictionary), compare);
}

int main() {
    // example usage
    Dictionary dicts[] = { {3, 30}, {1, 10}, {2, 20} };
    int numDicts = sizeof(dicts) / sizeof(dicts[0]);

    sortDictionaries(dicts, numDicts);

    for (int i = 0; i < numDicts; i++) {
        printf("{%d, %d}\n", dicts[i].key, dicts[i].value);
    }

    return 0;
}