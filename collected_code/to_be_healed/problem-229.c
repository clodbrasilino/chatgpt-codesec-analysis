#include <stdio.h>

void rearrange(int arr[], int n) {
    int i, j, temp;
    j = 0;
    for (i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] < 0) {
            if (i != j) {
                /* Possible weaknesses found:
                 *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
                temp = arr[i];
                /* Possible weaknesses found:
                 *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
                arr[i] = arr[j];
                arr[j] = temp;
            }
            j++;
        }
    }
}

int main() {
    int arr[] = {-2, 4, -6, 8, -10, 12};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i;
    rearrange(arr, n);
    printf("Array after rearrangement: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}