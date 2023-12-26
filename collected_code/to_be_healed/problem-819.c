#include <stdio.h>

void countConsecutiveDuplicates(int arr[], int size) {
    int count = 0;

    for (int i = 1; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'arr[i-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] == arr[i - 1]) {  // Check if current element is equal to its previous element
            count++;
        }
    }

    printf("Frequency of consecutive duplicate elements: %d\n", count);
}

int main() {
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    int size = sizeof(arr) / sizeof(arr[0]);

    countConsecutiveDuplicates(arr, size);

    return 0;
}