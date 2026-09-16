#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int64_t largest_k_mod_x_equals_y(int64_t x, int64_t y) {
    if (x <= 0) {
        return -1;
    }
    if (y < 0 || y >= x) {
        return -1;
    }
    if (y == 0) {
        return 0;
    }
    if (y >= INT64_MAX / x) {
        return -1;
    }
    int64_t max_multiple = INT64_MAX - (INT64_MAX % x);
    if (max_multiple > INT64_MAX - y) {
        return -1;
    }
    return max_multiple + y;
}

int main(void) {
    int64_t test_cases[][2] = {
        {5, 2},
        {10, 0},
        {3, 2},
        {1, 0},
        {7, 6},
        {1000000, 999999},
        {2, 1}
    };
    
    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        int64_t x = test_cases[i][0];
        int64_t y = test_cases[i][1];
        int64_t result = largest_k_mod_x_equals_y(x, y);
        
        printf("x=%lld, y=%lld -> k=%lld", 
               (long long)x, (long long)y, (long long)result);
        if (result >= 0) {
            printf(" (verify: %lld %% %lld = %lld)", 
                   (long long)result, (long long)x, (long long)(result % x));
        }
        printf("\n");
    }
    
    int64_t invalid_cases[][2] = {
        {0, 0},
        {-5, 2},
        {10, -1},
        {5, 5},
        {10, 10}
    };
    
    size_t num_invalid = sizeof(invalid_cases) / sizeof(invalid_cases[0]);
    
    for (size_t i = 0; i < num_invalid; i++) {
        int64_t x = invalid_cases[i][0];
        int64_t y = invalid_cases[i][1];
        int64_t result = largest_k_mod_x_equals_y(x, y);
        
        printf("Invalid: x=%lld, y=%lld -> k=%lld\n", 
               (long long)x, (long long)y, (long long)result);
    }
    
    return 0;
}