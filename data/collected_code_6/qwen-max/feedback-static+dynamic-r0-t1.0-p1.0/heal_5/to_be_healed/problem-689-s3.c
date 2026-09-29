#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 3, got -1
  *  test case 2 failed: expected 10, got -1
  *  test case 1 failed: expected 3, got -1
  */

int minJumps(const int arr[], int n) {
    if (n <= 1) return 0;
    if (arr[0] == 0) return -1;

    int jumps = 1, maxReach = arr[0], steps = arr[0];

    for (int i = 1; i < n && i <= maxReach; i++) {
        if (i + arr[i] > maxReach) maxReach = i + arr[i];

        steps--;
        if (steps == 0) {
            jumps++;
            if (i >= maxReach) return -1;
            steps = maxReach - i;
        }

        if (maxReach >= n - 1) return jumps;
    }

    return -1;
}

int main() {
    const int arr[] = {2, 3, 1, 1, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = minJumps(arr, n);
    printf("Minimum number of jumps: %d\n", result);

    const int arr2[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = minJumps(arr2, n2);
    printf("Minimum number of jumps: %d\n", result2);

    const int arr3[] = {3, 4, 2, 1, 2, 1, 2};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int result3 = minJumps(arr3, n3);
    printf("Minimum number of jumps: %d\n", result3);

    const int arr4[] = {1, 1, 0, 1};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    int result4 = minJumps(arr4, n4);
    printf("Minimum number of jumps: %d\n", result4);

    return 0;
}