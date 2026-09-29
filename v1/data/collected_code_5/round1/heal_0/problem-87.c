#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

typedef struct {
    char key[MAX];
    char value[MAX];
} Dictionary;

void mergeDict(Dictionary dict1[], Dictionary dict2[], Dictionary dict3[], int size1, int size2, int size3, Dictionary result[]) {
    int i, j = 0;

    for (i = 0; i < size1; i++) {
        result[j] = dict1[i];
        j++;
    }

    for (i = 0; i < size2; i++) {
        result[j] = dict2[i];
        j++;
    }

    for (i = 0; i < size3; i++) {
        result[j] = dict3[i];
        j++;
    }
}

void printDict(Dictionary dict[], int size) {
    int i;

    for(i = 0; i < size; i++) {
        printf("{ Key: %s, Value: %s }\n", dict[i].key, dict[i].value);
    }
}

int main() {
    Dictionary dict1[2] = {{"key1", "value1"}, {"key2", "value2"}};
    Dictionary dict2[2] = {{"key3", "value3"}, {"key4", "value4"}};
    Dictionary dict3[2] = {{"key5", "value5"}, {"key6", "value6"}};
    Dictionary result[6];

    mergeDict(dict1, dict2, dict3, 2, 2, 2, result);
    printDict(result, 6);

    return 0;
}