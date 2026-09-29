#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int countUnequalPairs(int arr[], int n) {
    int count = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (arr[i] != arr[j]) {
                ++count;
            }
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = countUnequalPairs(arr, n);
    printf("Number of unequal element pairs: %d\n", result);
    return 0;
}