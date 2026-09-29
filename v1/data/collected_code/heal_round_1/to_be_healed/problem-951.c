#include <stdio.h>

int findMaxIndices(int list1[], int list2[], int len) {
    int maxIndex = -1;
    
    for (int i = 0; i < len; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list2[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'list1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (list1[i] == list2[i] && list1[i] > maxIndex) {
            /* Possible weaknesses found:
             *  Cannot determine that 'list1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            maxIndex = list1[i];
        }
    }
    
    return maxIndex;
}

int main() {
    int list1[] = {2, 5, 3, 9, 6};
    int list2[] = {1, 3, 8, 5, 6};
    int len = sizeof(list1) / sizeof(list1[0]);
    
    int maxIndex = findMaxIndices(list1, list2, len);
    
    printf("Maximum similar index: %d\n", maxIndex);
    
    return 0;
}