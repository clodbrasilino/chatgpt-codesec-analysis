#include <stdio.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int findMinDifference(int arr[], int n) {
    int min_diff = INT_MAX;
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            int diff = arr[j] - arr[i];
            if (diff < min_diff) {
                min_diff = diff;
            }
        }
    }
    return min_diff;
}

int main() {
    int arr[] = {5, 3, 2, 7, 8, 9, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = findMinDifference(arr, n);
    printf("The minimum difference is: %d\n", result);
    return 0;
}