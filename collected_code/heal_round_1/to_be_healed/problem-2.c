#include <stdio.h>

void findSimilarElements(int list1[], int list2[], int size1, int size2) {
    printf("Similar elements: ");
    
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'list2[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'list1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (list1[i] == list2[j]) {
                /* Possible weaknesses found:
                 *  Cannot determine that 'list1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
                printf("%d ", list1[i]);
                break;
            }
        }
    }
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {4, 5, 6, 7, 8};
    int size1 = sizeof(list1) / sizeof(int);
    int size2 = sizeof(list2) / sizeof(int);
    
    findSimilarElements(list1, list2, size1, size2);
    
    return 0;
}