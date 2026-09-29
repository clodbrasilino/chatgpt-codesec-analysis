#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 4, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  *  test case 2 failed: expected 2, got <no output>
  */

int count_odd(const int *arr, int n) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] % 2 != 0) {
            ++count;
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = count_odd(arr, n);
    printf("Number of odd elements: %d\n", result);
    return 0;
}