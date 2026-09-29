#include <stdio.h>
#include <stdbool.h>

bool is_woodall(int n) {
    if (n <= 0) {
        return false;
    }
    
    for (int k = 1; ; k++) {
        long long woodall = (long long)k * (1LL << k) - 1;
        
        if (woodall == n) {
            return true;
        }
        
        if (woodall > n) {
            return false;
        }
        
        if (k > 30) {
            return false;
        }
    }
}

int main(void) {
    int test_cases[] = {1, 7, 23, 63, 159, 383, 895, 2047, 4607, 10239, 5, 10, 100, 1000};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_tests; i++) {
        int num = test_cases[i];
        printf("%d is %sa Woodall number\n", num, is_woodall(num) ? "" : "not ");
    }
    
    return 0;
}