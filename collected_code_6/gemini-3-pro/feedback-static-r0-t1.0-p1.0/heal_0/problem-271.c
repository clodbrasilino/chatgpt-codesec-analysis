#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_of_fifth_powers_even(unsigned int n) {
    unsigned long long sum = 0;
    unsigned int i;
    for (i = 1; i <= n; i++) {
        unsigned long long even_num = 2ULL * i;
        unsigned long long power = even_num * even_num * even_num * even_num * even_num;
        sum += power;
    }
    return sum;
}

int main(void) {
    unsigned int n;
    
    if (scanf("%u", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    unsigned long long result = sum_of_fifth_powers_even(n);
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}