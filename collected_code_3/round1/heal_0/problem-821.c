#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char key[MAX_SIZE];
    int value;
} Dictionary;

void mergeDictionaries(Dictionary dict1[], int size1, Dictionary dict2[], int size2, Dictionary result[]) {
    int i;

    for(i = 0; i < size1; i++) {
        strcpy(result[i].key, dict1[i].key);
        result[i].value = dict1[i].value;
    }

    for(i = 0; i < size2; i++) {
        strcpy(result[i + size1].key, dict2[i].key);
        result[i + size1].value = dict2[i].value;
    }
}

int main() {
    Dictionary dict1[2] = {{"apple", 1}, {"banana", 2}};
    Dictionary dict2[2] = {{"cherry", 3}, {"date", 4}};
    Dictionary result[4];

    mergeDictionaries(dict1, 2, dict2, 2, result);

    for(int i = 0; i < 4; i++) {
        printf("%s: %d\n", result[i].key, result[i].value);
    }

    return 0;
}