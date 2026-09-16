#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int findSmallestMissing(int arr[], int n) {
    bool present[n+1];
    for (int i = 0; i <= n; i++) {
        present[i] = false;
    }
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0 && arr[i] <= n) {
            present[arr[i]] = true;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!present[i]) {
            return i;
        }
    }
    return n + 1;
}

int main() {
    int arr[] = {3, 4, -1, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("The smallest missing number is %d\n", findSmallestMissing(arr, n));
    return 0;
}