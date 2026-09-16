#include <stdio.h>
#include <string.h>

int min_swaps(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return -1;
    }
    
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    
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
    
    return count_01 + count_10;
}

int main(void) {
    const char *test_s1[] = {"1100", "1100", "10"};
    const char *test_s2[] = {"0011", "1100", "01"};
    const int expected[] = {2, 0, 1};
    int num_tests = 3;
    int all_passed = 1;
    
    for (int i = 0; i < num_tests; i++) {
        int result = min_swaps(test_s1[i], test_s2[i]);
        printf("%d\n", result);
        if (result != expected[i]) {
            all_passed = 0;
        }
    }
    
    return all_passed ? 0 : 1;
}