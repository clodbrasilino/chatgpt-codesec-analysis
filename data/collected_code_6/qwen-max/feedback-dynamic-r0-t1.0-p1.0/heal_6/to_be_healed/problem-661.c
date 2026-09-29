#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 2101, got 1100
  *  test case 2 failed: expected 27, got 19
  *  test case 1 failed: expected 5013, got 3010
  */

int max_sum_no_three_consecutive(int *arr, int n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0];
    if (n == 2) return arr[0] + arr[1];

    int prev1 = arr[0], prev2 = arr[0], prev3 = 0, temp;
    for (int i = 2; i < n; ++i) {
        int pick = arr[i] + prev3;
        int notPick = prev1;
        prev1 = (pick > notPick ? pick : notPick);
        temp = prev2;
        prev2 = prev1;
        prev3 = temp;
    }
    return prev1;
}

int main() {
    int arr1[] = {500, 1000, 1000, 2000, 3000};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("Maximum sum with no three consecutive elements: %d\n", max_sum_no_three_consecutive(arr1, n1));

    int arr2[] = {100, 200, 300, 400};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("Maximum sum with no three consecutive elements: %d\n", max_sum_no_three_consecutive(arr2, n2));

    int arr3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("Maximum sum with no three consecutive elements: %d\n", max_sum_no_three_consecutive(arr3, n3));

    return 0;
}