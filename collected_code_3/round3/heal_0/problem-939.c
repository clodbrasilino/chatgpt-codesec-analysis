#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    int value;
} Dictionary;

int compare(const void* a, const void* b) {
    Dictionary* dictA = (Dictionary*) a;
    Dictionary* dictB = (Dictionary*) b;
    return dictA->value - dictB->value;
}

void sortDictionary(Dictionary* dict, int n) {
    qsort(dict, n, sizeof(Dictionary), compare);
}

int main() {
    Dictionary dict[3] = {{"Apple", 20}, {"Banana", 10}, {"Cherry", 30}};
    int n = sizeof(dict) / sizeof(dict[0]);

    sortDictionary(dict, n);

    for(int i = 0; i < n; i++) {
        printf("%s: %d\n", dict[i].key, dict[i].value);
    }

    return 0;
}