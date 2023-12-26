#include <stdio.h>

void mergeDictionaries(const int dict1[], int size1, const int dict2[], int size2, const int dict3[], int size3, int result[]){
    int i, j, k;
    
    for (i = 0; i < size1; i++) {
        result[i] = dict1[i];
    }
    
    j = size1;
    for (i = 0; i < size2; i++) {
        result[j] = dict2[i];
        j++;
    }
    
    k = j;
    for (i = 0; i < size3; i++) {
        result[k] = dict3[i];
        k++;
    }
}

int main() {
    int dict1[] = {1, 2, 3};
    int dict2[] = {4, 5, 6};
    int dict3[] = {7, 8, 9};
    
    int size1 = sizeof(dict1) / sizeof(dict1[0]);
    int size2 = sizeof(dict2) / sizeof(dict2[0]);
    int size3 = sizeof(dict3) / sizeof(dict3[0]);
    
    int result[size1 + size2 + size3];
    
    mergeDictionaries(dict1, size1, dict2, size2, dict3, size3, result);
    
    int resultSize = size1 + size2 + size3;
    int i;
    for (i = 0; i < resultSize; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'result[i]' is initialized [premium-bughuntingUninit]
         */
        printf("%d ", result[i]);
    }
    
    return 0;
}