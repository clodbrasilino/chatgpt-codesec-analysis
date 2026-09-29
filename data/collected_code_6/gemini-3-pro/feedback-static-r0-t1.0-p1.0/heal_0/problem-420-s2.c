#include <stdio.h>
#include <stdlib.h>

unsigned long long cube_sum_even(int n) {
    if (n <= 0) {
        return 0;
    }
    
    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        unsigned long long even_num = (unsigned long long)i * 2;
        sum += even_num * even_num * even_num;
    }
    
    return sum;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        return EXIT_FAILURE;
    }
    
    unsigned long long result = cube_sum_even(n);
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}