#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int abs_diff(int a, int b) {
    return (a > b) ? (a - b) : (b - a);
}

int digit_distance(int num1, int num2) {
    char s1[12], s2[12];
    snprintf(s1, sizeof(s1), "%d", num1);
    snprintf(s2, sizeof(s2), "%d", num2);

    size_t len1 = strnlen(s1, sizeof(s1));
    size_t len2 = strnlen(s2, sizeof(s2));
    size_t max_len = (len1 > len2) ? len1 : len2;

    int distance = 0;
    for (size_t i = 0; i < max_len; ++i) {
        int d1 = (i < len1) ? s1[i] - '0' : 0;
        int d2 = (i < len2) ? s2[i] - '0' : 0;
        distance += abs_diff(d1, d2);
    }
    return distance;
}

int main() {
    const int test_cases[] = {0, 1, 2};
    const int expected_results[] = {1, 6, 7};
    int num1, num2;

    for (int i = 0; i < 3; ++i) {
        int result;
        switch (test_cases[i]) {
            case 0:
                num1 = 234; num2 = 489; break;
            case 1:
                num1 = 123; num2 = 654; break;
            case 2:
                num1 = 987; num2 = 123; break;
        }
        result = digit_distance(num1, num2);
        if (result == expected_results[i]) {
            printf("Test case %d passed\n", i);
        } else {
            printf("Test case %d failed: expected %d, got %d\n", i, expected_results[i], result);
        }
    }

    return 0;
}