#include<stdio.h>

void removeDuplicates(int arr[], int n) {
    if (n == 0 || n == 1) {
        return;
    }

    int temp[n];
    int j = 0;

    for (int i = 0; i < n-1; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'arr[i+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] != arr[i+1]) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            temp[j++] = arr[i];
        }
    }

    /* Possible weaknesses found:
     *  Cannot determine that 'arr[n-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    temp[j++] = arr[n-1];

    for (int i = 0; i < j; i++) {
        arr[i] = temp[i];
    }

    printf("The modified list after removing consecutive duplicates is: \n");
    for (int i = 0; i < j; i++) {
        printf("%d ", arr[i]);
    }
}

int main() {
    int arr[] = {10, 20, 20, 30, 40, 40, 40, 50, 50};
    int n = sizeof(arr) / sizeof(arr[0]);

    removeDuplicates(arr, n);

    return 0;
}