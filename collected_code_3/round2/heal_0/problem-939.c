#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DICTS 100
#define MAX_KEY_LENGTH 50
#define MAX_VALUE_LENGTH 50

typedef struct {
    char key[MAX_KEY_LENGTH];
    char value[MAX_VALUE_LENGTH];
} Dictionary;

int compare(const void* a, const void* b) {
    Dictionary* dictA = (Dictionary*) a;
    Dictionary* dictB = (Dictionary*) b;
    return strcmp(dictA->key, dictB->key);
}

void sortDictionaries(Dictionary* dicts, int size) {
    qsort(dicts, size, sizeof(Dictionary), compare);
}

int main() {
    Dictionary dicts[MAX_DICTS];
    int size = 0;

    strcpy(dicts[size].key, "z");
    strcpy(dicts[size].value, "1");
    size++;

    strcpy(dicts[size].key, "a");
    strcpy(dicts[size].value, "2");
    size++;

    strcpy(dicts[size].key, "m");
    strcpy(dicts[size].value, "3");
    size++;

    sortDictionaries(dicts, size);

    for(int i = 0; i < size; i++) {
        printf("%s: %s\n", dicts[i].key, dicts[i].value);
    }

    return 0;
}