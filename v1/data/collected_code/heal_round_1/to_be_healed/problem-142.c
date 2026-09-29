#include <stdio.h>

int countSamePair(int list1[], int list2[], int list3[], int size) {
    int count = 0;
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'list2[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'list1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (list1[i] == list2[j]) {
                for (int k = 0; k < size; k++) {
                    /* Possible weaknesses found:
                     *  Cannot determine that 'list3[k]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                     *  Cannot determine that 'list1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                     */
                    if (list1[i] == list3[k]) {
                        count++;
                    }
                }
            }
        }
    }
    
    return count;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {2, 3, 4, 5, 6};
    int list3[] = {3, 4, 5, 6, 7};
    int size = sizeof(list1) / sizeof(list1[0]);
    
    int result = countSamePair(list1, list2, list3, size);
    
    printf("Number of same pairs: %d\n", result);
    
    return 0;
}