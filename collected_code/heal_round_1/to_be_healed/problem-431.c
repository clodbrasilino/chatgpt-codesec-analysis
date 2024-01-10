#include <stdio.h>
#include <stdbool.h>

bool findCommonElement(int list1[], int list2[], int size1, int size2) {
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'list2[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'list1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (list1[i] == list2[j]) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {6, 7, 8, 9, 10};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);

    if (findCommonElement(list1, list2, size1, size2)) {
        printf("Lists have at least one common element\n");
    } else {
        printf("Lists do not have any common elements\n");
    }

    return 0;
}