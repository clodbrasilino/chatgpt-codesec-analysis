#include <stdio.h>

int countPairs(int arr[], int n, int sum) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (arr[i] + arr[j] == sum)
                count++;
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 5, 7, -1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = 6;
    int pairs = countPairs(arr, n, sum);
    printf("Number of pairs whose sum is equal to %d: %d\n", sum, pairs);
    return 0;
}