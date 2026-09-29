#include <stdio.h>
#include <stdlib.h>

long long multiply(int a, int b) {
    long long result = 0;
    long long abs_a = a;
    long long abs_b = b;

    if (abs_a < 0) {
        abs_a = -abs_a;
    }
    
    if (abs_b < 0) {
        abs_b = -abs_b;
    }

    while (abs_b > 0) {
        if (abs_b & 1) {
            result += abs_a;
        }
        abs_a <<= 1;
        abs_b >>= 1;
    }

    if ((a < 0) != (b < 0)) {
        result = -result;
    }

    return result;
}

int main(void) {
    int test_pairs[5][2] = {
        {15, 25},
        {-10, 20},
        {30, -5},
        {-7, -8},
        {0, 99}
    };
    
    size_t num_tests = sizeof(test_pairs) / sizeof(test_pairs[0]);

    for (size_t i = 0; i < num_tests; i++) {
        int a = test_pairs[i][0];
        int b = test_pairs[i][1];
        long long result = multiply(a, b);
        
        printf("%lld\n", result);
    }

    return EXIT_SUCCESS;
}