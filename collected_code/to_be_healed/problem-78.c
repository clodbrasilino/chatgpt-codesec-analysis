#include <stdio.h>

int countSetBits(int num) {
    int count = 0;
  
    while (num) {
        count += num & 1;
        num >>= 1;
    }
  
    return count;
}

int countOddSetBits(int arr[], int n) {
    int result = 0;

    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (countSetBits(arr[i]) % 2 != 0) {
            result++;
        }
    }

    return result;
}

int main() {
    int array[] = {5, 10, 15, 20, 25};
    int size = sizeof(array) / sizeof(array[0]);

    int oddSetBits = countOddSetBits(array, size);

    printf("Number of integers with odd number of set bits: %d\n", oddSetBits);

    return 0;
}