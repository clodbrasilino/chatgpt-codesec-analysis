#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (a == 0 && b == 0) {
        return 0;
    }
    
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    
    return a;
}

int find_common_divisor(int a, int b) {
    int result = gcd(a, b);
    if (result == 0) {
        return 1;
    }
    return result;
}

int main(void) {
    int test_pairs[][2] = {
        {12, 18},
        {35, 49},
        {0, 5},
        {0, 0},
        {-24, 36},
        {17, 19},
        {100, 75}
    };
    
    size_t num_pairs = sizeof(test_pairs) / sizeof(test_pairs[0]);
    
    for (size_t i = 0; i < num_pairs; ++i) {
        int a = test_pairs[i][0];
        int b = test_pairs[i][1];
        int divisor = find_common_divisor(a, b);
        printf("Common divisor of %d and %d: %d\n", a, b, divisor);
    }
    
    return 0;
}