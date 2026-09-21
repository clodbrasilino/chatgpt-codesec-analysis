#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_undulating(long long num) {
    if (num < 0) {
        num = -num;
    }
    
    if (num < 100) {
        return num >= 10 && (num / 10 != num % 10);
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[32];
    int len = snprintf(str, sizeof(str), "%lld", num);
    
    if (len < 0 || len >= (int)sizeof(str)) {
        return false;
    }
    
    if (str[0] == str[1]) {
        return false;
    }
    
    for (int i = 2; i < len; i++) {
        if (str[i] != str[i - 2]) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    long long test_cases[] = {121, 1212, 212, 12121, 123, 111, 12345, 9090, 151515, 100};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_tests; i++) {
        printf("%lld: %s\n", test_cases[i], is_undulating(test_cases[i]) ? "Undulating" : "Not undulating");
    }
    
    return 0;
}