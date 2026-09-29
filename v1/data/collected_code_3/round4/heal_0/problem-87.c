#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

typedef struct {
    char key[SIZE];
    char value[SIZE];
} dict;

void mergeDicts(dict *dict1, int size1, dict *dict2, int size2, dict *dict3, int size3, dict *result) {
    int i, index = 0;

    for(i = 0; i < size1; i++) {
        strcpy(result[index].key, dict1[i].key);
        strcpy(result[index].value, dict1[i].value);
        index++;
    }

    for(i = 0; i < size2; i++) {
        strcpy(result[index].key, dict2[i].key);
        strcpy(result[index].value, dict2[i].value);
        index++;
    }

    for(i = 0; i < size3; i++) {
        strcpy(result[index].key, dict3[i].key);
        strcpy(result[index].value, dict3[i].value);
        index++;
    }
}

int main() {
    dict dict1[2] = {{"key1", "value1"}, {"key2", "value2"}};
    dict dict2[2] = {{"key3", "value3"}, {"key4", "value4"}};
    dict dict3[2] = {{"key5", "value5"}, {"key6", "value6"}};

    dict result[6];
    mergeDicts(dict1, 2, dict2, 2, dict3, 2, result);

    for(int i = 0; i < 6; i++) {
        printf("Key: %s Value: %s\n", result[i].key, result[i].value);
    }

    return 0;
}