#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_perfect_square(int num) {
    if (num < 0) {
        return false;
    }
    
    if (num == 0 || num == 1) {
        return true;
    }
    
    long long left = 1;
    long long right = num / 2;
    
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        long long square = mid * mid;
        
        if (square == num) {
            return true;
        } else if (square < num) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return false;
}

int main(void) {
    int test_cases[] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 2, 3, 5, 8, 10, 15, 99, -4, -16, 2147395600};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_tests; i++) {
        bool result = is_perfect_square(test_cases[i]);
        printf("%d is %sa perfect square\n", test_cases[i], result ? "" : "not ");
    }
    
    return 0;
}