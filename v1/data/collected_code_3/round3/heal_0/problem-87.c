#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char key[MAX_SIZE];
    char value[MAX_SIZE];
} Dictionary;

void mergeDictionaries(Dictionary dict1[], int size1, Dictionary dict2[], int size2, Dictionary dict3[], int size3, Dictionary result[]) {
    int i, j = 0;

    for(i = 0; i < size1; i++) {
        strcpy(result[j].key, dict1[i].key);
        strcpy(result[j].value, dict1[i].value);
        j++;
    }

    for(i = 0; i < size2; i++) {
        strcpy(result[j].key, dict2[i].key);
        strcpy(result[j].value, dict2[i].value);
        j++;
    }

    for(i = 0; i < size3; i++) {
        strcpy(result[j].key, dict3[i].key);
        strcpy(result[j].value, dict3[i].value);
        j++;
    }
}

int main() {
    Dictionary dict1[2] = {{"key1", "value1"}, {"key2", "value2"}};
    Dictionary dict2[2] = {{"key3", "value3"}, {"key4", "value4"}};
    Dictionary dict3[2] = {{"key5", "value5"}, {"key6", "value6"}};

    Dictionary result[6];

    mergeDictionaries(dict1, 2, dict2, 2, dict3, 2, result);

    for(int i = 0; i < 6; i++) {
        printf("Key: %s Value: %s\n", result[i].key, result[i].value);
    }

    return 0;
}