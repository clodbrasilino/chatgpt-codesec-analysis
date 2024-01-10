#include <stdio.h>

void merge(int list1[], int size1, int list2[], int size2, int mergedList[]) {
    int i = 0, j = 0, k = 0;
    
    while (i < size1 && j < size2) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list2[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'list1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (list1[i] < list2[j]) {
            /* Possible weaknesses found:
             *  Cannot determine that 'list1[i++]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            mergedList[k++] = list1[i++];
        } else {
            /* Possible weaknesses found:
             *  Cannot determine that 'list2[j++]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            mergedList[k++] = list2[j++];
        }
    }
    
    while (i < size1) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list1[i++]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        mergedList[k++] = list1[i++];
    }
    
    while (j < size2) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list2[j++]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        mergedList[k++] = list2[j++];
    }
}

int main() {
    int list1[] = {1, 4, 6, 8, 10};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    
    int list2[] = {2, 3, 5, 7, 9};
    int size2 = sizeof(list2) / sizeof(list2[0]);
    
    int mergedList[size1 + size2];
    
    merge(list1, size1, list2, size2, mergedList);
    
    printf("Merged List: ");
    for (int i = 0; i < size1 + size2; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'mergedList[i]' is initialized [premium-bughuntingUninit]
         */
        printf("%d ", mergedList[i]);
    }
    printf("\n");
    
    return 0;
}