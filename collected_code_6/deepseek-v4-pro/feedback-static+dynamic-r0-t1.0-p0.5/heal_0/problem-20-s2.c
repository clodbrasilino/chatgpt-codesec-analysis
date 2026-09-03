#include <stdio.h>
#include <stdbool.h>

bool is_woodall(int n) {
    if (n <= 0) {
        return false;
    }
    
    for (int k = 1; ; k++) {
        long long power = 1;
        for (int i = 0; i < k; i++) {
            power *= 2;
            if (power > n + k) {
                break;
            }
        }
        
        long long woodall = power * k - 1;
        
        if (woodall == n) {
            return true;
        }
        
        if (woodall > n) {
            return false;
        }
    }
}

int main(void) {
    int test_cases[] = {1, 7, 23, 63, 383, 3221225471};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_tests; i++) {
        printf("%d is %s Woodall number\n", 
               test_cases[i], 
               is_woodall(test_cases[i]) ? "a" : "not a");
    }
    
    return 0;
}