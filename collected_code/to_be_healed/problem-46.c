#include <stdio.h>

int areAllNumbersDifferent(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (arr[i] == arr[j]) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5}; // Replace with your own array

    int size = sizeof(arr) / sizeof(arr[0]);
    int result = areAllNumbersDifferent(arr, size);

    if (result) {
        printf("All numbers are different.\n");
    } else {
        printf("There are duplicate numbers.\n");
    }

    return 0;
}
