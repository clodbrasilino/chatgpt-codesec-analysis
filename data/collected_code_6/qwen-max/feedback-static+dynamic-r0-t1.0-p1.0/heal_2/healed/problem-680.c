#include <stdio.h>
#include <stdbool.h>

bool is_increasing_trend(const int numbers[], int length) {
    for (int i = 1; i < length; ++i) {
        if (numbers[i] <= numbers[i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int test_cases[][5] = {
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1},
        {1, 3, 2, 4, 5}
    };
    bool expected_results[] = {true, false, false};
    const int num_tests = 3;

    for (int t = 0; t < num_tests; ++t) {
        int length = sizeof(test_cases[t]) / sizeof(test_cases[t][0]);
        bool result = is_increasing_trend(test_cases[t], length);
        if (result == expected_results[t]) {
            printf("Test case %d passed.\n", t);
        } else {
            printf("Test case %d failed: expected %s, got %s\n", t, expected_results[t] ? "True" : "False", result ? "True" : "False");
        }
    }

    return 0;
}