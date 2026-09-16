#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

bool is_undulating(long long n) {
    if (n < 0) {
        n = -n;
    }
    
    if (n < 100) {
        return false;
    }
    
    int position = 0;
    int pattern_first = -1;
    int pattern_second = -1;
    
    while (n > 0) {
        int curr_digit = n % 10;
        n /= 10;
        
        if (position == 0) {
            pattern_first = curr_digit;
        } else if (position == 1) {
            pattern_second = curr_digit;
            if (pattern_first == pattern_second) {
                return false;
            }
        } else {
            if (position % 2 == 0) {
                if (curr_digit != pattern_first) {
                    return false;
                }
            } else {
                if (curr_digit != pattern_second) {
                    return false;
                }
            }
        }
        
        position++;
    }
    
    return position >= 3;
}

int main(void) {
    long long test_numbers[] = {121, 1212, 12121, 123, 111, 101, 121212, 1234, 0, 12, 1212121};
    size_t num_tests = sizeof(test_numbers) / sizeof(test_numbers[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        printf("%lld: %s\n", test_numbers[i], 
               is_undulating(test_numbers[i]) ? "true" : "false");
    }
    
    return EXIT_SUCCESS;
}