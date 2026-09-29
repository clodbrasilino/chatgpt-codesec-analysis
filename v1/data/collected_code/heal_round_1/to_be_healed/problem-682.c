#include <stdio.h>

void multiplyLists(int list1[], int list2[], int result[], int size) {
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list2[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'list1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        result[i] = list1[i] * list2[i];
    }
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {2, 4, 6, 8, 10};
    int size = sizeof(list1) / sizeof(list1[0]);

    int result[size];

    multiplyLists(list1, list2, result, size);

    printf("Resultant list: ");
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'result[i]' is initialized [premium-bughuntingUninit]
         */
        printf("%d ", result[i]);
    }

    return 0;
}