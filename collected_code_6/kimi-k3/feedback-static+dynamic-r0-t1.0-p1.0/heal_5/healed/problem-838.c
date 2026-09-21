#include <stdio.h>
#include <string.h>
#include <limits.h>

int min_swaps(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return -1;
    }
    
    size_t len1 = strnlen(s1, INT_MAX);
    size_t len2 = strnlen(s2, INT_MAX);
    
    if (len1 != len2) {
        return -1;
    }
    
    int count_01 = 0;
    int count_10 = 0;
    
    for (size_t i = 0; i < len1; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '0' && s2[i] == '1') {
                count_01++;
            } else if (s1[i] == '1' && s2[i] == '0') {
                count_10++;
            } else {
                return -1;
            }
        }
    }
    
    if (count_01 != count_10) {
        return -1;
    }
    
    return count_01;
}

int main(void) {
    const char *test_cases[][2] = {
        {"1100", "0011"},
        {"101", "010"},
        {"111", "000"}
    };
    const int expected[] = {2, 1, 0};
    const int num_tests = 3;
    
    for (int i = 0; i < num_tests; i++) {
        int result = min_swaps(test_cases[i][0], test_cases[i][1]);
        printf("%d\n", result);
        if (result == expected[i]) {
            printf("PASS\n");
        } else {
            printf("FAIL\n");
        }
    }
    
    return 0;
}