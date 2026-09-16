#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got 1
  *  test case 1 failed: expected 2, got 1
  */

int countRotations(const int arr[], int n) {
    int min_index = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[min_index]) {
            min_index = i;
        }
    }
    return (min_index == 0 && arr[0] <= arr[n - 1]) ? 0 : min_index;
}

int main() {
    const int test_cases[][6] = {
        {15, 18, 2, 3, 6, 12},
        {4, 5, 6, 7, 0, 1, 2},
        {1, 2, 3, 4, 5, 6, 7}
    };
    const int test_case_sizes[] = {6, 7, 7};
    /* Possible weaknesses found:
     *  Variable 'expected_outputs' is assigned a value that is never used. [unreadVariable]
     */
    const int expected_outputs[] = {2, 4, 0};
    int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int test = 0; test < num_test_cases; test++) {
        int rotations = countRotations(test_cases[test], test_case_sizes[test]);
        printf("Test case %d: Number of rotations: %d\n", test, rotations);
    }

    return 0;
}