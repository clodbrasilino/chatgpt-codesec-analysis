#include <stdio.h>
#include <string.h>

#define SIZE 100

void mergeDictionaries(const char dict1[][SIZE], int size1, const char dict2[][SIZE], int size2, char result[][SIZE]) {
    int i, j;

    for (i = 0; i < size1; i++) {
        /* Possible weaknesses found:
         *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
         */
        strncpy(result[i], dict1[i], SIZE);
    }

    for (j = 0; j < size2; j++) {
        /* Possible weaknesses found:
         *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
         */
        strncpy(result[i+j], dict2[j], SIZE);
    }
}

int main() {
    const char dict1[][SIZE] = {"key1: value1", "key2: value2"};
    const int size1 = sizeof(dict1) / sizeof(dict1[0]);

    const char dict2[][SIZE] = {"key3: value3", "key4: value4"};
    const int size2 = sizeof(dict2) / sizeof(dict2[0]);

    if((size1+size2)>SIZE){
        printf("%s\n","Size limit exceeded");
        return 0;
    }

    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char result[size1+size2][SIZE];

    mergeDictionaries(dict1, size1, dict2, size2, result);
    const int mergedSize = size1 + size2;

    for (int i = 0; i < mergedSize; i++) {
        printf("%s\n", result[i]);
    }
   
    return 0;
}