#include <stdio.h>

int findDuplicate(int arr[], int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (arr[i] == arr[j]) {
                /* Possible weaknesses found:
                 *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
                return arr[i];
            }
        }
    }
    return -1;
}

int main() {
    int arr[] = {4, 7, 2, 6, 2, 7, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    int duplicate = findDuplicate(arr, size);

    if (duplicate != -1) {
        printf("First duplicate element: %d\n", duplicate);
    } else {
        printf("No duplicate elements found.\n");
    }
    return 0;
}