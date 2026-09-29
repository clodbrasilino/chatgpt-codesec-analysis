#include <stdio.h>

void findIntersection(int arr1[], int size1, int arr2[], int size2) {
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr2[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (arr1[i] == arr2[j]) {
                /* Possible weaknesses found:
                 *  Cannot determine that 'arr1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
                printf("%d ", arr1[i]);
                break;
            }
        }
    }
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {4, 5, 6, 7, 8};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);

    findIntersection(arr1, size1, arr2, size2);

    return 0;
}