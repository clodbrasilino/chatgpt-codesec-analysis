#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    char value[50];
} KeyValuePair;

KeyValuePair* mergeDicts(KeyValuePair* dict1, int size1, KeyValuePair* dict2, int size2, int* newSize) {
    *newSize = size1 + size2;
    KeyValuePair* mergedDict = (KeyValuePair*)malloc((*newSize) * sizeof(KeyValuePair));

    for(int i = 0; i < size1; i++) {
        strcpy(mergedDict[i].key, dict1[i].key);
        strcpy(mergedDict[i].value, dict1[i].value);
    }

    for(int i = 0; i < size2; i++) {
        strcpy(mergedDict[i + size1].key, dict2[i].key);
        strcpy(mergedDict[i + size1].value, dict2[i].value);
    }

    return mergedDict;
}

int main() {
    KeyValuePair dict1[2] = {{"key1", "value1"}, {"key2", "value2"}};
    KeyValuePair dict2[2] = {{"key3", "value3"}, {"key4", "value4"}};

    int newSize;
    KeyValuePair* mergedDict = mergeDicts(dict1, 2, dict2, 2, &newSize);

    for(int i = 0; i < newSize; i++) {
        printf("Key: %s, Value: %s\n", mergedDict[i].key, mergedDict[i].value);
    }

    free(mergedDict);

    return 0;
}