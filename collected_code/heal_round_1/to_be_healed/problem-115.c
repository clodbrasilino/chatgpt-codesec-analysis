#include <stdio.h>

int checkAllDictionariesEmpty(int** list, int size) {
    for(int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i][0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if(list[i][0] != 0)
            return 0;
    }
    return 1;
}

int main() {
    // Example usage
    int dict1[] = {0};
    int dict2[] = {0};
    int dict3[] = {1};

    int* list[] = {dict1, dict2, dict3};
    int size = sizeof(list) / sizeof(list[0]);

    if(checkAllDictionariesEmpty(list, size))
        printf("All dictionaries are empty\n");
    else
        printf("Not all dictionaries are empty\n");

    return 0;
}