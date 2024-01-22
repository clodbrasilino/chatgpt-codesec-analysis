#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 100

void mergeDictionaries(const char dict1[][SIZE], int size1, const char dict2[][SIZE], int size2, char result[][SIZE]) {
    int i, j;

    for (i = 0; i < size1; i++) {
        strncpy(result[i], dict1[i], SIZE - 1);
    }

    for (j = 0; j < size2; j++) {
        strncpy(result[i+j], dict2[j], SIZE - 1);
    }
}

bool isSizeExceeded(int size1, int size2){
    if((size1+size2)>SIZE){
        printf("%s\n","Size limit exceeded");
        return true;
    }
    return false;
}

int main() {
    const char dict1[][SIZE] = {"key1: value1", "key2: value2"};
    const int size1 = sizeof(dict1) / sizeof(dict1[0]);

    const char dict2[][SIZE] = {"key3: value3", "key4: value4"};
    const int size2 = sizeof(dict2) / sizeof(dict2[0]);

    if(isSizeExceeded(size1, size2)){
        return 0;
    }

    char result[size1+size2][SIZE];

    mergeDictionaries(dict1, size1, dict2, size2, result);

    const int mergedSize = size1 + size2;

    for (int i = 0; i < mergedSize; i++) {
        printf("%s\n", result[i]);
    }
   
    return 0;
}