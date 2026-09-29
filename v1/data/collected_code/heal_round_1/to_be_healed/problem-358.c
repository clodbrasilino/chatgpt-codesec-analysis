#include <stdio.h>

void moduloDivision(int list1[], int list2[], int size) {
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list2[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'list1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        printf("%d ", list1[i] % list2[i]);
    }
}

int main() {
    int list1[] = {10, 20, 30, 40, 50};
    int list2[] = {4, 7, 3, 8, 5};
    int size = sizeof(list1) / sizeof(list1[0]);
    
    moduloDivision(list1, list2, size);
    
    return 0;
}