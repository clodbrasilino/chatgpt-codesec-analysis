#include <stdio.h>

int eulerian_number(int n, int m) {
    if (n == 0 || m >= n || m < 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    if (m == 0) {
        return 1;
    }
    return ((n - m) * eulerian_number(n - 1, m - 1) + (m + 1) * eulerian_number(n - 1, m));
}

int main() {
    int test_cases[] = { {4, 2}, {3, 1}, {5, 2} };
    int expected_results[] = { 11, 4, 26 };
    int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_test_cases; ++i) {
        int n = test_cases[i][0];
        int m = test_cases[i][1];
        int result = eulerian_number(n, m);
        printf("Eulerian number A(%d, %d) is: %d\n", n, m, result);
        if (result != expected_results[i]) {
            printf("Test case %d failed: expected %d, got %d\n", i + 1, expected_results[i], result);
        } else {
            printf("Test case %d passed.\n", i + 1);
        }
    }

    return 0;
}