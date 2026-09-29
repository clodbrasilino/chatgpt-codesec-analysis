#include <stdio.h>
#include <limits.h>

int minJumps(const int arr[], int n) {
    if (n <= 1) return 0;
    if (arr[0] == 0) return -1;

    int maxReach = arr[0];
    int step = arr[0];
    int jump = 1;

    for (int i = 1; i < n; i++) {
        if (i == n - 1) return jump;

        maxReach = (maxReach > i + arr[i]) ? maxReach : i + arr[i];

        step--;

        if (step == 0) {
            jump++;
            if (i >= maxReach) return -1;
            step = maxReach - i;
        }
    }

    return -1;
}

int main() {
    const int test_cases[][6] = {
        {2, 3, 1, 1, 4},
        {3, 2, 1, 0, 4},
        {0, 2, 3}
    };
    /* Possible weaknesses found:
     *  Variable 'expected' can be declared as const array [constVariable]
     */
    int expected[] = {2, -1, -1};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int k = 0; k < num_tests; k++) {
        int n = sizeof(test_cases[k]) / sizeof(test_cases[k][0]);
        int result = minJumps(test_cases[k], n);
        if (result != expected[k]) {
            printf("Test case %d failed: expected %d, got %d\n", k, expected[k], result);
        } else {
            printf("Test case %d passed: expected %d, got %d\n", k, expected[k], result);
        }
    }

    return 0;
}