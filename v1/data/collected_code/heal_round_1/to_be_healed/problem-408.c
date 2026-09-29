#include <stdio.h>

// Function to find k number of pairs from two arrays
void findPairs(int arr1[], int size1, int arr2[], int size2, int k) {
    int count = 0;
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr2[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            printf("(%d, %d)\n", arr1[i], arr2[j]);
            count++;
            if (count == k) {
                return;
            }
        }
    }
}

int main() {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};
    int k = 3;

    findPairs(arr1, sizeof(arr1) / sizeof(arr1[0]), arr2, sizeof(arr2) / sizeof(arr2[0]), k);

    return 0;
}